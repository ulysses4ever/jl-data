using ReverseSearch
using FactCheck

include("../examples/complete_graph.jl")

context("reverse search graph traversal on the complete graph on 1:n") do
    for n in 1:10
        facts("for n=$n, every vertex is visited exactly once") do
            @fact reverse_search_vertices_for_complete_graph(n) --> collect(1:n)
        end
    end
end
