file = open("likes.csv", "r")
data = readcsv(file,ASCIIString)
close(file)

# Simple statistics
num_users = length(unique(data[:,2]))
@printf("Analysing %d likes on %d jams by %d users.\n", length(data[:,1]), length(unique(data[:,1])), num_users)

# Generate colike-users graph where users are connected if they liked the same jame
users = Dict{ASCIIString,Set{ASCIIString}}()
for i in 1:length(data[:,1])
    jam = data[i,:]
    if !haskey(users, jam[2])
        users[jam[2]] = Set{ASCIIString}()
    end
    push!(users[jam[2]], jam[1])
end

println("Building graph…")

println("…writing vertices.")
graph_file = open("colike.graphml", "w")
write(graph_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
write(graph_file, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n")
write(graph_file, "<graph id=\"G\" edgedefault=\"undirected\">\n")
write(graph_file, "\t<key id=\"colikes_num\" for=\"edge\" attr.name=\"colilkes_num\" attr.type=\"int\"/>\n")
write(graph_file, "\t<key id=\"colikes\" for=\"edge\" attr.name=\"colilkes\" attr.type=\"string\"/>\n")

for user in users
    @printf(graph_file, "\t<node id=\"%s\" />\n", user[1])
end

println("…writing edges.")
i = 0
for user1 in users
    i += 1
    if i % 1000 == 0
        println()
    end
    @printf("Analysing user % 6d of %d\r", i, num_users)
    for user2 in users
        if user1[1] < user2[1]
            colikes = intersect(user1[2], user2[2])
            if length(colikes) > 0
                @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", user1[1], user2[1])
                @printf(graph_file, "\t\t<data key=\"colikes\">%s</data>\n", join(colikes,","))
                @printf(graph_file, "\t\t<data key=\"colikes_num\">%d</data>\n", length(colikes))
                write(graph_file, "\t</edge>\n")
            end
        end
    end
end
println("\n…done.")

write(graph_file, "</graph>\n")
write(graph_file, "</graphml>")
close(graph_file)
