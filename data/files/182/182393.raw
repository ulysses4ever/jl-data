using Graphs

file = open("likes-10000.csv", "r")
data = readcsv(file,ASCIIString)
close(file)

# Simple statistics
@printf("Analysing %d likes on %d jams by %d users.\n", length(data[:,1]), length(unique(data[:,1])), length(unique(data[:,2])))

# Generate colike-users graph where users are connected if they liked the same jame
users = Dict()
for i in 1:length(data[:,1])
    jam = data[i,:]
    if haskey(users, jam[2])
        push!(users[jam[2]], jam[1])
    else
        users[jam[2]] = [jam[1]]
    end
end

coliked_users = Set()
colike_users = Dict()
for user1 in users
    for user2 in users
        if user1[1] < user2[1]
            colikes = intersect(user1[2], user2[2])
            if length(colikes) > 0
                colike_users[(user1[1], user2[1])] = colikes
                push!(coliked_users, user1[1])
                push!(coliked_users, user2[1])
            end
        end
    end
end

@printf("There are %d pairs of users who liked at least one common jam.\n", length(colike_users))

colike_users_graph = inclist(KeyVertex{ASCIIString}, ExEdge{KeyVertex{ASCIIString}}, is_directed=false)
vertices = Dict()
for user in coliked_users
    vertex = KeyVertex{ASCIIString}(num_vertices(colike_users_graph) + 1, user)
    vertices[user] = add_vertex!(colike_users_graph, vertex)
end

for pair in colike_users
    u = vertices[pair[1][1]]
    v = vertices[pair[1][2]]
    add_edge!(colike_users_graph, u, v)
    edges = filter(e -> in(v, [e.source, e.target]), out_edges(u, colike_users_graph))
    append!(edges, filter(e -> in(u, [e.source, e.target]), out_edges(v, colike_users_graph)))
    for e in edges
        e.attributes["colikes"] = pair[2]
        e.attributes["colikes_num"] = length(pair[2])
    end
end

@printf("Generated co-like graph with %d vertices and %d edges.\n", num_vertices(colike_users_graph), num_edges(colike_users_graph))

graph_file = open("colike.graphml", "w")
write(graph_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
write(graph_file, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n")
write(graph_file, "<graph id=\"G\" edgedefault=\"undirected\">\n")

for v in colike_users_graph.vertices
    @printf(graph_file, "<node id=\"n%d\" />\n", vertex_index(v, colike_users_graph))
    for e in filter(e -> (e.source.key < e.target.key), out_edges(v, colike_users_graph))
        @printf(graph_file, "<edge source=\"n%d\" target=\"n%d\" />", vertex_index(e.source, colike_users_graph), vertex_index(e.target, colike_users_graph))
    end
end

write(graph_file, "</graph>\n")
write(graph_file, "</graphml>")
close(graph_file)
