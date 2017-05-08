using DataStructures
#push!(LOAD_PATH, "../../src")
using BGraph
nei=AdjacencyListNeighbor(3, 17)

adj=AdjacencyList(Vector, Deque, Int, Float64, "my graph")
v1=add_vertex!(24, adj)
v2=add_vertex!(25, adj)
e1=add_edge!(v1, v2, 3.7, adj)
println(e1)

typealias StringDict{V} Dict{ASCIIString,V}
adj=AdjacencyList(StringDict, Vector, Int, (), "my graph")
v1=add_vertex!("Chicago", 24, adj)
v2=add_vertex!("New York", 25, adj)
println("v1 $v1 v2 $v2")
e1=add_edge!(v1, v2, adj)
println("noneighbor $e1")


typealias StringDict{V} Dict{ASCIIString,V}
adj=AdjacencyList(StringDict, StringDict, Int, Float64, "my graph")
v1=add_vertex!("Chicago", 24, adj)
v2=add_vertex!("New York", 25, adj)
println("v1 $v1 v2 $v2")
e1=add_edge!(v1, v2, "plane", 3.7, adj)
println(e1)

function dijkstra_shortest_paths(g, weight, start)
    
end

g1_wedges = [
    (1, 2, 10.),
    (1, 3, 5.),
    (2, 3, 2.),
    (3, 2, 3.),
    (2, 4, 1.),
    (3, 5, 2.),
    (4, 5, 4.),
    (5, 4, 6.),
    (5, 1, 7.),
    (3, 4, 9.) ]

adj=AdjacencyList(Vector, Vector, (), Float64, ())
for i in 1:5
	add_vertex!((), adj)
end

for w in g1_wedges
	add_edge!(w[1], w[2], w[3], adj)
end

weight(edge)=edge_property(edge)
s1=dijkstra_shortest_paths(adj, weight, 1)

# @test s1.parents == [1, 3, 1, 2, 3]
# @test s1.dists == [0., 8., 5., 9., 7.]
# @test s1.colormap == [2, 2, 2, 2, 2]


