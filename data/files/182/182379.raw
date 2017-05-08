using DataFrames

users = Dict{(UTF8String,UTF8String), Vector{UTF8String}}()
user_ids = Set{UTF8String}()
let artists_u = Dict{UTF8String, Vector{UTF8String}}()
    let data = readtable("jams.csv", header=false), len = length(data[:,2])
        for i in 1:len
            user_id = data[i,2]
            push!(user_ids, user_id)
            artist = data[i,3]
            if isna(artist)
                continue
            end
            if !haskey(artists_u, artist)
                artists_u[artist] = UTF8String[]
            end
            push!(artists_u[artist], user_id)
        end
    end

    len = length(artists_u)
    i = 0
    for artist in artists_u
        @printf("\rProcessing artist crossproduct % 6d/%d (% 3d%%)                    ", i, len, div(i*100,len))
        i += 1
        j = 0
        for user1 in artist[2]
            j += 1
            if j % 25 == 0
                @printf("\rProcessing artist crossproduct % 6d/%d (% 3d%%) (user % 4d/%d)", i, len, div(i*100,len), j, length(artist[2]))
            end
            for user2 in artist[2]
                if user1 < user2
                    if !haskey(users, (user1, user2))
                        users[(user1, user2)] = []
                    end
                    push!(users[(user1, user2)], artist[1])
                end
            end
        end
    end
    println()
end

println("Building graph…")

graph_file = open("cojam2.graphml", "w")
write(graph_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
write(graph_file, "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n")
write(graph_file, "<graph id=\"G\" edgedefault=\"undirected\">\n")
write(graph_file, "\t<key id=\"cojams_num\" for=\"edge\" attr.name=\"cojams_num\" attr.type=\"int\"/>\n")
write(graph_file, "\t<key id=\"cojams\" for=\"edge\" attr.name=\"cojams\" attr.type=\"string\"/>\n")

println("…writing vertices.")
for user in user_ids
    @printf(graph_file, "\t<node id=\"%s\" />\n", user)
end

println("…writing edges.")
for edge in users
    @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", edge[1][1], edge[1][2])
    @printf(graph_file, "\t\t<data key=\"cojams\">%s</data>\n", join(edge[2],","))
    @printf(graph_file, "\t\t<data key=\"cojams_num\">%d</data>\n", length(edge[2]))
    write(graph_file, "\t</edge>\n")
end
println("\n…done.")

write(graph_file, "</graph>\n")
write(graph_file, "</graphml>")
close(graph_file)
