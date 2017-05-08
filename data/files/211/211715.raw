"""
`PersistentArray{T,N}` wraps an Array{Node, N} to
provide a versioned array interface. The Node type
maintains a history of each element, so the complexity
of each operation on the PersistentArray is dependent on
the corresponding Node operation in relation to the number
of stored versions.
"""
type PersistentArray{T,N} <: AbstractArray{T,N}
    data::AbstractArray{Node,N}
    version
end

"""
`PersistentArray{V,T}(dimss::Int...; default_value::T=0.0, default_version::V=1)`
builds a persistent array where each Node contains 1 version
(default_version, default_value).
"""
function PersistentArray{V,T}(dims::Int...; default_value::T=0.0, default_version::V=1)
    a = Array{Node{V,T}, length(dims)}(dims...)
    map(
        i -> a[i] = Node(default_version, default_value),
        eachindex(a)
    )
    PersistentArray{Node{V,T},length(dims)}(a, default_version)
end

"""
`Base.show(array::PersistentArray)` prints out the array version and data.

NOTE: this doesn't get used by the REPL for some reason.
"""
function Base.show(array::PersistentArray)
    print("PersistentArray(version=$(array.version), data=")
    show(array.data)
    print(")")
end

"`version(array::PersistentArray)` prints the current array version."
version(array::PersistentArray) = array.version

"`commit!(array::PersistentArray` increments the array version."
commit!(array::PersistentArray) = array.version = increment(array.version)

"`increment(x::Int)` provides the increment method for ints (default version type)"
increment(x::Int) = x + 1

"""
`update!{V,T}(array::PersistentArray{Node{V,T}}, x::T, version::V, idx...)`
updates or adds the version with the specifid value for each element specified
by `idx`. Runs in O(mlog(m)) time for each element selected where m is the
number of versions.
"""
function update!{V,T}(array::PersistentArray{Node{V,T}}, x::T, version::V, idx...)
    map(
        i -> update!(i, x, version),
        sub(array.data, idx...)
    )
end

"""
`lookup{V,T}(array::PersistentArray{Node{V,T}}, version::V, idx...)` looks up the
appropriate element selected at the given `version`. Runs in O(log(m)) for each element
selected where m is the number of versions.
"""
function lookup{V,T}(array::PersistentArray{Node{V,T}}, version::V, idx...)
    map(
        i -> lookup(i, version),
        sub(array.data, idx...)
    )
end

"""
`getindex{V,T}(array::PersistentArray{Node{V,T}}, idx...)` returns the
current version of all elements selected. Runs in O(1) for each element.
"""
function Base.getindex{V,T}(array::PersistentArray{Node{V,T}}, idx...)
    result = map(
        i -> getlatest(i),
        sub(array.data, idx...)
    )
    if length(result) == 1
        return result[1]
    else
        return result
    end
end

"""
`setindex!{V,T}(array::PersistentArray{Node{V,T}}, x::T, idx...)`
sets the current version of every node selected. If the node doesn't have a
current version it is added. Runs in O(m) time for each element where
m is the number of versions.
"""
function Base.setindex!{V,T}(array::PersistentArray{Node{V,T}}, x::T, idx...)
    map(
        i -> setlatest!(i, x, array.version),
        sub(array.data, idx...)
    )
end

# Required for subtype of AbstractArray
Base.size(array::PersistentArray, idx::Int...) = size(array.data, idx...)
Base.linearindexing{T<:PersistentArray}(::Type{T}) = Base.LinearFast()
#Base.ndims(array::PersistentArray) = ndims(array.data)
