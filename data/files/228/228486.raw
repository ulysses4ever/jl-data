##functions range_target, tie_range mostly written by Chris Cameron (github: @chrisjcameron)
##used with permission

function make_queue(nbrs::Set{Int64}, size::Int64, target::Int64)
    visited::BitVector = BitVector(size)

    node_queue::Vector{Int64} = Int64[]
    for v in nbrs
        if !is(v, target)
            push!(node_queue, v)
            visited[v] = true
        end
    end
    return visited, node_queue
end

function range_target{T}(g::Graph{T}, source::Int64, target::Int64, tie_len::Int64)

    visited, node_queue = make_queue(neighbors(g, source), g.size, target)

    while length(node_queue) > 0
        next_node_queue = Int64[]
        for nbr in node_queue
            v_set::Set{Int64} = neighbors(g, nbr)
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
        node_queue::Vector{Int64} = next_node_queue
        tie_len += 1
    end
    return -1
end


function tie_range{T}(g::Graph{T}) #for undirected
    edges::Array{(Int64,Int64), 1} = get_edges(g)
    ranges::Array{Int64, 1} = [0 for x in 1:length(edges)]

    tie_len::Int64 = 2

    for edge_num in 1:length(edges)
        e1::Int64, e2::Int64 = edges[edge_num]
        if e1 < e2
            remove_edge!(g, edges[edge_num])
            ranges[edge_num] = range_target(g, e1, e2, tie_len)
            add_edge_index!(g, e1, e2)
        end
    end
    return edges, ranges
end
