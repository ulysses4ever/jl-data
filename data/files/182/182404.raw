using Graphs

file = open("likes.csv", "r")
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

println("Building graph..")

colike_users_graph = inclist(KeyVertex{ASCIIString}, ExEdge{KeyVertex{ASCIIString}}, is_directed=false)

vertices = Dict()
i = 0
num_users = length(unique(data[:,2]))
for user1 in users
    i += 1
    @printf("Analysing user %d of %d\r", i, num_users)
    j = 0
    for user2 in users
        if j % 1000 == 0
            @printf("Analysing user % 6d of %d (% 6d/%d inner)\r", i, num_users, j, num_users)
        end
        j += 1
        if user1[1] < user2[1]
            colikes = intersect(user1[2], user2[2])
            if length(colikes) > 0
                if (!haskey(vertices, user1[1]))
                    u = KeyVertex{ASCIIString}(num_vertices(colike_users_graph) + 1, user1[1])
                    vertices[user1[1]] = add_vertex!(colike_users_graph, u)
                else
                    u = vertices[user1[1]]
                end
                if (!haskey(vertices, user2[1]))
                    v = KeyVertex{ASCIIString}(num_vertices(colike_users_graph) + 1, user2[1])
                    vertices[user2[1]] = add_vertex!(colike_users_graph, v)
                else
                    v = vertices[user2[1]]
                end
                add_edge!(colike_users_graph, u, v)
                edges = filter(e -> in(v, [e.source, e.target]), out_edges(u, colike_users_graph))
                append!(edges, filter(e -> in(u, [e.source, e.target]), out_edges(v, colike_users_graph)))
                for e in edges
                    e.attributes["colikes"] = colikes
                    e.attributes["colikes_num"] = length(colikes)
                end
            end
        end
    end
end

@printf("Generated co-like graph with %d vertices and %d edges.\n", num_vertices(colike_users_graph), num_edges(colike_users_graph))

graph_file = open("colike.graphml", "w")
write(graph_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
write(graph_file, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n")
write(graph_file, "<graph id=\"G\" edgedefault=\"undirected\">\n")
write(graph_file, "<key id=\"colikes_num\" for=\"edge\" attr.name=\"colilkes_num\" attr.type=\"int\"/>\n")
write(graph_file, "<key id=\"colikes\" for=\"edge\" attr.name=\"colilkes\" attr.type=\"string\"/>\n")

for v in colike_users_graph.vertices
    @printf(graph_file, "<node id=\"n%d\" />\n", vertex_index(v, colike_users_graph))
    for e in filter(e -> (e.source.key < e.target.key), out_edges(v, colike_users_graph))
        @printf(graph_file, "<edge source=\"n%d\" target=\"n%d\">\n", vertex_index(e.source, colike_users_graph), vertex_index(e.target, colike_users_graph))
        for attr in e.attributes
            @printf(graph_file, "<data key=\"%s\">%s</data>\n", attr[1], attr[2])
        end
        write(graph_file, "</edge>\n")
    end
end

write(graph_file, "</graph>\n")
write(graph_file, "</graphml>")
close(graph_file)
