

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
#     all normalised by sqrt(n entries)
#   1: polynomial
#     byte 0:
#       bit 7: 1
#       bit 0-6: (mod 5 + 1) number of inputs
#     remaining bytes as triplets:
#       byte 0: index into input
#       byte 1: (mod 9 - 4) power
#       byte 2: scale (see below for byte -> float)
#     polynomials are evaluated as:
#       positive power: scale*(input/10)^power
#       negative power: scale*(3*input)^power (clipped 1/0 -> 127 as byte)
#       zero power: scale
#       all normalised by sqrt(n terms)
# indexing into input is
#   positive (mod available): direct index into input
#   negative (mod available): indirect index into input (relative to "here")
# general encoding from byte <-> float is
#   float(b) = signed(b) / sqrt(128) with hard clipping


# --- data structuring


unpack_kernel_size(n::UInt8) = ((n & 0x70) >> 4) + 1, (n & 0x0f) + 1
unpack_polynomial_size(n::UInt8) = Int(((n & 0x7f) % 5) + 1)

b2f(b::Int8) = Float32(reinterpret(Int8, b) / sqrt(128))
f2b(f::Number) = Int8(min(127, max(-128, round(f * sqrt(128)))))

const given = 12  # indices that are constant or taken from position
const header = map(UInt8, collect("goxp"))

@enum Operation kernel polynomial junk

@auto_hash_equals immutable Fragment
    # we only parse to this level because we need to preserve all bits
    # for evolutionary algorithms.  parsing to semantical level
    # discards some bits and life gets complicated.
    operation::Operation
    data::Vector{UInt8}
end

@auto_hash_equals type Expression
    version::UInt8
    # must be maintained by mutating operations
    length::UInt16
    fragment::Vector{Fragment}
    Expression(version::UInt8) = new(version, 7, Fragment[])
    Expression() = Expression(0x00)
end

function read_input(e::ArrayIterator{UInt8}, available)
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

function pack_polynomial(coeffs...)
    n = length(coeffs)
    @assert 1 <= n <= 5
    data = [UInt8(n-1) | 0x80]
    for (input, power, scale) in coeffs
        @assert -4 <= power <= 4
        if power > 0
            scale = scale * 10
        elseif power < 0
            scale = scale / 3
        end
        push!(data, UInt8(input-1), UInt8(power + 4), f2b(scale))
    end
    Fragment(polynomial, data)
end

function unpack_polynomial(f::Fragment, available)
    e = ArrayIterator(f.data)
    n = unpack_polynomial_size(read(e))
    function coeff(e)
        input = read_input(e, available)
        power = Int(read(e) % 9) - 4
        if power == 0
            scale = b2f(read(e, Int8))
        elseif power > 0
            scale = b2f(read(e, Int8)) / 10
        else
            scale = b2f(read(e, Int8)) * 3
        end
        (input, power, scale)
    end
    [coeff(e) for i in 1:n]
end

function Base.push!(e::Expression, f::Fragment)
    push!(e.fragment, f)
    e.length += length(f.data)
end

function unpack_expression(data::Vector{UInt8})
    d = ArrayIterator(data)
    @assert read(d, 4) == header
    e = Expression(read(d))
    length = read(d, UInt16)
    
    while !done(d)
        tag = peek(d)
        if tag & 0x80 == 0
            op = kernel
            n = prod(unpack_kernel_size(tag)) + 4
        else
            op = polynomial
            n = unpack_polynomial_size(tag) * 3 + 1
        end
        if n > length - d.state
            f = Fragment(junk, read(d, length - d.state + 1))
        else
            f = Fragment(op, read(d, n))
        end
        push!(e, f)
    end

    # this is all we support right now
    @assert e.version == 0x00
    @assert e.length == length
    e
end

Expression(data::Vector{UInt8}) = unpack_expression(data)

pack_expression(e::Expression) = vcat(header, [0x00], reinterpret(UInt8, [e.length]), [f.data for f in e.fragment]...)


# --- evaluation


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

function evaluate_kernel{N}(f::Fragment, p::Position{N}, d::Array{Int8, 3}, available)
    e = ArrayIterator(f.data)
    nx, ny = unpack_kernel_size(read(e))
    n = nx * ny
    edge = b2f(read(e, Int8))
    cy, cx = [divrem(read(e) % n, nx)...] + [1,1]
    input = read_input(e, available)
    kernel = reshape([b2f(read(e, Int8)) for i in 1:nx*ny], nx, ny)
    my_acc = zeros(Float32, N, N)
    @forall i j N begin
        for di in 1:nx
            for dj in 1:ny
                # the best way to understand this is to draw a picture.
                # it's basically a coord change from one frame (kernel)
                # to the other (data).
                my_acc[i,j] += kernel[di, dj] * lookup(i+di-cx, j+dj-cy, i, j, d, input, edge, p)
            end
        end
        d[i, j, available+1] = f2b(my_acc[i, j] / sqrt(n))
    end
end

function evaluate_polynomial{N}(f::Fragment, p::Position{N}, d::Array{Int8, 3}, available)
    e = ArrayIterator(f.data)
    coeffs = unpack_polynomial(f, available)
    my_acc = zeros(Float32, N, N)
    for (input, power, scale) in coeffs
        @forall i j N begin
            value = lookup(i, j, 0, 0, d, input, 0.0, p)
            my_acc[i, j] += scale * value^power
        end
    end
    @forall i j N begin
        d[i, j, available+1] = f2b(my_acc[i, j] / sqrt(length(coeffs)))
    end
end

function evaluate(f::Fragment, p::Position, d::Array{Int8, 3}, available)
    if f.operation == kernel
        evaluate_kernel(f, p, d, available)
    elseif f.operation == polynomial
        evaluate_polynomial(f, p, d, available)
    elseif available > 0
        # copy previous data on no-op so that final data (used as
        # output) is always valid
        d[:,:,available+1] = d[:,:,available]
    end
end

function evaluate{N}(e::Expression, p::Position{N})
    n = length(e.fragment)
    output_data = zeros(Int8, N, N, n)
    for i in 1:n
        evaluate(e.fragment[i], p, output_data, i-1)
    end
    # output is final frame (most complex)
    output_data[:,:,n]
end

function evaluate(data::Array{UInt8, 1}, p::Position)
    evaluate(Expression(data), p)
end


# --- move extraction


