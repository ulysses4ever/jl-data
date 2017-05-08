# `CompressedFinder{T <: Integer}` is an optimized variant of UnionFinder{T}
# which does not support the addition of more edges. `CompressedFinder` also
# tracks the number of groups in the graph and garuantees that all group IDs
# will be between 1 and the total group number, inclusive.
type CompressedFinder{T <: Integer}
    ids :: Array{T}
    groups :: T
end


# `CompressedFinder(uf)` creates a `CompressedFinder` instance from the 
# groups within `uf`.
function CompressedFinder{T <: Integer}(uf :: UnionFinder{T})
    groups = zero(T)
    ids = zeros(T, length(uf.parents))
    
    for i in 1:length(uf.parents)
        root = find!(uf, i)
        if ids[root] == 0
            groups += 1
            ids[root] = groups
        end
        ids[i] = ids[root]
    end
    
    return CompressedFinder(ids, groups)
end


# `find(cf, node)` returns the group ID of `node`. `node` must be a valid
# index into `uf`.
function find{T <: Integer}(cf :: CompressedFinder{T}, node :: T)
    if node <= 0 || node > length(cf.ids)
        throw(ArgumentError("Node $d is out of range for CompressedFinder."))
    end

    return cf.ids[node]
end


# `nodes(uf)` returns the number of nodes in `cf`.
function nodes(cf :: CompressedFinder)
    return length(cf.ids)
end


# `groups(cf)` returns the number of groups in `cf`.
function groups(cf :: CompressedFinder)
    return cf.groups
end
