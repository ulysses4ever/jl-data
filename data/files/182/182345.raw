using DataFrames

user_ids = Set{UTF8String}()
# In the end we will only write out user_ids as vertices if they have at least one neighbour
used_user_ids = Set{UTF8String}()
let artists_u = Dict{UTF8String, Vector{UTF8String}}()
    let data = readtable("jams.csv", header=false), len = length(data[:,2])
        for i in 1:len
            if isna(data[i,3])
                continue
            end
            user_id::UTF8String = data[i,2]
            push!(user_ids, user_id)
            artist::UTF8String = data[i,3]
            if !haskey(artists_u, artist)
                artists_u[artist] = UTF8String[]
            end
            push!(artists_u[artist], user_id)
        end
    end
    @printf("Number of vertices: %d\n", length(user_ids))

    len = length(artists_u)
    i = 0
    for artist in artists_u
        if i % 100 == 0
            @printf("\rProcessing artist crossproduct % 6d/%d (% 3d%%)", i, len, div(i*100,len))
        end
        i += 1
        if length(artist[2]) > 0
            for user in artist[2]
                push!(used_user_ids, user)
            end
        end
    end
    println()
end

graph_file = open("cojam3.graphml", "a")

print("Writing vertices…")
for user in user_ids
    @printf(graph_file, "\t<node id=\"%s\" />\n", user)
end
println("done.")
close(graph_file)
