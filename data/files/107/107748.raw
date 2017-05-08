

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
#       positive power: scale*(input/10)**power
#       negative power: scale*(3*input)**power (clipped 1/0 -> 127 as byte)
#       zero power: scale
# indexing into input is
#   positive (mod available): direct index into input
#   negative (mod available): indirect index into input (relative to "here")
# general encoding from byte <-> float is
#   float(b) = signed(b) / sqrt(128) with hard clipping



unpack_kernel_size(n::UInt8) = (n & 0x70) >> 4, n & 0x0f

b2f(x::Int8) = Float32(coerce(Int8, x) / sqrt(128))
f2b(x::Float32) = Int8(max(127, min(-128, round(x * sqrt(128)))))

const given = 12  # indices that are constant or taken from position

function count_operations(e)
    count = 0
    try
        while true
            tag = read(e)
            if tag & 0x80 ==  n = product(unpack_kernel_size(tag))
                read(e, n+3)  # drop edge + locn + index + kernel
            else
                n = tag & 0x07
                read(e, n*3)
            end
            count += 1
        end
    catch x
        # ignore end of data
        println(x)  # check and rethrow
        rethrow()
    end        
end

function lookup{N}(x, y, ox, oy, d::Array{Int8, 3}, inp, edge, p::Position{N})
    if 1 <= x <= N && 1 <= y <= N
        if inp > given
            # yay, simple lookup
            b2f(d[x, y, inp-given])
        elseif inp == 1
            # constant 0
            zero(Float32)
        elseif inp == 2
            # constant 1
            one(Float32)
        elseif inp == 3
            # 1 for black, 0 for empty, -1 for white
            Float32(point(p, x, y))
        elseif inp == 4
            # 1 if same group as 'centre', -1 if not
            Float32(p.groups.index[x, y] == p.groups.index[ox, oy] ? 1 : -1)
        elseif inp == 5
            # size of group at that point
            Float32(p.groups.size[x, y])
        elseif inp == 6
            # number of lives in group at that point
            Float32(p.groups.lives[x, y])
        elseif inp == 7
            # distance to nearest stone (-ve for white)
            Float32(p.flood.distance[x, y])
        elseif inp == 8
            # 1 if owned by black, -1 owned by white, 0 otherwise
            b = p.space.border[x, y]
            if b == 0 || b == 3
                zero(Float32)
            elseif b == 1
                one(Float32)
            else
                -one(Float32)
            end
        elseif inp == 9
            # 1 if same space as 'centre', -1 if not            
            Float32(p.space.index[x, y] == p.space.index[ox, oy] ? 1 : -1)
        elseif inp == 10
            # constant score (+ve for black)
            Float32(p.score.total)
        elseif inp == 11
            # fraction of space that is 'owned'
            p.score.owned
        elseif inp == 12
            # fraction of board that is stones
            p.score.stones
        end
    else
        edge
    end
end

function read_input(e::StatefulIterator, available)
    inp = read(e, Int8)
    n = given + available
    if inp < 0
        n - ((-inp) % n)
    else
        1 + (inp % n)
    end
end

function evaluate_kernel{N}(tag::UInt8, e::StatefulIterator, p::Position{N}, d::Array{Int8, 3}, available)
    nx, ny = unpack_kernel_size(tag)
    edge = b2f(read(e, Int8))
    cy, cx = [divrem(read(e) % (nx * ny), nx)...] + [1,1]
    input = read_input(e, available)
    kernel = reshape([b2f(read(e, Int8)) for i in nx * ny], nx, ny)
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
    n = 1 + (tag & 0x07)
    my_acc = zeros(Float32, N, N)
    @forall i j N begin
        for k = 1:n
            input = read_input(e)
            scale = b2f(read(e, Int8))
            power = (read(e) % 9) - 4
            if power == 0
                my_acc[i, j] += scale
            else
                value = lookup(i, j, 0, 0, d, input, 0, p)
                if power > 0
                    my_acc[i, j] += scale * (input / 10)**power
                else
                    my_acc[i, j] += scale * (3 * input)**power
                end
            end
        end
        d[i, j, available+1] = f2b(my_acc[i, j])
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
    @assert read(e, 4) == map(UInt8, "goxp")   # header
    @assert read(e) = 0x00                     # version
    len = read(e, UInt16)                      # length
    n = count_operations(copy(e))
    output_data = zeros(Int8, N, N, n)
    for i in 1:n
        evaluate(e, p, output_data, i-1)
    end
    output_data[:,:,n]
end
