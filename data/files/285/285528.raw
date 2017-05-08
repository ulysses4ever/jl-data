using ReverseSearch

function reverse_search_params_for_complete_graph(n)
    function adj(vertex, index)
        if n != vertex
            index
        else
            None
        end
    end

    max_degree = n
    sink = 1

    function f(vertex)
        if vertex == 1
            None
        else
            vertex - 1
        end
    end

    ReverseSearchParams(adj, max_degree, sink, f)
end

function reverse_search_vertices_for_complete_graph(n)
    revese_search_params = reverse_search_params_for_complete_graph(n)
    reverse_search_task = @task reverse_search_producer(reverse_search_params)
    sort(collect(reverse_search_task))
end
