

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
#   bit 6+7 of first byte gives type
#   00: jump
#     byte 0:
#       bit 6-7 (delegate tag)
#       bit 0-5 index to jump to (-n-1 so always -ve, relative)
#   01: kernel
#     byte 0: 
#       bit 6-7: 0 (kernel tag)
#       bit 0-5: size in x and y (see code)
#     byte 1: index into input
#     byte 2: byte used for input outside board edges
#     byte 3: (mod size of grid) location of output within the kernel 
#     byte 4: (mod number of combines) how to combine transforms
#     remaining bytes as kernel (see below for byte -> float)
#     all normalised by sqrt(n entries)
#   10, 11: arithmetic
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

# new fragments start every chunk (see below) bytes after the header.
# this allows changes without 'breaking' all following fragments.

# evaluation order

# originally fragments were evaluated in the order they appeared in the
# expression, with the final value being taken from the last expression.
# but this evaluated unused expressions, to the evaluation was made lazy.
# and then the ordering was reversed, so that the final value is taken
# from the first fragment defined, and references are to later fragments.
# this gives more persistence across merges, because early fragments 
# are not affected by re-interpretation of modified later fragments.



# --- data structuring


const kernel_extra = 5
const arith_extra = 1
unpack_kernel_size(n::UInt8) = ((n & 0x38) >> 3) + 1, (n & 0x07) + 1
unpack_arithmetic_size(n::UInt8) = (n & 0x03) + 1

const scale = 64.0
b2f(b::Int8) = Float32(reinterpret(Int8, b) / scale)
f2b(f::Number) = Int8(min(127, max(-128, round(f * scale))))

const chunk = 8
function chunkend(s)
    n = (s.state - lheader - 1) % chunk
    if n > 0
        read(s, UInt8, min(available(s), chunk - n))
    else
        UInt8[]
    end
end

const given_atom = 14
const given_kern = 3
const header = map(UInt8, collect("goxp"))
const lheader = 7   # 4 chars, 1 version, 2 length

const transforms = ([1 0; 0 1], [0 1; -1 0], [-1 0; 0 -1], [0 -1; 1 0],
                    [1 0; 0 -1], [0 1; 1 0], [-1 0; 0 1], [0 -1; -1 0])

const combines = Dict{Int, Function}(0 => x(p...) = sum(p...) / length(transforms),
                                     1 => x(p...) = prod(p...),
                                     2 => x(p...) = maximum(p...) - minimum(p...),
                                     3 => minimum,
                                     4 => maximum)
const combine_names = Dict{Int, ASCIIString}(0 => "average",
                                             1 => "product",
                                             2 => "range",
                                             3 => "max",
                                             4 => "min")

@enum Operation jump=0 kernel=1 addition=2 product=3 junk=4

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

immutable Index
    # indexing is simple for atoms - at level n there are
    # available+given_atom indices that can be used, where available
    # is i-1 (the number of entries below i) - see read_input.
    # for kernels, however, we are restricted to kernel enties.  so
    # 'available' depends on the number of kernels below, and indexing
    # is not linear.  to handle this, we construct these index tables,
    # which give the number of kernels below a given point and the
    # translation from input to direct index (both these include
    # given_kern).
    available::Vector{Int}
    index::Vector{Int}
end

function build_index(e::Expression)
    n = length(e.fragment)
    ok = zeros(Bool, n+given_atom)
    ok[1:given_kern] = true
    index = Index(zeros(Int, n), Int[1:given_kern;])
    for i = n:-1:1   # work through fragments in reverse
        index.available[i] = length(index.index) - given_kern
        if e.fragment[i].operation == kernel
            push!(index.index, given_kern + (n-i+1))
            ok[n-i+1 + given_atom] = true
        elseif e.fragment[i].operation == jump
            if ok[unpack_jump(e.fragment[i], n-i)]
                push!(index.index, given_kern + (n-i+1))
                ok[n-i+1 + given_atom] = true
            end
        elseif e.fragment[i].operation in (addition, product)
            for (input, scale, change) in unpack_arithmetic(e.fragment[i], n-i)
                if ok[input]
                    push!(index.index, given_kern + (n-i+1))
                    ok[n-i+1 + given_atom] = true
                    break
                end
            end
        end
    end
    index
end

function read_input(e::StatefulIterator{Vector{UInt8},Int}, available, given)
    # signed value
    input = read(e, Int8)
    n = given + available
    # abs(-128) = -128 for Int8
    index = abs(Int(input)) % n
    if input < 0
        # relative indexing for -ve values, -1 means next
        n - index
    else
        # absolute indexing for +ve values, 0 means bottom
        1 + index
    end
end

function unpack_jump(f::Fragment, available)
    masked = reinterpret(Int8, f.data[1] & 0x3f)
    # clunky, but allows same routine to be called
    # zero maps to -1
    read_input(StatefulIterator([reinterpret(UInt8, -masked-one(Int8))]), 
               available, given_atom)
end

# positive input is not handled correctly
function pack_jump(input)
    # -1 maps to zero
    n = UInt8((-input-1) & 0x3f)
    Fragment(jump, [n], [])
end

function unpack_kernel(f::Fragment, i, index)
    e = StatefulIterator(f.data)
    nx, ny = unpack_kernel_size(read(e))
    idx = read_input(e, index.available[i], given_kern)
    input = index.index[idx]
    edge = b2f(read(e, Int8))
    cy, cx = map(Int, [divrem(read(e) % (nx*ny), nx)...] + [1,1])
    combine = read(e) % length(combines)
    kernel = reshape([b2f(read(e, Int8)) for i in 1:nx*ny], nx, ny)
    (input, edge, (cx, cy), combine, kernel)
end

# input is not handled correctly
function pack_kernel(input, edge, c, combine, coeffs)
    cx, cy = c
    nx, ny = size(coeffs)
    data = [UInt8(nx-1) << 3 | UInt8(ny-1)]
    push!(data, UInt8(input-1), f2b(edge), UInt8((cy-1)*nx + cx-1), UInt8(combine))
    append!(data, reinterpret(UInt8, map(f2b, reshape(coeffs, nx*ny))))
    Fragment(kernel, data, [])
end

function unpack_arithmetic(f::Fragment, available)
    e = StatefulIterator(f.data)
    tag = read(e)
    n = unpack_arithmetic_size(tag)
    flags = ((tag >> 2) & 0x0f) << 1
    function term(e)
        input = read_input(e, available, given_atom)
        scale = b2f(read(e, Int8))
        change = flags & 0x01 == 0x01
        flags = flags >> 1
        (input, scale, change)
    end
    [term(e) for i in 1:n]
end

unpack_product = unpack_arithmetic
unpack_addition = unpack_arithmetic

# -ve input is not handled correctly
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
    n_bytes = read(d, UInt16)
    
    while !done(d)
        tag = peek(d)
        if tag & 0x80 == 0
            if tag & 0x40 == 0
                op = jump
                n = 1
            else
                op = kernel
                n = prod(unpack_kernel_size(tag)) + kernel_extra
            end
        else
            if tag & 0x40 == 0
                op = addition
                n = unpack_arithmetic_size(tag) * 2 + arith_extra
            else
                op = product
                n = unpack_arithmetic_size(tag) * 2 + arith_extra
            end
        end
        if n > available(d)
            f = Fragment(junk, read(d, available(d)), [])
        else
            f = Fragment(op, read(d, n), chunkend(d))
        end
        push!(e, f)
    end
    # this is all we support right now
    @assert e.version == 0x00
    @assert e.length == n_bytes
    @assert (e.length - lheader) % chunk == 0
    e
end

Expression(data::Vector{UInt8}) = unpack_expression(data)

function pack_expression(e::Expression)
    data = vcat(header, [0x00], [0x00, 0x00])
    for f in e.fragment
        fragment = vcat(f.data, f.padding)
        append!(data, fragment)
        # this is not needed when packing previously unpacked data,
        # but is when assembling a hand-written fragment
        n = length(data) - lheader
        if n % chunk != 0
            m = chunk - (n % chunk)
            append!(data, zeros(UInt8, m))
            append!(f.padding, zeros(UInt8, m))
            e.length += m
        end
    end
    # set length at end, with extra padding
    data[lheader-1:lheader] = reinterpret(UInt8, [e.length])
    @assert length(data) == e.length
    @assert (e.length - lheader) % chunk == 0
    data
end


# --- lazy evaluation


function lookup{N}(f, x, y, e, d::Array{Int8, 3}, input, edge, p::Position{N}, t::Point, index::Index)
    
    if input == 4
        if p.stats.moves == 0
            Float32(0.5)
        elseif isnull(p.stats.prev)
            zero(Float32)
        else
            one(Float32)
        end
    elseif input == 5
        zero(Float32)
    elseif input == 6
        one(Float32)
    elseif input == 7
        Float32(p.stats.score * Int(t))
    elseif input == 8
        Float32(p.stats.owned / (N*N - p.stats.stones))
    elseif input == 9
        p.stats.stones
    elseif 1 <= x <= N && 1 <= y <= N
        if input == 1
            # -1 for "our" colour, 0 for space, 1 for opponent's colour
            Float32(-1 * Int(t) * Int(point(p, x, y)))
        elseif input == 2
            # distance to nearest stone (-ve for opponent's colour)
            Float32(Int(t) * p.flood.distance[x, y])
        elseif input == 3
            # -1 if owned by us, 1 owned by opponent, 0 otherwise
            b = p.space.border[x, y]
            if b == 0 || b == 3
                zero(Float32)
            elseif b == border_mask(t)
                -one(Float32)
            else
                one(Float32)
            end
        elseif input == 10
            i = p.groups.index[x, y]
            if i > 0
                Float32(p.groups.size[i])
            else
                edge
            end
        elseif input == 11
            i = p.groups.index[x, y]
            if i > 0
                Float32(p.groups.lives[i])
            else
                edge
            end
        elseif input == 12
            m = (N+1) / 2
            dx = abs(m - x)
            dy = abs(m - y)
            (dx + dy) / N
        elseif input == 13
            dx = min(x, N+1-x)
            dy = min(y, N+1-y)
            2 * (min(dx, dy) - 1) / N
        elseif input == 14
            2 * min(abs(x-y), abs(N+1-x-y)) / N
        else
            i = input-given_atom
            e[i] || evaluate(f, length(f)-i+1, p, t, e, d, index)
            b2f(d[x, y, i])
        end
    elseif 0 <= x <= N+1 && 0 <= y <= N+1
        edge
    else
        0
    end
end

function evaluate_jump{N}(f::Vector{Fragment}, idx, p::Position{N}, t::Point, e, d::Array{Int8, 3}, index::Index)
    n = length(f)
    input = unpack_jump(f[idx], n-idx)
    @forall i j N begin
        d[i, j, n-idx+1] = f2b(lookup(f, i, j, e, d, input, 0.0, p, t, index))
    end
    e[n-idx+1] = true
end

function evaluate_kernel{N}(f::Vector{Fragment}, idx, p::Position{N}, t::Point, e, d::Array{Int8, 3}, index::Index)
    n, nt = length(f), length(transforms)
    input, edge, (cx, cy), combine, coeffs = unpack_kernel(f[idx], idx, index)
    nx, ny = size(coeffs)
    my_acc = zeros(Float32, N, N, nt)
    @forall i j N begin
        for k in 1:nt
            for di in 1:nx
                for dj in 1:ny
                    ddi, ddj = [di-cx dj-cy] * transforms[k]
                    # the best way to understand this is to draw a picture.
                    # it's basically a coord change from one frame (coeffs)
                    # to the other (data).
                    my_acc[i,j,k] += coeffs[di, dj] * lookup(f, i+ddi, j+ddj, e, d, input, edge, p, t, index)
                end
            end
        end
    end
    d[1:end, 1:end, n-idx+1] = map(f2b, combines[combine](my_acc, 3))
    e[n-idx+1] = true
end

function evaluate_arithmetic{N}(f::Vector{Fragment}, idx, p::Position{N}, t::Point, e, d::Array{Int8, 3}, g, index::Index)
    n = length(f)
    coeffs = unpack_addition(f[idx], n-idx)
    my_acc = zeros(Float32, N, N)
    for (input, scale, change) in coeffs
        @forall i j N begin
            value = lookup(f, i, j, e, d, input, 0.0, p, t, index)
            my_acc[i, j] += scale * (change ? g(value) : value)
        end
    end
    @forall i j N begin
        d[i, j, n-idx+1] = f2b(my_acc[i, j] / sqrt(length(coeffs)))
    end
    e[n-idx+1] = true
end

function evaluate(f::Vector{Fragment}, i, p::Position, t::Point, e, d::Array{Int8, 3}, index::Index)
    fragment = f[i]
    if fragment.operation == jump
        evaluate_jump(f, i, p, t, e, d, index)
    elseif fragment.operation == kernel
        evaluate_kernel(f, i, p, t, e, d, index)
    elseif fragment.operation == addition
        evaluate_arithmetic(f, i, p, t, e, d, x -> sin(pi * x / 128), index)
    elseif fragment.operation == product
        evaluate_arithmetic(f, i, p, t, e, d, x -> 1/x, index)
    end
end

function evaluate{N}(e::Expression, p::Position{N}, t::Point)
    index = build_index(e)
    n = length(e.fragment)
    evaluated = zeros(Bool, n)
    output_data = zeros(Int8, N, N, n)
    evaluate(e.fragment, 1, p, t, evaluated, output_data, index)
    # output is final frame (most complex)
    map(b2f, output_data[:,:,n])
end

function evaluate(e::Array{UInt8, 1}, p::Position, t::Point)
    evaluate(Expression(e), p, t)
end


# --- move extraction


# the above generates a matrix of 'values' that can be positive or
# negative.  the best interpretation i can give to that is log(prob).
# and in a sense i get to choose, because if i decide that and evolve
# on that basis, then that is what i get (in an ideal world).

# however, it's damn spiky.  so any random sampling will be dominated
# by the largest numbers.  so instead, we just pick off the largest
# scoring locations (and then exclude invalid moves etc).

function moves{N}(e::Array{UInt8, 1}, h::Vector{Position{N}}, t::Point)
    p = h[end]
    logp = evaluate(e, p, t)
    indexed = reshape([(logp[i, j], (i, j)) for i in 1:N, j in 1:N], N*N)
    positive = filter(x -> x[1] > 0, indexed)
    possible = filter(x -> valid(h, t, x[2]...), positive)
    m = map(x -> x[2], sort(possible; by=x -> x[1], rev=true))
    if p.stats.moves == 0
        r = hex2bytes(name(e))[1]
        t = transforms[1 + (r % length(transforms))]
        o = [Int((N+1) / 2) Int((N+1) / 2)]
        function transform(xy)
            xy2 = hcat(xy...)
            xy3 = o + ((xy2 - o) * t)
            tuple(xy3...)
        end
        m = map(transform, m)
    end
    m
end


# --- analysis

const lookup_dict = Dict{Int,ASCIIString}(5 => "zero",
                                          6 => "one",
                                          7 => "score",
                                          8 => "owned%",
                                          9 => "stones%",
                                          1 => "point",
                                          2 => "flood",
                                          3 => "owner",
                                          4 => "prev",
                                          10 => "size",
                                          11 => "lives",
                                          12 => "centre",
                                          13 => "edge",
                                          14 => "diag")

function lookup_name(input, n, given)
    if input > given
        n-(input - given)+1
    else
        lookup_dict[input]
    end
end

int(x) = typeof(x) <: Integer

function dump_jump(i, f)
    n = length(f)
    input = lookup_name(unpack_jump(f[i], n-i), n, given_atom)
    println(" $i jump to $(input)")
    filter(int, [input])
end

function cell(value, lo, hi, symbols)
    if value <= lo
        symbols[1]
    elseif value >= hi
        symbols[3]
    else
        symbols[2]
    end
end

function sketch_kernel(kernel, cx, cy)
    nx, ny = size(kernel)
    ord = sort(reshape(kernel, nx*ny))
    lo = nx*ny >=9 ? ord[cld(length(ord), 3)] : ord[1]
    hi = nx*ny >=9 ? ord[length(ord) - fld(length(ord), 3)] : ord[end]
    for j in 1:ny
        for i in 1:nx
            if i == cx && j == cy
                print(cell(kernel[i,j], lo, hi, "O.@"))
            else
                print(cell(kernel[i,j], lo, hi, "- +"))
            end
        end
        println()
    end
end

function dump_kernel(i, f, index)
    (input, edge, (cx, cy), combine, kernel) = unpack_kernel(f[i], i, index)
    input = lookup_name(input, length(f), given_kern)
    println(" $i kernel($(combine_names[combine]), $(input))")
    sketch_kernel(kernel, cx, cy)
    filter(int, [input])
end

term2str(n, input, scale, change) = string("$(scale)*$(lookup_name(input, n, given_atom))", change ? "!" : "")

function dump_arithmetic(i, f, op)
    n = length(f)
    terms = unpack_arithmetic(f[i], n-i)
    expr = join(map(x -> term2str(n, x...), terms), " $op ")
    println(" $i $expr")
    filter(int, map(x -> lookup_name(x[1], n, given_atom), terms))
end

function dump_fragment(i, f, used, index)
    if f[i].operation == jump
        refs = dump_jump(i, f)
    elseif f[i].operation == kernel
        refs = dump_kernel(i, f, index)
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
    index = build_index(e)
    used = Set([1])
    for (i, fragment) in collect(enumerate(e.fragment))
        if i in used
            dump_fragment(i, e.fragment, used, index)
        end
    end
end

dump_expression(e::Vector{UInt8}) = dump_expression(unpack_expression(e))
