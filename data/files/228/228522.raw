using DataFrames

network = readtable("/Users/georgeberry/Google Drive/fsqr proj/second_try/sFoursquareFriendship.csv",header=true)
checkins = readtable("/Users/georgeberry/Google Drive/fsqr proj/second_try/sFoursquareCheckins.csv",header=true)


function dateify(date_as_string::String)
    r = [int(x) for x in split(date_as_string, r"\s|:|-")]
    return Date(r[1],r[2],r[3],r[4],r[5],r[6])
end


####

function user_venue_checkins(chk)
    users = Dict{Int64, Dict}()
    sizehint(users, 10000)

    for row_iter in eachrow(chk)

        user, date, venue = split_up(row_iter)

        if haskey(users, user) == false
            users[user] = Dict{Int64, Array{Date,1}}()
        end

        if haskey(users[user], venue) == false
            users[user][venue] = Date[]
        end

        push!(users[user][venue], date)
    end

    for user in keys(users)
        for venue in keys(users[user])
            users[user][venue] = date_sort(users[user][venue])
        end
    end
    users
end

function split_up(row)
    user, lat, long, date, venue = row
    user, date, venue = int(user[2]), dateify(date[2]), int(venue[2])
    return user, date, venue
end

##### make stuff

@time chkins = user_venue_checkins(checkins)

gg = empty_graph()

@time for row in eachrow(network)
    add_edge!(gg, row)
end

@time for num in nodes_iter(gg)
    i = getname(gg, num)
    gg.node_attr[num] = chkins[i]
end

a = open("/Users/georgeberry/Desktop/save.thing", "w+")

@time serialize(a, gg)

##### ego analysis

g = open("/Users/georgeberry/Desktop/save.thing", "r") do file
    deserialize(file)
end

#types
type Exposure
    size::Int64
    config::Dict{Str, Config}
end

type Config
    adopt::Int64
    exp::Int64
end


##functions

function ego_analysis(ego_subgraph::Graph)
    ego_info = Dict{Int, Dict()}()

    ego_subgraph.node_attr[1] = first_checkins(ego_subgraph.node_attr[1])

    all_venues = Set{Int64}()
    for nodes in nodes_iter(ego_subgraph)
        union(all_venues, keys(ego_subgraph.node_attr[node]))
    end
    #would like to get all venues up front

    for venue in all_venues

        ego_visited = 0

        if venue in ego_subgraph.node_attr[1]
            ego_visited = 1
        end

        prev_alters = prev_alter_checkins(ego_subgraph, venue, ego_subgraph.node_attr[venue][1]) ##need to pass the last argument a really big date if the ego hasn't checked in



        for alters in range(len(prev_alters))
            #may need to fix indexing here
            exposure_group = append!([prev_alters[x][1] for x in range(alters)], 1)
            ego_venue_subgraph = subgraph(ego_subgraph, exposure_group)
            exposure_size = ego_venue_subgraph.num_nodes - 1

            if exposure_size >= 1 && exposure_size <= 5
                config = get_config(ego_venue_subgraph)
                if haskey(ego_info, exposure_size) == false
                    ego_info[exposure_size] = Exposure(exposure_size, Dict{Str, Config}())
                end

                if haskey(ego_info[exposure_size].config, config) == false
                    ego_info[exposure_size].config[config] = Config(0, 0)
                end

            end

            ego_info[exposure_size].config[config].exp += 1

            if ego_visited == 1
                if (alters) == length(prev_alters)
                    ego_info[exposure_size].config[config].adopt += 1
                end
            end
        end
    end
    return ego_info
end


function first_checkins(checkins::Dict)

end

function prev_alter_checkins(ego_subgraph::Graph, venue::Int64, date_cutoff::Date)
    prev_alters = Tuple[]

    for alter in nodes_iter(ego_subgraph)
        if venue in ego_subgraph.node_attr[alter]
            for checkin in ego_subgraph.node_attr[alter][venue]
                if greater_than(checkin, date_cutoff)
                    break
                elseif greater_than(date_cutoff, checkin)
                    push!(prev_alters, (alter, checkin))
                    break
                end
            count += 1
        end

        if count > 6
            break
        end
    end

    sort!(prev_alters, lt = lt_date_tuple)

    return prev_alters
end



end

function get_config(ego_venue_subgraph::Graph)
    goodbye_ego = remove_node(ego_venue_subgraph, 1)

    config = [str(x) for x in sort(degree(ego_venue_subgraph))]
    config = join(config, '')
    

end

function lt_date_tuple(date_tuple1::Tuple, date_tuple2::Tuple)
    if less_than(date_tuple1[2], date_tuple2[2])
        return true
    else
        return false
    end
end

