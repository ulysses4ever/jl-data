##functions range_target, tie_range mostly written by Chris Cameron (github: @chrisjcameron)
##used with permission

function range_target{T}(g::Graph{T}, source::Int64, target::Int64)

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
    return -1
end


function tie_range{T}(g::Graph{T}) #for undirected
    edges = get_edges(g)
    ranges = [0 for x in 1:length(edges)]

    for edge_num in 1:length(edges)
        e1, e2 = edges[edge_num]
        if e1 < e2
            remove_edge!(g, edges[edge_num])
            ranges[edge_num] = range_target(g, e1, e2)
            add_edge!(g, (get_name(g, e1), get_name(g,e2)))
        end
    end
    return edges, ranges
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