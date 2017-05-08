using DataFrames

lower_idx = int(ARGS[1])
upper_idx = int(ARGS[2])

users = Dict{UTF8String, Dict{UTF8String,Int}}()
user_ids = Set{UTF8String}()
let artists_u = Dict{UTF8String, Vector{UTF8String}}(), user_id2idx = Dict{UTF8String,Int}()
    idx::Int = 1
    let data = readtable("jams.csv", header=false), len = length(data[:,2])
        for i in 1:len
            if isna(data[i,3])
                continue
            end
            user_id::UTF8String = data[i,2]
            if !in(user_ids, user_id)
                push!(user_ids, user_id)
                user_id2idx[user_id] = idx
                idx += 1
            end
            artist::UTF8String = data[i,3]
            if !haskey(artists_u, artist)
                artists_u[artist] = UTF8String[]
            end
            push!(artists_u[artist], user_id)
        end
    end

    len = length(artists_u)
    i = 0
    @printf("Generating edges (u,v) for %d <= u < %d of %d vertices\n", lower_idx, upper_idx, idx)
    for artist in artists_u
        if i % 100 == 0
            @printf("\rProcessing artist crossproduct % 6d/%d (% 3d%%)", i, len, div(i*100,len))
        end
        i += 1
        for user1 in artist[2]
            user1_idx::Int = user_id2idx[user1]
            if user1_idx < lower_idx || user1_idx >= upper_idx
                continue
            end
            for user2 in artist[2]
                if user1 < user2
                    if !haskey(users, user1)
                        users[user1] = Dict{UTF8String,Int}()
                    end
                    if !haskey(users[user1], user2)
                        users[user1][user2] = 0
                    end
                    users[user1][user2] += 1
                end
            end
        end
    end
    println()
end

graph_file = open("cojam3.graphml", "a")

print("Writing edges…")
for (user1,snd) in users
    for (user2,count) in snd
        @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", user1, user2)
        @printf(graph_file, "\t\t<data key=\"cojams_num\">%d</data>\n", count)
        write(graph_file, "\t</edge>\n")
    end
end
println("done.")
close(graph_file)
