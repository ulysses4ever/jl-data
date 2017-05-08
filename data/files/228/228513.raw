using networkj
using DataFrames

n = readtable("/Users/georgeberry/Google Drive/networkj/graph.csv", header=false)

g = empty_graph(1.)

for link in eachrow(n)
    add_edge!(g, link)
end

s = subgraph(g, [1., 386., 611., 836., 741.])

s = remove_node!(s, 611

c = connected_components(g)