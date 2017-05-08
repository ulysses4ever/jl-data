using ReverseSearch
using Base.Test

n = 10

vertices = collect(1:n)

function adj(vertex, index)
    if n != vertex
        vertices[index]
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

reverse_search_vertices = sort(collect(@task reverse_search_producer(adj, max_degree, sink, f)))

@test reverse_search_vertices == vertices
