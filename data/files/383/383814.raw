using Graphs
using GraphPlot
using Compose

V1 = ExVertex(1, "V1");
V2 = ExVertex(2, "V2");
println(V2)
vertexList = ExVertex[]
push!(vertexList, V1)
push!(vertexList, V2)
E1 = ExEdge(1, vertexList[1], vertexList[2])
println(typeof(vertexList[1]))
draw(PDF("simple_graph.pdf", 10cm, 10cm),gplot(g,layout=circular_layout))
