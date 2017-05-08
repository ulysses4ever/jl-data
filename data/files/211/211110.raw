using Graphs

# see https://stackoverflow.com/questions/24578430/changing-vertices-value-with-graphs-jl
# for example julia Graphs with non integer vertices.
function empty_graph()
  va::Array{Graphs.KeyVertex{String},1} = {}
  ea::Array{Graphs.Edge{Graphs.KeyVertex{String}},1} = {}
  G = Graphs.graph(va,ea)
end

function add_label!(G,s::String)
  v = Graphs.KeyVertex(Graphs.num_vertices(G) + 1,s)
  Graphs.add_vertex!(G,v)
  v
end

function add_connection!(G,from::Int,to::Int)
  va = Graphs.vertices(G)
  e = Graphs.ExEdge(Graphs.num_edges(G) + 1,va[from],va[to])
  Graphs.add_edge!(G,e)
  e
end

g = empty_graph()

add_label!(g, "foo")

v1 = KeyVertex(1, "foo")
g

add_vertex!(g, v1)