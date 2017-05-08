function bfs(adj::Array{Set{Int64}}, node_index::Int64)
    seen = Set{Int64}()
    to_traverse = Int64[]

    push!(to_traverse, node_index)
    push!(seen, node_index)

    while length(to_traverse) > 0
        t = pop!(to_traverse)

        for vertex in adj[t]
            if in(vertex, seen) == false
                push!(to_traverse, vertex)
                push!(seen, vertex)
            end
        end
    end
    return seen
end


#number of connectex components in a graph
function connected_components(g::Graph)
    seen_set = Set{Int64}()
    components = Set{Int64}[]

    for vertex in index_iter(g)
        if in(vertex, seen_set) == false
            c = bfs(g.adj, vertex)
            push!(components, c)
            union!(seen_set, c)
        end
    end
    return sort(components, by = x -> length(x), rev = true)
end