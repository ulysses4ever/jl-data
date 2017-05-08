using DataFrames

function generate_edges(tracks_a::Dict{UTF8String, Vector{UTF8String}}, user_id2idx::Dict{UTF8String,Int}, lower_idx::Int, upper_idx::Int)
    users = Dict{UTF8String, Dict{UTF8String,Int}}()
    for tracks in tracks_a
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

    return users
end

function parsecsv()
    tracks_u = Dict{UTF8String, Vector{UTF8String}}()
    user_id2idx = Dict{UTF8String,Int}()
    idx::Int = 1
    data = readtable("../jams.csv", header=false)
    len = length(data[:,2])
    user_ids = Set{UTF8String}()
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
    return (tracks_u, user_id2idx)
end


function write_edges(users::Dict{UTF8String, Dict{UTF8String,Int}})
    num_edges::Int = 0
    for (user1,snd) in users
        for (user2,count) in snd
            if count >= min_intersection
                num_edges += 1
                @printf(graph_file, "\t<edge source=\"%s\" target=\"%s\">\n", user1, user2)
                @printf(graph_file, "\t\t<data key=\"cojams_num\">%d</data>\n", count)
                write(graph_file, "\t</edge>\n")
            end
        end
    end
    return num_edges
end

min_intersection = int(ARGS[1])
users = Dict{UTF8String, Dict{UTF8String,Int}}()

(tracks_u, user_id2idx) = parsecsv()
graph_file = open(string("cojam-tracks-",min_intersection,".graphml"), "a")

partition = [0       160000 ; 160000  320000; 320000  480000; 480000  640000; 640000  720000; 720000  800000; 800000  880000; 880000  960000; 960000  1040000; 1040000 1120000; 1120000 1200000; 1200000 1280000; 1280000 1360000; 1360000 1440000; 1440000 1480000; 1480000 1500000; 1500000 1520000; 1520000 1530000; 1530000 1540000; 1540000 1550000; 1550000 1555000; 1555000 1560000; 1560000 1565000; 1565000 1570000; 1570000 1571000; 1571000 1572000; 1572000 1573000; 1573000 1574000; 1574000 1575000]

for i in 1:size(partition,1)
    lower_idx = partition[i,1]
    upper_idx = partition[i,2]
    @printf("Generating edges (u,v) for %d <= u < %d…", lower_idx, upper_idx)
    users = generate_edges(tracks_u, user_id2idx, lower_idx, upper_idx)
    println("done.")

    print("Writing edges…")
    num_edges = write_edges(users)
    @printf("wrote %d edges.\n", num_edges)
end

close(graph_file)

