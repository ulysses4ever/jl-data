Module NetworkJ

export Graph, empty_graph, getindex, getname, nodes_iter, add_edge, subgraph

#####graph area

#graph type
type Graph
    graph_attr::Dict
    names_to_int::Dict{Int64, Int64}
    int_to_names::Dict{Int64, Int64}
    node_attr::Dict
    adj_list::Array #Array{Set{tie{Int, Dict}, 1}, 2}
    num_nodes::Int64
end

#edge type
#type Tie
#    alter::Int
#    #attrs::Dict
#end

empty_graph() = Graph(Dict(), Dict{Int64, Int64}(), Dict{Int64, Int64}(), Dict(),Set[],0)

#gets index of node from the name of the node
getindex(g::Graph, name) = g.names_to_int[name]

getname(g::Graph, integer) = g.int_to_names[integer]

#returns the "to" index from the "from" index
convert_index(g::Graph, h::Graph, from_index) = getindex(h, getname(g, from_index))

nodes_iter(g::Graph) = 1:g.num_nodes

function add_edge!(g::Graph, edge)
    e1, e2 = edge[1], edge[2]

    if haskey(g.names_to_int, e1) == false
        g.num_nodes += 1
        g.names_to_int[e1] = g.num_nodes
        g.int_to_names[g.num_nodes] = e1
        push!(g.adj_list, Set())
    end

    if haskey(g.names_to_int, e2) == false
        g.num_nodes += 1
        g.names_to_int[e2] = g.num_nodes
        g.int_to_names[g.num_nodes] = e2
        push!(g.adj_list, Set())
    end

    i1 = getindex(g, e1)
    push!(g.adj_list[i1], getindex(g, e2))

    i2 = getindex(g, e2)
    push!(g.adj_list[i2], getindex(g, e1))
end


function subgraph(g::Graph, node_bunch::Array)
    s = empty_graph()
    l = length(node_bunch)

    for node1 in node_bunch
        for node2 in g.adj_list[node1]
            if node2 in node_bunch
                add_edge!(s, (getname(g, node1), getname(g, node2)))
            end
        end
    end

    for vertex in nodes_iter(s)
        s.node_attr[vertex] = g.node_attr[convert_index(s, g, vertex)]
    end
    return s
end


#by index not by name
function ego_subgraph(g::Graph, node::Int64)
    s = empty_graph()

    #get cnnections to ego
    for adj_vertex in g.adj_list[node]
        add_edge!(s, (getname(g, node), getname(g, adj_vertex)))
    end

    #get connections between alters
    for adj_vertex in g.adj_list[node]
        for friend_of_friend in g.adj_list[adj_vertex]
            #if the alter's conteact is in the ego subgraph
            if haskey(s.names_to_int, getname(g, friend_of_friend))
                add_edge!(s, (getname(g, adj_vertex), getname(g, friend_of_friend)))
            end
        end
    end

    #move node attributes over
    for vertex in nodes_iter(s)
        s.node_attr[vertex] = g.node_attr[convert_index(s, g, vertex)]
    end
    return s
end

#by index not by name
function remove_node(g::Graph, node::Int64)
    s = empty_graph()

    for vertex in nodes_iter(g)
        if vertex != node
            append!(s, g.adj_list[vertex])
            s.node_attr[vertex] = g.node_attr[vertex]
            s.num_nodes = g.num_nodes - 1
            s.names_to_int[getname(g, vertex)] = s.names_to_int[getname(g, vertex)]
            s.int_to_names[vertex] = g.int_to_names[vertex]
        end
    end

    for vertex1 in s.adj_list
        delete!(vertex1, node)
    end

    return s
end


function degree(g::Graph)
    deg = zeros(Int64, g.num_nodes)

    for vertex in nodes_iter(g)
        deg[vertex] = length(g.adj_list[vertex])
    end
    return deg
end


function bfs(adj::Array, node::Int64, to_traverse::Array, seen::Set)

    union!(seen, Set(node))

    for vertex in adj[node]
        if in(vertex, seen) == false
            unshift!(to_traverse, vertex)
        end
    end

    if length(to_traverse) == 0
        return seen
    end

    b = bfs(adj, pop!(to_traverse), to_traverse, seen)

end

#connected component starting from a vertex
function connected_component(g::graph, node::Int64)
    



