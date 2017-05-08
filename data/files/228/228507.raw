#by name not by index
function subgraph{T}(g::Graph{T}, node_bunch::Array)
    s = empty_graph(node_bunch[1])

    node_set = Set()

    for vertex in node_bunch
        push!(node_set, vertex)
    end

    for vertex in node_set
        add_node!(s, vertex)
    end

    for node1 in node_set
        for node2 in node_set
            if in(get_index(g, node2), g.adj[get_index(g, node1)])
                add_edge!(s, (node1, node2))
            end
        end
    end

    #move node attrs
    for vertex in index_iter(s)
        if haskey(g.node, vertex)
            s.node[get_name(s, vertex)] = g.node[get_name(s, vertex)]
        end
    end

    return s
end


#change a graph

#by name not by index
function ego_subgraph{T}(g::Graph{T}, node::T)

    node_index = get_index(g, node)

    s = empty_graph(node)

    #get cnnections to ego
    for adj_vertex in g.adj[node_index]
        add_edge!(s, (get_name(g, node_index), get_name(g, adj_vertex)))
    end

    #get connections between alters
    for friend in g.adj[node_index]
        for friend_of_friend in g.adj[friend]
            #if the alter's conteact is in the ego subgraph
            if haskey(s.names_to_int, get_name(g, friend_of_friend))
                add_edge!(s, (get_name(g, friend), get_name(g, friend_of_friend)))
            end
        end
    end

    #move node attributes over
    for vertex in index_iter(s)
        if haskey(g.node, get_name(s, vertex))
            s.node[get_name(s, vertex)] = g.node[get_name(s, vertex)]
        end
    end
    return s
end