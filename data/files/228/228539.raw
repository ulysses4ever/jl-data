module networkj

export Graph, empty_graph, get_index, get_names, index_iter, add_edge, subgraph, ego_subgraph, remove_node, degree, bfs
end

#####graph area

#graph type
type Graph{T}
    #graph::Dict
    names_to_int::Dict{T, Int64}
    int_to_names::Dict{Int64, T}
    node::Dict{T, Any}
    adj::Array #Array{Set{tie{Int, Dict}, 1}, 2}
    size::Int64
end

#edge type
#type Tie
#    alter::Int
#    #attrs::Dict
#end

empty_graph{T}(key_type::T) = Graph(Dict{T, Int64}(), Dict{Int64, T}(), Dict{T, Any}(),Set{Int64}[],0)

#gets index of node from the name of the node
get_index(g::Graph, name) = g.names_to_int[name]

get_names(g::Graph, integer) = g.int_to_names[integer]

#returns the "to" index of H from the "from" index of G
convert_index(g::Graph, h::Graph, from_index) = get_index(h, get_names(g, from_index))

index_iter(g::Graph) = 1:g.size

names_iter(g::Graph) = keys(g.names_to_int)

print_names(g::Graph) = [x for x in keys(g.names_to_int)]


#add edges by node names, not indicies
function add_edge!(g::Graph, edge)
    e1, e2 = edge[1], edge[2]

    if haskey(g.names_to_int, e1) == false
        g.size += 1
        g.names_to_int[e1] = g.size
        g.int_to_names[g.size] = e1
        push!(g.adj, Set{Int64}())
    end

    if haskey(g.names_to_int, e2) == false
        g.size += 1
        g.names_to_int[e2] = g.size
        g.int_to_names[g.size] = e2
        push!(g.adj, Set{Int64}())
    end

    i1 = get_index(g, e1)
    i2 = get_index(g, e2)

    push!(g.adj[i1], i2)

    push!(g.adj[i2], i1)
end

#give this the node name
function add_node!{T}(g::Graph{T}, node::T, node_attr=nothing)
    if haskey(g.names_to_int, node) == false
        g.size += 1
        g.names_to_int[node] = g.size
        g.int_to_names[g.size] = node
        push!(g.adj, Set{Int64}())
    end

    if node_attr != nothing
        g.node[node] = node_attr
    end
end


#by name not by index
function subgraph(g::Graph, node_bunch::Array)
    s = empty_graph(node_bunch[1])

    node_bunch = Set(node_bunch)

    for node in node_bunch
        add_node!(s, node)
    end

    for node1 in node_bunch
        for node2 in node_bunch
            if in(get_index(g, node2), g.adj[get_index(g, node1)])
                add_edge!(s, (node1, node2))
            end
        end
    end

    #move node attrs
    for vertex in names_iter(s)
        if haskey(g.node, vertex)
            s.node[vertex] = g.node[vertex]
        end
    end

    return s
end



#by name not by index
function ego_subgraph(g::Graph, node)

    node_index = get_index(g, node)

    s = empty_graph(node)


    #get cnnections to ego
    for adj_vertex in g.adj[node_index]
        add_edge!(s, (get_names(g, node_index), get_names(g, adj_vertex)))
    end

    #get connections between alters
    for adj_vertex in g.adj[node_index]
        for friend_of_friend in g.adj[adj_vertex]
            #if the alter's conteact is in the ego subgraph
            if haskey(s.names_to_int, get_names(g, friend_of_friend))
                add_edge!(s, (get_names(g, adj_vertex), get_names(g, friend_of_friend)))
            end
        end
    end


    #move node_index attributes over
    for vertex in names_iter(s)
        if haskey(g.node, vertex)
            s.node[vertex] = g.node[vertex]
        end
    end
    return s
end

#by name not by index
function remove_node{T}(g::Graph{T}, node::T)

    node_index = get_index(g, node)

    delete!(g.names_to_int, node)
    delete!(g.node, node)
    delete!(g.int_to_names, node_index)
    g.size = g.size - 1

    node_links = g.adj[node_index]

    for link in node_links
        delete!(g.adj[link], node_index)
    end

    splice!(g.adj, node_index)

    #add one back for the removed node
    for index_num in (index_iter(g)+1)
        if index_num > node_index
            #shift the indx down by one
            g.int_to_names[index_num-1] = g.int_to_names[index_num]
        end
    end

    #delete last after
    delete!(g.int_to_names, g.size+1)

    #subtract one from all keys above removed node index
    for vertex_name in keys(g.names_to_int)
        if g.names_to_int[vertex_name] > node_index
            g.names_to_int[vertex_name] -= 1
        end
    end

    return g

end


function degree(g::Graph)
    deg = zeros(Int64, g.size)

    for vertex in index_iter(g)
        deg[vertex] = length(g.adj[vertex])
    end
    return deg
end


##bfs starting at node indexed by node_index
function bfs(adj::Array{Set{Int64}}, node_index::Int64, to_traverse = Int64[], seen = Set{Int64}())

    push!(seen, node_index)

    if length(to_traverse) == 0
        return seen
    end

    for vertex in adj[node_index]
        if in(vertex, seen) == false
            unshift!(to_traverse, vertex)
        end
    end

    t = pop!(to_traverse)

    b = bfs(adj, t, to_traverse, seen)

end

#number of connectex components in a graph
function connected_components(g::Graph)
    seen_set = Set{Int64}()
    components = Set{Int64}[]

    for vertex in index_iter(g)
        if in(vertex, seen_set) == false
            c = bfs(g.adj, vertex)
            push!(components, c)
            union!(seen_set, c)
        end
    end
    return components
end