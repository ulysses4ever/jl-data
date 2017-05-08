module ReverseSearch

"""
`adj` maps (vertex, index) to Union(child, None), where child is the child in the traversal tree
`max_degree` is a nonnegative integer
`sink` is a vertex
`f` maps a vertex to its parent in the traversal tree
"""
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
