module NetworkJ

using Base.Collections

export Graph, empty_graph, get_name, get_index, convert_index, index_iter, names_iter
export print_names, add_edge!, add_node!, subgraph, ego_subgraph, remove_node!
export remove_edge!, dijkstra_targ, tie_range
export degree, bfs, connected_components
export PriorityQueue, enqueue!, dequeue!
end

#graph type
#T is the type of the human-readable node names
#allows for doing lookup/analysis by string names without runing performance
type Graph{T}
    names_to_int::Dict{T, Int64}
    int_to_names::Dict{Int64, T}
    node::Dict{T, Any}
    adj::Array{Set{Int64}}
    size::Int64
end

#type Bipartite{T}
#    names_to_int::Dict{T, Int64}
#    int_to_names::Dict{Int64, T}
#    node::Dict{T, Any}
#    adj::Array{Set{Int64}}
#    int_to_category::Dict{Int64, Int64}
#    size::Int64
#end

#really basic graph methods

#this is hack-y right now: should give it a type not an instance of that type
empty_graph{T}(key_type::T) = Graph(Dict{T, Int64}(), Dict{Int64, T}(), Dict{T, Any}(),Set{Int64}[],0)

#gets index of node from the name of the node
get_index{T}(g::Graph{T}, name::T) = g.names_to_int[name]

get_name(g::Graph, integer::Int64) = g.int_to_names[integer]

#returns the "to" index of H from the "from" index of G
convert_index(g::Graph, h::Graph, from_index::Int64) = get_index(h, get_name(g, from_index))

index_iter(g::Graph) = 1:g.size

names_iter(g::Graph) = keys(g.names_to_int)

print_names(g::Graph) = [x for x in keys(g.names_to_int)]

num_edges(g::Graph) = sum(degree(g))/2

neighbors{T}(g::Graph{T}, node_index) = g.adj[node_index]

function get_edges(g::Graph)
    e = (Int64,Int64)[]

    for ego_index in index_iter(g)
        for alter_index in g.adj[ego_index]
            push!(e, (ego_index, alter_index))
        end
    end

    return e
end

#build a graph

#add edges by node names, not indicies
function add_edge!{T}(g::Graph{T}, edge::(T,T))
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

#by name not by index
function remove_node!{T}(g::Graph{T}, node::T)

    node_index = get_index(g, node)

    delete!(g.names_to_int, node)
    delete!(g.node, node)
    delete!(g.int_to_names, node_index)
    g.size = g.size - 1

    node_links = g.adj[node_index]

    #delete connections to node among all other verticies
    for link in node_links
        delete!(g.adj[link], node_index)
    end

    #remove element of adj array corresponding to node
    splice!(g.adj, node_index)

    #de-increment elements of g.adj > node_index
    for elem in g.adj
        for alter in elem
            if alter > node_index
                delete!(elem, alter)
                push!(elem, alter-1)
            end
        end
    end

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
end

function remove_edge!{T}(g::Graph{T}, edge::(Int64, Int64))
    e1 = edge[1]
    e2 = edge[2]

    delete!(g.adj[e1], e2)
    delete!(g.adj[e2], e1)
end


#misc

function degree(g::Graph)
    deg = zeros(Int64, g.size)

    for vertex in index_iter(g)
        deg[vertex] = length(g.adj[vertex])
    end
    return deg
end


function bfs(adj::Array{Set{Int64}}, node_index::Int64)
    seen = Set{Int64}()
    to_traverse = Int64[]

    push!(to_traverse, node_index)
    push!(seen, node_index)

    while length(to_traverse) > 0
        t = pop!(to_traverse)

        for vertex in adj[t]
            if in(vertex, seen) == false
                push!(to_traverse, vertex)
                push!(seen, vertex)
            end
        end
    end
    return seen
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
    return sort(components, by = x -> length(x), rev = true)
end


##path length algorithms

init_dist(size::Int64) = [Inf for x in 1:size]
init_prev(size::Int64) = [-1 for x in 1:size]

function dijkstra{T}(g::Graph{T}, source::T)

    source_index = get_index(g, source)
    dist = init_dist(g.size)
    prev = init_prev(g.size)

    sizehint(Q) = g.size

    Q = PriorityQueue{Int64, Union(Int64, Float64)}()

    for node in index_iter(g)
        enqueue!(Q, node, Inf)
    end

    #set source manually to 0
    Q[source_index] = 0
    dist[source_index] = 0

    while length(Q) > 0
        u = dequeue!(Q)

        if dist[u] == Inf
            break
        end

        for v in g.adj[u]

            #the 1 is really edge length, but they're all 1 here
            alt = dist[u] + 1

            if alt < dist[v]
                dist[v] = alt
                prev[v] = u
                Q[v] = alt
            end
        end
    end
    return dist
end

function range_targ{T}(g::Graph{T}, source::Int64, target::Int64)

    visited = BitVector(g.size)

    node_queue = Set{Int64}()
    for v in neighbors(g, source)
        if !is(v, target)
            push!(node_queue, v)
            visited[v] = true
        end
    end

    tie_len = 2

    while !isempty(node_queue)
        next_node_queue = Set{Int64}()
        for nbr in node_queue
            v_set = neighbors(g, nbr)
            for v in v_set
                if is(v, target)
                    return tie_len
                end
                if !visited[v]
                    push!(next_node_queue, v)
                    visited[v] = true
                end
            end
        end
        node_queue = next_node_queue
        tie_len += 1
    end
    return - 1
end


function tie_range{T}(g::Graph{T}) #for undirected
    edges = get_edges(g)
    ranges = [0 for x in 1:length(edges)]

    for edge_num in 1:length(edges)
        e1, e2 = edges[edge_num]
        if e1 < e2
            remove_edge!(g, edges[edge_num])
            ranges[edge_num] = range_targ(g, e1, e2)
            add_edge!(g, (get_name(g, e1), get_name(g,e2)))
        end
    end
    return edges, ranges
end