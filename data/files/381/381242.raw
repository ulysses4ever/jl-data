module M

import Base: show, +, getindex, convert, length, ==
export @m_str, MString

const INLINE_SIZE=8

type MString <: AbstractString
    kind::DataType

    # Depedenent
    backing::MString
    offset::Int
    length::Int

    # Fixed
    data::Vector{UInt8}

    # Rope
    left::MString
    right::MString

    # Extensible
    pointer::Int

    # Inline
    inline::NTuple{INLINE_SIZE, UInt8}

    function MString{N}(s::NTuple{N, UInt8})
        N > INLINE_SIZE && error("Tuple too big ($N vs $INLINE_SIZE)")
        m = new()
        m.kind = InlineString
        m.length = N
        d = zeros(UInt8, INLINE_SIZE)
        d[1:N] = [s...]
        m.inline = (d...)
        m
    end

    function MString(s::ByteString)
        if length(s) ≤ INLINE_SIZE
            return MString((s.data...))
        end
        get(ATOMS, hash(s.data)) do
            m = new()
            m.kind = FixedString
            m.data = s.data
            m
        end
    end

    MString() = new()
end

MString(s::AbstractString) = MString(utf8(s))


const ATOMS = Dict{UInt64, MString}()


macro m_str(s)
    get!(ATOMS, hash(s.data)) do
        m = MString(s)
        if m.kind == InlineString
            m.kind = InlineAtomString
        else
            m.kind = AtomString
        end
        m
    end
end

abstract BaseString
abstract LinearString <:BaseString
abstract RopeString <: BaseString
abstract DependentString <: LinearString
abstract FlatString <: LinearString
abstract FixedString <: FlatString
abstract ExtensibleString <: FlatString
abstract AtomString <: FixedString
abstract InlineString <: FixedString
abstract InlineAtomString <: InlineString
typealias IsAtom Union{InlineAtomString, AtomString}

show(io::IO, m::MString) = show(io, m, m.kind)

show{T<:FlatString}(io, m, ::Type{T}) = show(io, utf8(m))

function show(io, m, ::Type{DependentString})
    print(io, "Dependent ($(m.offset), $(m.length)) of ")
    show(io, m.backing)
end

convert(::Type{UTF8String}, m::MString) = convert(UTF8String, m, m.kind)

function convert{T<:BaseString}(::Type{UTF8String}, m, ::Type{T})
    ensureflat(m)
    convert(UTF8String, m)
end

convert{T<:FixedString}(::Type{UTF8String}, m, ::Type{T}) = utf8(asarray(m, T))


ensureflat(m::MString) = ensureflat(m, m.kind)

ensureflat{T<:FlatString}(m, ::Type{T}) = m

function ensureflat(m, ::Type{DependentString})
    backing, offset, length = m.backing, m.offset, m.length
    while backing.kind == DependentString
        if length > backing.length
            error("Too long")
        end
        offset += backing.offset
        backing = backing.backing
    end
    ensureflat(backing)
    m.data = backing.data[(offset+1):(offset+length)]
    m.kind = FixedString
    m
end

function buffersize(n)
    exp = floor(Int, log2(n)) + 1
    2^exp
end

length(m::MString) = length(m, m.kind)::Int

length(m::MString, ::Type{RopeString}) = length(m.left) + length(m.right)
length{T<:FixedString}(m::MString, ::Type{T}) = length(m.data)
length(m::MString, ::Type{ExtensibleString}) = m.pointer
length(m::MString, ::Type{DependentString}) = m.length
length{T<:InlineString}(m::MString, ::Type{T}) = m.length
length(m::MString, ::Type{RopeString}) = m.length + length(m.right)

function ensureflat(m, ::Type{RopeString})
    ensureflat(m.left)
    ensureflat(m.right)
    ll = length(m.left)
    lr = length(m.right)
    outlength = ll + lr
    if m.left.kind == ExtensibleString && length(m.left.data) > outlength
        m.data = m.left.data
        unsafe_copy!(m.data, ll+1, m.right.data, 1, lr)
        m.pointer = outlength
    else
        m.data = Vector{UInt8}(buffersize(outlength))
        info("Resized to $(length(m.data))")
        unsafe_copy!(m.data, 1, m.left.data, 1, ll)
        unsafe_copy!(m.data, ll+1, m.right.data, 1, lr)
        m.pointer = outlength
    end
    m.kind = ExtensibleString
    m
end

function +(left::MString, right::MString)
    m = MString()
    m.kind = RopeString
    m.left, m.right = left, right
    m.length = length(m.left)
    m
end

+(left::MString, right) = left + MString(right)
+(left, right::MString) = MString(left) + right

function show(io, m, ::Type{RopeString})
    print(io, "Rope(")
    show(io, m.left)
    print(io, ", ")
    show(io, m.right)
    print(io, ")")
end


function getindex(backing::MString, r::UnitRange{Int})
    offset = r.start-1
    length = r.stop - r.start + 1
    m = MString()
    m.kind = DependentString
    m.backing, m.offset, m.length = backing, offset, length
    m
end

getindex(m::MString, idx::Int) = getindex(m, m.kind, idx)::Char
getindex{T<:FlatString}(m, ::Type{T}, idx) = Char(m.data[idx])
getindex{T<:InlineString}(m, ::Type{T}, idx) = Char(m.inline[idx])
function getindex{T<:RopeString}(m, ::Type{T}, idx)
    if idx ≤ m.length
        m.left[idx]
    else
        m.right[idx - m.length]
    end
end
function getindex{T<:DependentString}(m, ::Type{T}, idx)
    m.backing[idx + m.offset]
end


asarray{T<:FixedString}(m, ::Type{T}) = m.data
asarray(m, ::Type{ExtensibleString}) = slice(m.data, 1:m.pointer)
asarray{T<:InlineString}(m, ::Type{T}) = [m.inline[1:m.length]...]

==(left::MString, right::MString) = ==(left, right, left.kind, right.kind)
==(left::MString, right::AbstractString) = left==MString(right)
==(left::AbstractString, right::MString) = MString(left)==right

=={T<:IsAtom, G<:IsAtom}(left, right, ::Type{T}, ::Type{G}) = left===right
=={T<:InlineString, G<:InlineString}(left, right, ::Type{T}, ::Type{G}) = left.inline == right.inline && left.length == right.length

function =={T<:FlatString, G<:InlineString}(left, right, ::Type{G}, ::Type{T})
    N = length(left, InlineString)
    N == length(right, T) || return false
    for i=1:N
        left.inline[i] == right.data[i] || return false
    end
    true
end

=={T<:FlatString, G<:InlineString}(left, right, ::Type{T}, ::Type{G}) = right==left

function =={T<:FlatString, G<:FlatString}(left, right, ::Type{T}, ::Type{G})
    asarray(left, T) == asarray(right, G)
end

function Base.match(r::Regex, m::MString, offset=0)
    match(r, utf8(m), offset)
end

end
