##path length algorithms

init_dist(size::Int64) = [Inf for x in 1:size]
init_prev(size::Int64) = [-1 for x in 1:size]

function make_queue(indicies::Vector{Int64})
    sizehint(Q) = length(indicies)
    Q = PriorityQueue{Int64, Union(Int64, Float64)}()

    for node in indicies
        enqueue!(Q, node, Inf)
    end

    return Q
end

function dijkstra{T}(g::Graph{T}, source::T)

    source_index::Int64 = get_index(g, source)
    dist::Array{Float64, 1} = init_dist(g.size)
    #prev::Array{Int64, 1} = init_prev(g.size)

    Q = make_queue(index_list(g))

    #set source manually to 0
    Q[source_index] = 0
    dist[source_index] = 0

    while length(Q) > 0
        u::Int64 = dequeue!(Q)

        if dist[u] == Inf
            break
        end

        for v in g.adj[u]

            #the 1 is really edge length, but they're all 1 here
            alt::Int64 = dist[u] + 1

            if alt < dist[v]
                dist[v] = alt
                #prev[v] = u
                Q[v] = alt
            end
        end
    end
    return dist
end
