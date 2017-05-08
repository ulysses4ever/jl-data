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

gg = empty_graph(1)

@time for row in eachrow(network)
    add_edge!(gg, row)
end

@time for name in names_iter(gg)
    gg.node[name] = chkins[name]
end

a = open("/Users/georgeberry/Desktop/save.thing", "w+")

@time serialize(a, gg)

##### ego analysis

@time g = open("/Users/georgeberry/Desktop/save.thing", "r") do file
    deserialize(file)
end

#types
type Config
    adopt::Int64
    exp::Int64
end

#function add_up(c1::Exposure, c2::Exposure)
#    c3 = Exposure()


##functions

function ego_analysis(ego_subgraph::Graph)
    ego_info = Dict()

    ego_name = get_names(ego_subgraph, 1)

    ego_subgraph.node[ego_name] = first_checkins(ego_subgraph.node[ego_name])

    all_venues = Set{Int64}()
    for nodes in names_iter(ego_subgraph)
        union!(all_venues, keys(ego_subgraph.node[nodes]))
    end
    #would like to get all venues up front

    for venue in all_venues

        if haskey(ego_subgraph.node[ego_name], venue)
            ego_visited = 1
            first_checkin = ego_subgraph.node[ego_name][venue][1]
        else
            ego_visited = 0
            first_checkin = Date(2014,1,1,1,1,1) #after the dataset
        end

        prev_alters = prev_alter_checkins(ego_subgraph, venue, first_checkin) ##need to pass the last argument a really big date if the ego hasn't checked in

        for alters in 1:length(prev_alters)
            #may need to fix indexing here
            exposure_group = push!([prev_alters[x][1] for x in 1:alters], ego_name)
            ego_venue_subgraph = subgraph(ego_subgraph, exposure_group)
            exposure_size = ego_venue_subgraph.size - 1

            if exposure_size >= 1 && exposure_size <= 5
                config = get_config(ego_venue_subgraph)
                if haskey(ego_info, exposure_size) == false
                    ego_info[exposure_size] = Dict()
                end

                if haskey(ego_info[exposure_size], config) == false
                    ego_info[exposure_size][config] = [0,0]
                end

                ego_info[exposure_size][config][2] += 1
            end


            if ego_visited == 1 && exposure_size <= 5
                if (alters) == length(prev_alters)
                    ego_info[exposure_size][config][1] += 1
                end
            end
        end
    end
    return ego_info
end


function first_checkins(venue_dict::Dict)
    checkin_dict = Dict()

    for venue in keys(venue_dict)
        checkin_dict[venue] = [venue_dict[venue][1]]
    end

    return checkin_dict

end

function prev_alter_checkins(ego_subgraph::Graph, venue::Int64, date_cutoff::Date)
    prev_alters = Tuple[]

    count = 0

    for alter in names_iter(ego_subgraph)
        if haskey(ego_subgraph.node[alter], venue)
            for checkin in ego_subgraph.node[alter][venue]
                if greater_than(checkin, date_cutoff)
                    break
                elseif greater_than(date_cutoff, checkin)
                    push!(prev_alters, (alter, checkin))
                    break
                end
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


function get_config(ego_venue_subgraph::Graph)
    goodbye_ego = remove_node(ego_venue_subgraph, get_names(ego_venue_subgraph, 1))

    config = [string(x) for x in sort(degree(ego_venue_subgraph))]
    config = join(config, "")
    config = join((config, length(connected_components(ego_venue_subgraph))), ":")
    return config
end

function lt_date_tuple(date_tuple1::Tuple, date_tuple2::Tuple)
    if less_than(date_tuple1[2], date_tuple2[2])
        return true
    else
        return false
    end
end

answers = Dict()

@time for vertex in names_iter(g)
    x = ego_analysis(ego_subgraph(g, vertex))
    for size in keys(x)
        if haskey(answers, size) == false
            answers[size] = Dict()
        end

        for c in keys(x[size])
            if haskey(answers[size], c) == false
                answers[size][c] = [0,0]
            end

            answers[size][c][1] += x[size][c][1]
            answers[size][c][2] += x[size][c][2] 
        end
    end
end
