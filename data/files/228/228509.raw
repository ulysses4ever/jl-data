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