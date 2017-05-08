"""
`Node{V,T}` simply maintains an ordered array of
Pairs (version, value) representing the history
of the node.

NOTE: Changes to the complexity cost of the
PersistentArray is a result of the complexity of the
operation being performed on the node in relation to m
where m is the number of versions of the given node.
"""
type Node{V,T}
    versions::AbstractArray{Pair{V,T}}
end

"""
`Node{V,T}(version::V, val::T)` is the only
Node constructor. The version and val given
represent the initial Pair in the version history.
"""
function Node{V,T}(version::V, val::T)
    Node{V,T}(
        [Pair{V,T}(version, val)]
    )
end

"""
`Base.show(io::IO, n::Node)` just prints the version history.
"""
Base.show(io::IO, n::Node) = print(io, "$(n.versions)")


"""
`getlatest(n::Node)` simply gets the latest node version.
This can be done in O(1) time since the versions are stored
in sorted order.
"""
getlatest(n::Node) = n.versions[end][2]

"""
`setlatest!{V,T}(n::Node{V,T}, x::T, version::V) either overwrites
the latest version if the provided version matches or pushes a new
version Pair (version, x) in the version history. This is a O(m)
operation due to the potential `push!` operation on the version history
array of m elements. If `version` is less than the latest element in
this history an error will be thrown.
"""
function setlatest!{V,T}(n::Node{V,T}, x::T, version::V)
    new_version = Pair(version, x)

    if n.versions[end][1] == version
        n.versions[end] = new_version
    elseif n.versions[end][1] < version
        push!(n.versions, new_version)
    else
        error("
            The version given is not >= the latest
            ($(n.versions[end][1])). Please use `update!` to overwrite
            previous versions"
        )
    end
end

"""
`lookup{V,T}(n::Node{V,T}, version::V)` does a binary search on the versions
array and returns the value for the most recent version that is <= `version`.
Runs in O(log(m)) where m is the number of elements in the history
"""
function lookup{V,T}(n::Node{V,T}, version::V)
    index = searchsortedlast(n.versions, Pair(version, zero(T)), by=first)

    if index > 0
        return n.versions[index][2]
    else
        error("A version <= ($version) not found")
    end
end

"""
`update!{V,T}(n::Nodes{V,T}, x::T, version::V)` does a binary search
on the versions array to locate the existing (or insertion) position.
If that version doesn't exist yet a new Pair (version, x) is inserted
at the appropriate position, otherwise the existing version is overwritten.
Runs in O(mlog(m)) where m is the number of elements int the history.
"""
function update!{V,T}(n::Node{V,T}, x::T, version::V)
    new_version = Pair(version, x)

    indices = searchsorted(n.versions, new_version)
    @assert length(indices) <= 1
    if isempty(indices)
        insert!(n.versions, first(indices), new_version)
    else
        n.versions[indices[1]] = new_version
    end
end
