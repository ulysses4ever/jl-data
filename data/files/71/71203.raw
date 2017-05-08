# `UnionFinder{T <: Integer}` is a graph containing a constant number of nodes
# which allows for union-find operations. All nodes are indexed by an integer
# of type `T` which is between 1 an the number of internal nodes.
type UnionFinder{T <: Integer}
    sizes :: Array{T}
    parents :: Array{T}

    # `UnionFinder(nodes)` returns a `UnionFinder` with `nodes` unconnected
    # internal nodes.

    function UnionFinder(nodes :: T)
        if nodes <= 0
            throw(ArgumentError())
        end
        
        uf = new(Array(T, nodes), Array(T, nodes))
        reset(uf)
        
        return uf
    end
end


# `reset(uf)` disconnects all the nodes within `uf`.
function reset(uf :: UnionFinder)
    for i in 1:length(uf.parents)
        uf.sizes[i] = 1
        uf.parents[i] = i
    end
end


# `union(uf, iterator)` iterates through `iterator` which returns integer
# edges, (`u`, `v`), and connects them within `uf`. `u` and `v` must be valid
# node indices for `uf`.
function union!{T <: Integer}(uf :: UnionFinder{T}, iterator)
    for (u, v) in iterator
        union!(uf, u, v)
    end
end


# `union(uf, us, vs)` connects nodes within `uf` which are bridged by
# the edges (`us[i]`, `vs[i]`). All values in `us` and `vs` must be valid node
# indices for `uf` and `us` and `vs` must be the same length.
function union!{T <: Integer}(uf :: UnionFinder{T}, 
                              us :: Array{T}, vs :: Array{T})
    if length(us) != length(vs)
        throw(ArgumentError())
    end

    for i in 1:length(us)
        union!(uf, us[i], vs[i])
    end
end


# `union(uf, idx1, idx2)` connects the nodes within `uf` with indices
# `idx1` and `idx2`. `idx1` and `idx2` must be valid indices into `uf`.
function union!{T <: Integer}(uf :: UnionFinder{T}, idx1 :: T, idx2 :: T)
    if idx1 > length(uf.parents) || idx1 <= 0
        throw(ArgumentError())
    elseif idx2 > length(uf.sizes) || idx2 <= 0
        throw(ArgumentError())
    end

    root1 = find(uf, idx1)
    root2 = find(uf, idx2)

    # TODO: Test whether using rank or using size is better for performance.
    if uf.sizes[root1] < uf.sizes[root2]
        uf.parents[root1] = root2
        uf.sizes[root2] += uf.sizes[root1]
    else
        uf.parents[root2] = root1
    end
end


# `find(uf, node)` returns the group ID of `node`. `node` must be a valid
# index into `uf`.
function find!{T <: Integer}(uf :: UnionFinder{T}, node :: T)
    if node > length(uf.parents) || node <= 0
        throw(ArgumentError())
    end

    if uf.parents[node] != uf.parents[uf.parents[node]]
        compress!(uf, node)
    end
    return uf.parents[node]
end


# `compress(uf, node)` compresses the internal parental node tree so that
# all nodes between `node` and the root of its group will point directly to the
# root. `node` must be a valid index into `uf`.
function compress!{T <: Integer}(uf :: UnionFinder{T}, idx :: T)
    if node > length(uf.parents) || node <= 0
        throw(ArgumentError())
    end

    child = node
    parent = uf.parents[child]

    while child != parent
        child = parent
        parent = uf.parents[child]
    end
    root = child

    child = node
    parent = uf.parents[child]

    while grandparent != parent
        child = parent
        parent = uf.parents[child]
        uf.parents[child] = root
    end
end


# `nodes(uf)` returns the number of nodes in `uf`.
function nodes(uf :: UnionFinder)
    return length(uf.parents)
end


# `size!(uf, node)` returns the size of the group containing `node`.
function size!{T <: Integer}(uf :: UnionFinder{T}, node :: T)
    return uf.sizes[find!(uf, node)]
end
