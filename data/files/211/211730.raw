module PersistentArrays

# package code goes here

"""
The version (V) / value (T) pairs are in
the reverse order of the Node{T,V} for sorting
of the pairs by version.
"""
type Node{T,V}
    versions::AbstractArray{Pair{V,T}}
end

Node{T,V}(val::T, version::V) = Node{T,V}(
    [Pair{V,T}(version, val)]
)
Base.show(io::IO, n::Node) = print(io, "$(n.versions)")

latest(n::Node) = n.versions[end][2]
function lookup{T,V}(n::Node{T,V}, version::V)
    # println(n.versions)
    index = searchsortedlast(n.versions, Pair(version, zero(T)), by=first)
    # println("version: $version, index: $index")

    if index > 0
        return n.versions[index][2]
    else
        error("A version <= ($version) not found")
    end
end

function update!{T,V}(n::Node{T,V}, x::T, version::V)
    new_version = Pair(version, x)

    indices = searchsorted(n.versions, new_version)
    @assert length(indices) <= 1
    if isempty(indices)
        insert!(n.versions, first(indices), new_version)
    else
        n.versions[indices[1]] = new_version
    end
end


type PersistentArray{T,N} <: AbstractArray{T,N}
    data::AbstractArray{Node,N}
    version
end

function PersistentArray{T,V}(dims::Int...; default_value::T=0.0, default_version::V=0)
    a = Array{Node{T,V}, length(dims)}(dims...)
    map(
        i -> a[i] = Node(default_value, default_version),
        eachindex(a)
    )
    PersistentArray{Node{T,V},length(dims)}(a, increment(default_version))
end

function Base.show(array::PersistentArray)
    print("PersistentArray(version=$(array.version), data=")
    show(array.data)
    print(")")
end

version(array::PersistentArray) = array.version
commit!(array::PersistentArray) = array.version = increment(array.version)
increment(x::Int) = x + 1

function update!{T,V}(array::PersistentArray{Node{T,V}}, x::T, version::V, idx...)
    subarray = sub(array.data, idx...)
    for i in subarray
        update!(i, x, version)
    end
end


function lookup{T,V}(array::PersistentArray{Node{T,V}}, version::V, idx...)
    map(
        i -> lookup(i, version),
        sub(array.data, idx...)
    )
end

function Base.getindex{T,V}(array::PersistentArray{Node{T,V}}, idx...)
    result = map(
        i -> latest(i),
        sub(array.data, idx...)
    )
    if length(result) == 1
        return result[1]
    else
        return result
    end
end

function Base.setindex!{T,V}(array::PersistentArray{Node{T,V}}, x::T, idx...)
    update!(array, x, array.version, idx...)
end

# Required for subtype of AbstractArray
Base.size(array::PersistentArray, idx::Int...) = size(array.data, idx...)
Base.linearindexing{T<:PersistentArray}(::Type{T}) = Base.LinearFast()
#Base.ndims(array::PersistentArray) = ndims(array.data)


export PersistentArray, version, lookup, update!, commit!, increment
end # module
