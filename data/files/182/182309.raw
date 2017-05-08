using DataFrames

min_intersection = int(ARGS[1])
lower_idx = int(ARGS[2])
upper_idx = int(ARGS[3])

users = Dict{UTF8String, Dict{UTF8String,Int}}()
let tracks_u = Dict{UTF8String, Vector{UTF8String}}(), user_id2idx = Dict{UTF8String,Int}()
    idx::Int = 1
    let data = readtable("../jams.csv", header=false), len = length(data[:,2]), user_ids = Set{UTF8String}()
        for i in 1:len
            if isna(data[i,3]) || isna(data[i,4])
                continue
            end
            user_id::UTF8String = data[i,2]
            if !in(user_ids, user_id)
                push!(user_ids, user_id)
                user_id2idx[user_id] = idx
                idx += 1
            end
            track::UTF8String = string(data[i,3], data[i,4])
            if !haskey(tracks_u, track)
                tracks_u[track] = UTF8String[]
            end
            push!(tracks_u[track], user_id)
        end
    end

    len = length(tracks_u)
    i = 0
    @printf("Generating edges (u,v) for %d <= u < %d of %d vertices\n", lower_idx, upper_idx, idx)
    for tracks in tracks_u
        if i % 100 == 0
            @printf("\rProcessing track crossproduct % 6d/%d (% 3d%%)", i, len, div(i*100,len))
        end
        i += 1
        for user1 in tracks[2]
            user1_idx::Int = user_id2idx[user1]
            if user1_idx < lower_idx || user1_idx >= upper_idx
                continue
            end
            for user2 in tracks[2]
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

graph_file = open(string("cojam-tracks-",min_intersection,".graphml"), "a")

print("Writing edges…")
for (user1,snd) in users
    for (user2,count) in snd
        if count >= min_intersection
            @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", user1, user2)
            @printf(graph_file, "\t\t<data key=\"cojams_num\">%d</data>\n", count)
            write(graph_file, "\t</edge>\n")
        end
    end
end
println("done.")
close(graph_file)
