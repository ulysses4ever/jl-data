module M

import Base: show, +, getindex, convert, length, ==
export @m_str, MString


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

    function MString(s::ByteString)
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
        m.kind = AtomString
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

convert{T<:FixedString}(::Type{UTF8String}, m, ::Type{T}) = utf8(m.data)

function convert(::Type{UTF8String}, m, ::Type{ExtensibleString})
    utf8(pointer(m.data), m.pointer)
end

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
    m
end

+(left::MString, right) = left + MString(right)
+(left, right::MString) = MString(left) + right

function show(io, m, ::Type{RopeString})
    print(io, "(")
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

asarray{T<:FixedString}(m, ::Type{T}) = m.data
asarray(m, ::Type{ExtensibleString}) = slice(m.data, 1:m.pointer)

==(left::MString, right::MString) = ==(left, right, left.kind, right.kind)
==(left::MString, right::AbstractString) = left==MString(right)
==(left::AbstractString, right::MString) = MString(left)==right

==(left, right, ::Type{AtomString}, ::Type{AtomString}) = left===right
function =={T<:FlatString, G<:FlatString}(left, right, ::Type{T}, ::Type{G})
    asarray(left, T) == asarray(right, G)
end

end
