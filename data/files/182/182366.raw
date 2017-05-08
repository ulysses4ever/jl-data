using DataFrames

users_a = Dict{UTF8String, Vector{UTF8String}}()
let data = readtable("jams-100000.csv", header=false), len = length(data[:,2])
    for i in 1:len
        artist = data[i,3]
        user_id = data[i,2]
        if isna(user_id)
            println((data[i-1,1], data[i-1,2]))
        end
        if isna(artist)
            continue
        end
        if !haskey(users_a, user_id)
            users_a[user_id] = UTF8String[]
        end
        push!(users_a[user_id], artist)
    end
end

println("Building graph…")

graph_file = open("cojam.graphml", "w")
write(graph_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
write(graph_file, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n")
write(graph_file, "<graph id=\"G\" edgedefault=\"undirected\">\n")
write(graph_file, "\t<key id=\"cojams_num\" for=\"edge\" attr.name=\"cojams_num\" attr.type=\"int\"/>\n")
write(graph_file, "\t<key id=\"cojams\" for=\"edge\" attr.name=\"cojams\" attr.type=\"string\"/>\n")

println("…writing vertices.")
for user in users_a
    @printf(graph_file, "\t<node id=\"%s\" />\n", user[1])
end

# num_users = length(users_a)
println("…writing edges.")
#i = 0
for user1 in users_a
    #i += 1
    #if i % 10000 == 0
    #    println()
    #end
    #@printf("Analysing user % 6d of %d\r", i, num_users)
    for user2 in users_a
        if user1[1] < user2[1]
            cojams = intersect(user1[2], user2[2])
            if length(cojams) > 0
                @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", user1[1], user2[1])
                @printf(graph_file, "\t\t<data key=\"cojams\">%s</data>\n", join(cojams,","))
                @printf(graph_file, "\t\t<data key=\"cojams_num\">%d</data>\n", length(cojams))
                write(graph_file, "\t</edge>\n")
            end
        end
    end
end
println("\n…done.")

write(graph_file, "</graph>\n")
write(graph_file, "</graphml>")
close(graph_file)
