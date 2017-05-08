using Graphs

# Create new graph
g = adjlist(KeyVertex{ASCIIString}, is_directed=false)

# Add 2 vertices
v = add_vertex!(g, "v")
u = add_vertex!(g, "u")

# Add an edge between them
add_edge!(g, v, u)

# This will print:
#   KeyVertex{ASCIIString}(1,"v")
# which is the neighbour of u
println(out_neighbors(u, g))
