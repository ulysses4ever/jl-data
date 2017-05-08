

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
#       bit 7: 0 (polynomial tag)
#       bit 0-6: size in x and y (see code)
#     byte 1: byte used for input outside board edges
#     byte 2: (mod size of grid) location of output within the kernel 
#     byte 3: index into input
#     remaining bytes as kernel (see below for byte -> float)
#     all normalised by sqrt(n entries)
#   1: arithmetic
#     byte 0:
#       bit 7: 1 (arithmetic tag)
#       bit 6:
#         0: additiion/subtraction
#         1: multiplication/division
#       bit 5-2: 4 flags (after first) mult/div and sine
#       bit 1-0: (+1) number of terms
#     remaining bytes as pairs:
#       byte 0: index into input
#       byte 1: scale (see below for byte -> float)
# indexing into input is
#   positive (mod available): direct index into input
#   negative (mod available): indirect index into input (relative to "here")
# general encoding from byte <-> float is
#   float(b) = signed(b) / scale (see below) with hard clipping

# chunking

# new fragments start every chunk (see below) bytes.  this allows changes
# without 'breaking' all following fragments.

# evaluation order

# originally fragments were evaluated in the order they appeared in the
# expression, with the final value being taken from the last expression.
# but this evaluated unused expressions, to the evaluation was made lazy.
# and then the ordering was reversed, so that the final value is taken
# from the first fragment defined, and references are to later fragments.
# this gives more persistence across merges, because early fragments 
# are not affected by re-interpretatin of modified later fragments.



# --- data structuring


unpack_kernel_size(n::UInt8) = ((n & 0x70) >> 4) + 1, (n & 0x0f) + 1
unpack_arithmetic_size(n::UInt8) = (n & 0x03) + 1

const scale = 64.0
b2f(b::Int8) = Float32(reinterpret(Int8, b) / scale)
f2b(f::Number) = Int8(min(127, max(-128, round(f * scale))))

const chunk = 16
chunkend(s) = read(s, UInt8, min(available(s), s.state % chunk))

const given = 12  # indices that are constant or taken from position
const header = map(UInt8, collect("goxp"))
const lheader = 7   # 4 chars, 1 version, 2 length

@enum Operation kernel product addition junk

@auto_hash_equals immutable Fragment
    # we only parse to this level because we need to preserve all bits
    # for evolutionary algorithms.  parsing to semantical level
    # discards some bits and life gets complicated.
    operation::Operation
    data::Vector{UInt8}
    padding::Vector{UInt8}
end

@auto_hash_equals type Expression
    version::UInt8
    # must be maintained by mutating operations
    length::UInt16
    fragment::Vector{Fragment}
    Expression(version::UInt8) = new(version, 7, Fragment[])
    Expression() = Expression(0x00)
end

function read_input(e::StatefulIterator{Vector{UInt8},Int}, available)
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

function unpack_kernel(f::Fragment, available)
    e = StatefulIterator(f.data)
    nx, ny = unpack_kernel_size(read(e))
    input = read_input(e, available)
    edge = b2f(read(e, Int8))
    cy, cx = map(Int, [divrem(read(e) % (nx*ny), nx)...] + [1,1])
    kernel = reshape([b2f(read(e, Int8)) for i in 1:nx*ny], nx, ny)
    (input, edge, (cx, cy), kernel)
end

function pack_kernel(input, edge, c, coeffs)
    cx, cy = c
    nx, ny = size(coeffs)
    data = [UInt8(nx-1) << 4 | UInt8(ny-1)]
    push!(data, UInt8(input-1), f2b(edge), UInt8((cy-1)*nx + cx-1))
    append!(data, map(f2b, reshape(coeffs, nx*ny)))
    Fragment(kernel, data, [])
end

function unpack_arithmetic(f::Fragment, available)
    e = StatefulIterator(f.data)
    tag = read(e)
    n = unpack_arithmetic_size(tag)
    flags = ((tag >> 2) & 0x0f) << 1
    function term(e)
        input = read_input(e, available)
        scale = b2f(read(e, Int8))
        change = flags & 0x01 == 0x01
        flags = flags >> 1
        (input, scale, change)
    end
    [term(e) for i in 1:n]
end

unpack_product = unpack_arithmetic
unpack_addition = unpack_arithmetic

function pack_arithmetic(coeffs...)
    n = length(coeffs)
    @assert 1 <= n <= 5
    data = [UInt8(n-1) | 0x80]
    flags, mask = 0x00, 0x01
    for (input, scale, change) in coeffs
        push!(data, UInt8(input-1), f2b(scale))
        flags = flags | (change ? mask : 0x00)
        mask = mask << 1
    end
    data[1] = data[1] | ((flags >> 1) << 2)
    data
end

pack_addition(coeffs...) = Fragment(addition, pack_arithmetic(coeffs...), [])

function pack_product(coeffs...)
    data = pack_arithmetic(coeffs...)
    data[1] = data[1] | 0x40
    Fragment(product, data, [])
end

function Base.push!(e::Expression, f::Fragment)
    # by appending junk to the previous padding we don't have to worry
    # about junk during evaluation.
    if f.operation == junk && length(e.fragment) > 0
        append!(e.fragment[end].padding, f.data)
    else
        push!(e.fragment, f)
    end
    e.length += length(f.data) + length(f.padding)
end

function unpack_expression(data::Vector{UInt8})
    d = StatefulIterator(data)
    @assert read(d, 4) == header
    e = Expression(read(d))
    length = read(d, UInt16)
    
    while !done(d)
        tag = peek(d)
        if tag & 0x80 == 0
            op = kernel
            n = prod(unpack_kernel_size(tag)) + 4
        elseif tag & 0x40 == 0
            op = addition
            n = unpack_arithmetic_size(tag) * 2 + 1
        else
            op = product
            n = unpack_arithmetic_size(tag) * 2 + 1
        end
        if n > available(d)
            f = Fragment(junk, read(d, available(d)), chunkend(d))
        else
            f = Fragment(op, read(d, n), chunkend(d))
        end
        push!(e, f)
    end

    # this is all we support right now
    @assert e.version == 0x00
    @assert e.length == length
    e
end

Expression(data::Vector{UInt8}) = unpack_expression(data)

function pack_expression(e::Expression)
    data = vcat(header, [0x00], reinterpret(UInt8, [e.length]))
    for f in e.fragment
        fragment = vcat(f.data, f.padding)
        append!(data, fragment)
    end
    @assert length(data) == e.length
    data
end


# --- evaluation


function lookup{N}(x, y, ox, oy, d::Array{Int8, 3}, input, edge, p::Position{N}, t::Point)
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
            # 1 for "our" colour, 0 for space, "-1" for opponent's colour
            Float32(Int(t) * Int(point(p, x, y)))
        elseif input == 4
            if ox != 0 && oy != 0
                # kernel: 1 if same group as 'centre', -1 if not
                Float32(p.groups.index[x, y] == p.groups.index[ox, oy] ? 1 : -1)
            else
                # arithmetic: can't think of anything better here
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
            # distance to nearest stone (-ve for opponent's colour)
            Float32(Int(t) * p.flood.distance[x, y])
        elseif input == 8
            # 1 if owned by us, -1 owned by opponent, 0 otherwise
            b = p.space.border[x, y]
            if b == 0 || b == 3
                zero(Float32)
            elseif b == border_mask(t)
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
            # constant score (+ve for us)
            Float32(p.score.total * Int(t))
        elseif input == 11
            # fraction of space that is 'owned'
            Float32(p.score.owned / (N*N - p.score.stones))
        elseif input == 12
            # fraction of board that is stones
            p.score.stones
        end
    else
        edge
    end
end

function evaluate_kernel{N}(f::Fragment, p::Position{N}, t::Point, d::Array{Int8, 3}, available, transform)
    input, edge, (cx, cy), coeffs = unpack_kernel(f, available)
    nx, ny = size(coeffs)
    my_acc = zeros(Float32, N, N)
    @forall i j N begin
        for di in 1:nx
            for dj in 1:ny
                ddi, ddj = [di-cx dj-cy] * transform
                # the best way to understand this is to draw a picture.
                # it's basically a coord change from one frame (coeffs)
                # to the other (data).
                my_acc[i,j] += coeffs[di, dj] * lookup(i+ddi, j+ddj, i, j, d, input, edge, p, t)
            end
        end
        d[i, j, available+1] = f2b(my_acc[i, j] / sqrt(nx*ny))
    end
end

function evaluate_arithmetic{N}(f::Fragment, p::Position{N}, t::Point, d::Array{Int8, 3}, available, transform)
    coeffs = unpack_addition(f, available)
    my_acc = zeros(Float32, N, N)
    for (input, scale, change) in coeffs
        @forall i j N begin
            value = lookup(i, j, 0, 0, d, input, 0.0, p, t)
            my_acc[i, j] += scale * (change ? transform(value) : value)
        end
    end
    @forall i j N begin
        d[i, j, available+1] = f2b(my_acc[i, j] / sqrt(length(coeffs)))
    end
end

function evaluate(f::Fragment, p::Position, t::Point, d::Array{Int8, 3}, available, transform)
    if f.operation == kernel
        evaluate_kernel(f, p, t, d, available, transform)
    elseif f.operation == addition
        evaluate_arithmetic(f, p, t, d, available, x -> sin(pi * x / 128))
    elseif f.operation == product
        evaluate_arithmetic(f, p, t, d, available, x -> 1/x)
    end
end

function evaluate{N}(e::Expression, p::Position{N}, t::Point)
    n = length(e.fragment)
    my_acc = zeros(Float32, N, N)
    # these are the 8 ways that kernels can be evaluated.  if we treat
    # the numbers as log(prob) then it makes a kind of weird sense
    # that we are adding these together.
    for transform in ([1 0; 0 1], [0 1; -1 0], [-1 0; 0 -1], [0 -1; 1 0],
                      [1 0; 0 -1], [0 1; 1 0], [-1 0; 0 1], [0 -1; -1 0])
        output_data = zeros(Int8, N, N, n)
        # evaluate backwards, but store output_data forwards so indices
        # still work correctly.
        for i in n:-1:1
            evaluate(e.fragment[i], p, t, output_data, n-i, transform)
        end
        # output is final frame (most complex)
        my_acc += map(b2f, output_data[:,:,n])
    end
    my_acc
end

"""return an array of log(p) of the probability that a move is good at
a particular board point, for colour t."""
function evaluate(e::Array{UInt8, 1}, p::Position, t::Point)
    evaluate(Expression(e), p, t)
end


# --- lazy evaluation


function lookup_lazy{N}(f, x, y, ox, oy, e, d::Array{Int8, 3}, input, edge, p::Position{N}, t::Point, transform)
    if 1 <= x <= N && 1 <= y <= N
        if input > given
            # yay, simple lookup
            i = input-given
            # not so simple inference of fragment that corresponds to
            # output_data
            e[i] || evaluate_lazy(f, length(f)-i+1, p, t, e, d, transform)
            b2f(d[x, y, i])
        elseif input == 1
            # constant 0
            zero(Float32)
        elseif input == 2
            # constant 1
            one(Float32)
        elseif input == 3
            # 1 for "our" colour, 0 for space, "-1" for opponent's colour
            Float32(Int(t) * Int(point(p, x, y)))
        elseif input == 4
            if ox != 0 && oy != 0
                # kernel: 1 if same group as 'centre', -1 if not
                Float32(p.groups.index[x, y] == p.groups.index[ox, oy] ? 1 : -1)
            else
                # arithmetic: can't think of anything better here
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
            # distance to nearest stone (-ve for opponent's colour)
            Float32(Int(t) * p.flood.distance[x, y])
        elseif input == 8
            # 1 if owned by us, -1 owned by opponent, 0 otherwise
            b = p.space.border[x, y]
            if b == 0 || b == 3
                zero(Float32)
            elseif b == border_mask(t)
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
            # constant score (+ve for us)
            Float32(p.score.total * Int(t))
        elseif input == 11
            # fraction of space that is 'owned'
            Float32(p.score.owned / (N*N - p.score.stones))
        elseif input == 12
            # fraction of board that is stones
            p.score.stones
        end
    else
        edge
    end
end

function evaluate_lazy_kernel{N}(f::Vector{Fragment}, index, p::Position{N}, t::Point, e, d::Array{Int8, 3}, transform)
    n = length(f)
    input, edge, (cx, cy), coeffs = unpack_kernel(f[index], n-index)
    nx, ny = size(coeffs)
    my_acc = zeros(Float32, N, N)
    @forall i j N begin
        for di in 1:nx
            for dj in 1:ny
                ddi, ddj = [di-cx dj-cy] * transform
                # the best way to understand this is to draw a picture.
                # it's basically a coord change from one frame (coeffs)
                # to the other (data).
                my_acc[i,j] += coeffs[di, dj] * lookup_lazy(f, i+ddi, j+ddj, i, j, e, d, input, edge, p, t, transform)
            end
        end
        d[i, j, n-index+1] = f2b(my_acc[i, j] / sqrt(nx*ny))
    end
    e[n-index+1] = true
end

function evaluate_lazy_arithmetic{N}(f::Vector{Fragment}, index, p::Position{N}, t::Point, e, d::Array{Int8, 3}, g, transform)
    n = length(f)
    coeffs = unpack_addition(f[index], n-index)
    my_acc = zeros(Float32, N, N)
    for (input, scale, change) in coeffs
        @forall i j N begin
            value = lookup_lazy(f, i, j, 0, 0, e, d, input, 0.0, p, t, transform)
            my_acc[i, j] += scale * (change ? g(value) : value)
        end
    end
    @forall i j N begin
        d[i, j, n-index+1] = f2b(my_acc[i, j] / sqrt(length(coeffs)))
    end
    e[n-index+1] = true
end

function evaluate_lazy(f::Vector{Fragment}, i, p::Position, t::Point, e, d::Array{Int8, 3}, transform)
    fragment = f[i]
    if fragment.operation == kernel
        evaluate_lazy_kernel(f, i, p, t, e, d, transform)
    elseif fragment.operation == addition
        evaluate_lazy_arithmetic(f, i, p, t, e, d, x -> sin(pi * x / 128), transform)
    elseif fragment.operation == product
        evaluate_lazy_arithmetic(f, i, p, t, e, d, x -> 1/x, transform)
    end
end

function evaluate_lazy{N}(e::Expression, p::Position{N}, t::Point)
    n = length(e.fragment)
    my_acc = zeros(Float32, N, N)
    # these are the 8 ways that kernels can be evaluated.  if we treat
    # the numbers as log(prob) then it makes a kind of weird sense
    # that we are adding these together.
    for transform in ([1 0; 0 1], [0 1; -1 0], [-1 0; 0 -1], [0 -1; 1 0],
                      [1 0; 0 -1], [0 1; 1 0], [-1 0; 0 1], [0 -1; -1 0])
        evaluated = zeros(Bool, n)
        output_data = zeros(Int8, N, N, n)
        evaluate_lazy(e.fragment, 1, p, t, evaluated, output_data, transform)
        # output is final frame (most complex)
        my_acc += map(b2f, output_data[:,:,n])
    end
    my_acc
end

function evaluate_lazy(e::Array{UInt8, 1}, p::Position, t::Point)
    evaluate_lazy(Expression(e), p, t)
end


# --- move extraction


# the above generates a matrix of 'values' that can be positive or
# negative.  the best interpretation i can give to that is log(prob).
# and in a sense i get to choose, because if i decide that and evolve
# on that basis, then that is what i get.

# however, it's damn spiky.  so any random sampling will be dominated
# by the largest numbers.  so instead, we just pick off the largest
# scoring locations (and then exclude invalid moves etc).

function moves{N}(e::Array{UInt8, 1}, p::Position{N}, t::Point, lazy::Bool, rng)
    logp = lazy ? evaluate_lazy(e, p, t) : evaluate(e, p, t)
    indexed = reshape([(logp[i, j], (i, j)) for i in 1:N, j in 1:N], N*N)
    positive = filter(x -> x[1] > 0, indexed)
    possible = filter(x -> valid(p, t, x[2]...), positive)
    map(x -> x[2], sort(shuffle(rng, possible), by=x -> x[1]))
end


# --- analysis

const lookup_dict = Dict{Int,ASCIIString}(1 => "zero",
                                          2 => "one",
                                          3 => "point",
                                          4 => "group index",
                                          5 => "group size",
                                          6 => "group lives",
                                          7 => "flood",
                                          8 => "space owner",
                                          9 => "same space",
                                          10 => "score",
                                          11 => "owned %",
                                          12 => "stones %")

function lookup_name(input, n)
    if input > given
        n-(input - given)+1
    else
        lookup_dict[input]
    end
end

int(x) = typeof(x) <: Integer

function dump_kernel(i, f)
    n = length(f)
    input = lookup_name(unpack_kernel(f[i], n-i)[1], n)
    println(" $i kernel($input)")
    filter(int, [input])
end

term2str(n, input, scale, change) = string("$(scale)*$(lookup_name(input, n))", change ? "!" : "")

function dump_arithmetic(i, f, op)
    n = length(f)
    terms = unpack_arithmetic(f[i], n-i)
    expr = join(map(x -> term2str(n, x...), terms), " $op ")
    println(" $i $expr")
    filter(int, map(x -> lookup_name(x[1], n), terms))
end

function dump_fragment(i, f, used)
    if f[i].operation == kernel
        refs = dump_kernel(i, f)
    elseif f[i].operation == addition
        refs = dump_arithmetic(i, f, "+")
    elseif f[i].operation == product
        refs = dump_arithmetic(i, f, "*")
    else
        refs = Int[]
    end
    for ref in refs
        push!(used, ref)
    end
end

function dump_expression(e::Expression)
    used = Set([1])
    for (i, fragment) in collect(enumerate(e.fragment))
        if i in used
            dump_fragment(i, e.fragment, used)
        end
    end
end

dump_expression(e::Vector{UInt8}) = dump_expression(unpack_expression(e))
