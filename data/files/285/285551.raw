module ReverseSearch

export reverse_search_producer, ReverseSearchParams

VERSION < v"0.4-" && using Docile

type ReverseSearchParams
    adj
    max_degere
    sink
    f
end

@doc doc"""
Equivalent to calling

    reverse_search_producer(p.adj, p.max_degree, p.sink, p.f)

Intended for use cases where `ReverseSearchParams` cleanly encapsulate some
problem domain.
""" ->
function reverse_search_producer(p::ReverseSearchParams)
    reverse_search_producer(p.adj, p.max_degere, p.sink, p.f)
end

@doc doc"""
# Input

- `adj` should be a function mapping `(vertex, n)` to `Union(child, None)`, where `child` is the `n`-th child of `vertex` in the traversal tree, or `None` if `n` is greater than the degree of `vertex` in the tree
- `max_degree` should be a nonnegative integer denoting the maximum degree of a vertex in the tree
- `sink` should be a vertex
- `f` should map a vertex to its parent in the traversal tree

# Output
A producer for the nodes of the graph.
""" ->
function reverse_search_producer(adj, max_degree, sink, f)
    current_vertex = sink
    neighbor_counter = 0
    while true
        while neighbor_counter < max_degree
            neighbor_counter += 1
            next_vertex = adj(current_vertex, neighbor_counter)
            if (next_vertex != None) && (f(next_vertex) == current_vertex)
                # reverse traverse (away from sink)
                current_vertex = next_vertex
                neighbor_counter = 0
            end
        end
        if current_vertex != sink
            produce(current_vertex)
            # forward traverse (towards sink)
            prev_vertex = current_vertex
            current_vertex = f(current_vertex)
            neighbor_counter = 0
            while true
                neighbor_counter += 1
                if adj(current_vertex, neighbor_counter) == prev_vertex
                    break
                end
            end
        end
        if current_vertex == sink && neighbor_counter == max_degree
            break
        end
    end
    produce(sink)
end

end # module
