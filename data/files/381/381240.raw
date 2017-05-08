module M

import Base: show, +, getindex
export MString

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

    function MString(s::AbstractString)
        m = new()
        m.kind = FixedString
        m.data = s.data
        m
    end

    MString() = new()
end

abstract BaseString
abstract LinearString <:BaseString
abstract RopeString <: BaseString
abstract DependentString <: LinearString
abstract FlatString <: LinearString
abstract FixedString <: FlatString
abstract ExtensibleString <: FlatString

show(io::IO, m::MString) = show(io, m, m.kind)

show(io, m, ::Type{FixedString}) = show(io, utf8(m))
function show(io, m, ::Type{DependentString})
    print(io, "Dependent ($(m.offset), $(m.length)) of ")
    show(io, m.backing)
end

function Base.convert(::Type{UTF8String}, m::MString)
    ensureflat(m)
    utf8(m.data)
end

ensureflat(m::MString) = ensureflat(m, m.kind)

ensureflat{T<:FlatString}(m, ::Type{T}) = m

function ensureflat(m, ::Type{DependentString})
    ensureflat(m.backing)
    m.data = m.backing.data[(m.offset+1):(m.offset+m.length)]
    m.kind = FixedString
    m
end

function ensureflat(m, ::Type{RopeString})
    ensureflat(m.left)
    ensureflat(m.right)
    m.data = vcat(m.left.data, m.right.data)
    m.kind = FixedString
    m
end

function +(left::MString, right::MString)
    m = MString()
    m.kind = RopeString
    m.left, m.right = left, right
    m
end

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


end
