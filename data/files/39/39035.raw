using DataStructures
#push!(LOAD_PATH, "../../src")
using BGraph

# println(CreateVertex(:Deque, :self, ALUnidirectional, Int, Int))
# v1=ALVertexDequeVE{Int,Float64}(3)
# println(CreateVertex(:Deque, Int, ALBidirectional, Int, Int))
# v3=ALVertexBiDequeInt64VE{Int,Float64}(3)
# println(names(v3))
# println(CreateVertex(:Vector, Int, ALUnidirectional, Int, Int))
# v2=ALVertexVectorInt64VE{Int,Float64}(3)
# println(CreateVertex(:Deque, :self, ALUnidirectional, Int, false))
# v4=ALVertexDequeV{Int}(3)

CreateAdjacencyList(:Vector, :Deque, VP=true)
adj_list=BGraph.AdjacencyVectorDequeV(Int)
CreateAdjacencyList(:Vector, :Deque, VP=true, EP=true)
adj_list=BGraph.AdjacencyVectorDequeVE(Int, Float64)
println("From script ", names(Main))
CreateAdjacencyList(:Vector, :Deque, VP=true, EP=true, GP=true)
adj_list=BGraph.AdjacencyVectorDequeVEG(Int, Float64, "hiya")
println(typeof(adj_list))
println(adj_list.graph_property)
println("type of vertices ", typeof(adj_list.vertices))
v1=add_vertex!(24, adj_list)
v2=add_vertex!(24, adj_list)
e1=add_edge!(v1, v2, 3.7, adj_list)
in_edges(v2, adj_list)

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

# adj=AdjacencyList(Vector, Vector, (), Float64, ())
# for i in 1:5
# 	add_vertex!(adj)
# end

# for w in g1_wedges
# 	add_edge!(w[1], w[2], w[3], adj)
# end

# weight(edge)=edge_property(edge)
# s1=dijkstra_shortest_paths(adj, weight, 1)

# @test s1.parents == [1, 3, 1, 2, 3]
# @test s1.dists == [0., 8., 5., 9., 7.]
# @test s1.colormap == [2, 2, 2, 2, 2]


