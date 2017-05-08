# `UnionFinder{T <: Integer}` is a graph containing a constant number of nodes
# which allows for union-find operations. All nodes are indexed by an integer
# of type `T` which is between 1 an the number of internal nodes.
type UnionFinder{T <: Integer}
    sizes :: Array{T}
    parents :: Array{T}
end


# `UnionFinder(nodes)` returns a `UnionFinder` with `nodes` unconnected
# internal nodes.
function UnionFinder{T <: Integer}(nodes :: T)
    if nodes <= 0
        throw(ArgumentError("Non-positive nodes, $nodes."))
    end
    
    uf = UnionFinder(Array(T, nodes), Array(T, nodes))
    reset!(uf)
    
    return uf
end


# `reset(uf)` disconnects all the nodes within `uf`.
function reset!(uf :: UnionFinder)
    for i in 1:length(uf.parents)
        uf.sizes[i] = 1
        uf.parents[i] = i
    end
end


# `union!(uf, iterator)` iterates through `iterator` which returns integer
# edges, (`u`, `v`), and connects them within `uf`. `u` and `v` must be valid
# node indices for `uf`.
function union!{T <: Integer}(uf :: UnionFinder{T}, iterator)
    for (u, v) in iterator
        union!(uf, u, v)
    end
end


# `union!(uf, us, vs)` connects nodes within `uf` which are bridged by
# the edges (`us[i]`, `vs[i]`). All values in `us` and `vs` must be valid node
# indices for `uf` and `us` and `vs` must be the same length.
function union!{T <: Integer}(uf :: UnionFinder{T}, 
                              us :: Array{T}, vs :: Array{T})
    if length(us) != length(vs)
        throw(ArgumentError("us and vs not of the same length."))
    end

    for i in 1:length(us)
        union!(uf, us[i], vs[i])
    end
end


# `union!(uf, edges)` conncts all nodes within `uf` which are bridged by an
# edge within `edges`. All edge vertices must be valid node indices.
function union!{T <: Integer}(uf :: UnionFinder{T}, edges :: Array{(T, T)})
    for (u, v) in edges
        union!(uf, u, v)
    end
end


# `union!(uf, node1, node2)` connects the nodes within `uf` with indices
# `node1` and `node2`. `node1` and `node2` must be valid indices into `uf`.
function union!{T <: Integer}(uf :: UnionFinder{T}, node1 :: T, node2 :: T)
    if node1 > length(uf.parents) || node1 <= 0
        throw(ArgumentError("node1, $node1, is out of range."))
    elseif node2 > length(uf.sizes) || node2 <= 0
        throw(ArgumentError("node2, $node2, is out of range."))
    end

    root1 = find!(uf, node1)
    root2 = find!(uf, node2)

    # TODO: Test whether using rank or using size is better for performance.
    if root1 == root2
        return
    elseif uf.sizes[root1] < uf.sizes[root2]
        uf.parents[root1] = root2
        uf.sizes[root2] += uf.sizes[root1]
    else
        uf.parents[root2] = root1
        uf.sizes[root1] += uf.sizes[root2]
    end
end


# `find!(uf, node)` returns the group ID of `node`. `node` must be a valid
# index into `uf`.
function find!{T <: Integer}(uf :: UnionFinder{T}, node :: T)
    if node > length(uf.parents) || node <= 0
        throw(ArgumentError("$node out of range for UnionFinder."))
    end

    if uf.parents[node] != uf.parents[uf.parents[node]]
        compress!(uf, node)
    end
    return uf.parents[node]
end


# `compress!(uf, node)` compresses the internal parental node tree so that
# all nodes between `node` and the root of its group will point directly to the
# root. `node` must be a valid index into `uf`.
#
# Not publicly exported.
function compress!{T <: Integer}(uf :: UnionFinder{T}, node :: T)
    child = node
    parent = uf.parents[child]

    while child != parent
        child = parent
        parent = uf.parents[child]
    end
    root = child

    child = node
    parent = uf.parents[child]
    uf.parents[child] = root

    while child != parent
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
