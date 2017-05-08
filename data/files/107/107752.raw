

# overview

# so this isn't a neural net.  roughly, it's a series of matrix
# operations, where the "matrix" values are the same size as the
# playing board.

# the final result, after evaluating the operations, is treated as a
# probability distribution for where to make the next move.

# the input matrices are taken from the position itself - so, for
# example, a matrix where spaces are 0, black is 1 and white is -1.
# there are also two contant matrices, with the values 0 and 1 at
# every point.

# the operations available are:
# - convolution with a kernel
# - addition of two values scaled by some factor
# - product of two values raised to some power

# implementation

# to make meta-heuristics as effective as possible we want the
# representation to be very compact (everything counts), and for all
# values to be normalised (everything is useful).

# so we use bytes for values, but evaluate expressins using floats.
# the conversion from byte to float depends on the context.

# byte/serialisation format

# the idea here is to make this as flexible as possible, so that we
# can move data between different experiments.  its quite possible
# that any particular run / optimisation will be much more
# restrictive.

# header: "go" + "xp" (expression) + byte for version (version 0 below)
# length: unsigned two bytes (for following data, excluding header + length)
#         (any final operation that is incomplete because of the length
#         is simply discarded)
# operations: repeated until end (discarding any incomplete at end)
#   bit 7 of first byte gives type and size
#   0: kernel
#     byte 0: 
#       bit 7: 0
#       bit 0-6: size in x and y (see code)
#     byte 1: byte used for input outside board edges
#     byte 2: (mod size of grid) location of output within the kernel 
#     byte 3: index into input
#     remaining bytes as kernel (see below for byte -> float)
#   1: polynomial
#     byte 0:
#       bit 7: 1
#       bit 6-4: unused
#       bit 0-3: (+1) number of inputs
#     remaining bytes as triplets:
#       byte 0: index into input
#       byte 1: scale (see below for byte -> float)
#       byte 2: (mod 9 - 4) power
#     polynomials are evaluated as:
#       positive power: scale*(input/10)^power
#       negative power: scale*(3*input)^power (clipped 1/0 -> 127 as byte)
#       zero power: scale
# indexing into input is
#   positive (mod available): direct index into input
#   negative (mod available): indirect index into input (relative to "here")
# general encoding from byte <-> float is
#   float(b) = signed(b) / sqrt(128) with hard clipping



unpack_kernel_size(n::UInt8) = ((n & 0x70) >> 4) + 1, (n & 0x0f) + 1
unpack_polynomial_size(n::UInt8) = 1 + (n & 0x07)

b2f(b::Int8) = Float32(reinterpret(Int8, b) / sqrt(128))
f2b(f::Float32) = Int8(min(127, max(-128, round(f * sqrt(128)))))

const given = 12  # indices that are constant or taken from position

function count_operations(e)
    count = 0
    try
        while true
            tag = read(e)
            if tag & 0x80 == 0
                n = prod(unpack_kernel_size(tag))
                read(e, n+3)  # drop edge + locn + index + kernel
            else
                n = unpack_polynomial_size(tag)
                read(e, n*3)
            end
            count += 1
        end
    catch x
        # ignore end of data
        if ! isa(x, BoundsError)
            rethrow()
        end
    end
    count
end

function lookup{N}(x, y, ox, oy, d::Array{Int8, 3}, input, edge, p::Position{N})
    if 1 <= x <= N && 1 <= y <= N
        if input > given
            # yay, simple lookup
            b2f(d[x, y, input-given])
        elseif input == 1
            # constant 0
            zero(Float32)
        elseif input == 2
            # constant 1
            one(Float32)
        elseif input == 3
            # 1 for black, 0 for empty, -1 for white
            Float32(Int(point(p, x, y)))
        elseif input == 4
            if ox != 0 && oy != 0
                # kernel: 1 if same group as 'centre', -1 if not
                Float32(p.groups.index[x, y] == p.groups.index[ox, oy] ? 1 : -1)
            else
                # polynomial: can't think of anything better here
                Float32(p.groups.index[x, y])
            end
        elseif input == 5
            # size of group at that point
            i = p.groups.index[x, y]
            if i > 0
                Float32(p.groups.size[i])
            else
                edge
            end
        elseif input == 6
            # number of lives in group at that point
            i = p.groups.index[x, y]
            if i > 0
                Float32(p.groups.lives[i])
            else
                edge
            end
        elseif input == 7
            # distance to nearest stone (-ve for white)
            Float32(p.flood.distance[x, y])
        elseif input == 8
            # 1 if owned by black, -1 owned by white, 0 otherwise
            b = p.space.border[x, y]
            if b == 0 || b == 3
                zero(Float32)
            elseif b == 1
                one(Float32)
            else
                -one(Float32)
            end
        elseif input == 9
            if ox != 0 && oy != 0
                # 1 if same space as 'centre', -1 if not            
                Float32(p.space.index[x, y] == p.space.index[ox, oy] ? 1 : -1)
            else
                # polynomial: can't think of anything better here
                Float32(p.space.index[x, y])
            end
        elseif input == 10
            # constant score (+ve for black)
            Float32(p.score.total)
        elseif input == 11
            # fraction of space that is 'owned'
            p.score.owned
        elseif input == 12
            # fraction of board that is stones
            p.score.stones
        end
    else
        edge
    end
end

function read_input(e::StatefulIterator, available)
    input = read(e, Int8)
    n = given + available
    # abs(-128) = -128 for Int8
    index = abs(Int(input)) % n
    if input < 0
        n - index
    else
        1 + index
    end
end

function evaluate_kernel{N}(tag::UInt8, e::StatefulIterator, p::Position{N}, d::Array{Int8, 3}, available)
    nx, ny = unpack_kernel_size(tag)
    edge = b2f(read(e, Int8))
    cy, cx = [divrem(read(e) % (nx * ny), nx)...] + [1,1]
    input = read_input(e, available)
    kernel = reshape([b2f(read(e, Int8)) for i in 1:nx*ny], nx, ny)
    my_acc = zeros(Float32, N, N)
    @forall i j N begin
        for di in 1:nx
            for dj in 1:ny
                # the best way to understand this is to draw a picture.
                # it's basically a coord change from one frame (kernel)
                # to the other (data).
                my_acc[i,j] += lookup(i+di-cx, j+dj-cy, i, j, d, input, edge, p)
            end
        end
        d[i, j, available+1] = f2b(my_acc[i, j])
    end
end

function evaluate_polynomial{N}(tag::UInt8, e::StatefulIterator, p::Position{N}, d::Array{Int8, 3}, available)
    n = unpack_polynomial_size(tag)
    my_acc = zeros(Float32, N, N)
    for k in 1:n
        input = read_input(e, available)
        scale = b2f(read(e, Int8))
        power = Int(read(e) % 9) - 4
        @forall i j N begin
            if power == 0
                my_acc[i, j] += scale
            else
                value = lookup(i, j, 0, 0, d, input, 0.0, p)
                if power > 0
                    my_acc[i, j] += scale * (value / 10)^power
                else
                    my_acc[i, j] += scale * (3 * value)^power
                end
            end
            if k == n
                d[i, j, available+1] = f2b(my_acc[i, j])
            end
        end
    end
end

function evaluate(e::StatefulIterator, p::Position, d::Array{Int8, 3}, available)
    tag = read(e)
    if tag &0x80 == 0
        evaluate_kernel(tag, e, p, d, available)
    else
        evaluate_polynomial(tag, e, p, d, available)
    end
end

function evaluate{N}(data::Array{UInt8, 1}, p::Position{N})
    e = StatefulIterator(data)
    @assert read(e, 4) == map(UInt8, collect("goxp"))   # header
    @assert read(e) == 0x00                             # version
    @assert read(e, UInt16) == length(data)             # length
    n = count_operations(copy(e))
    output_data = zeros(Int8, N, N, n)
    for i in 1:n
        evaluate(e, p, output_data, i-1)
#        println(fix(map(b2f, output_data[:,:,i])))
    end
    output_data[:,:,n]
end

