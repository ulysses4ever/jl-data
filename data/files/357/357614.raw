using LightGraphs


type MyDiGraph
    adjmx::Matrix
    g::LightGraphs.DiGraph
    n::Int
    MyDiGraph(adjmx, g, n) = new(adjmx, g, n)

    is_strongly_connected
    period
    cyclic_components_proj::Array
end


function MyDiGraph{T}(adjmx::Matrix{T})
    n = size(adjmx, 1)

    adjmx_diag_zeros = copy(adjmx)
    for i in 1:n
        adjmx_diag_zeros[i, i] = 0
    end

    g = LightGraphs.DiGraph(adjmx_diag_zeros)

    return MyDiGraph(adjmx, g, n)
end


function is_strongly_connected(g::MyDiGraph)
    if !isdefined(g, :is_strongly_connected_components)
        sccs = LightGraphs.strongly_connected_components(g.g)
        g.is_strongly_connected = (length(sccs) == 1)
    end
    return g.is_strongly_connected
end


function period(g::MyDiGraph)
    if !isdefined(g, :period)
        compute_period(g)
    end

    return g.period
end


function is_aperiodic(g::MyDiGraph)
    return (period(g) == 1)

end


function cyclic_components(g::MyDiGraph)
    if is_aperiodic(g)
        return Array[[1:g.n]]
    else
        return [find(x -> x == k, g.cyclic_components_proj)
                for k in 0:g.period-1]
    end
end


function compute_period(g::MyDiGraph)
    # Not defined for a non strongly-connected digraph
    is_strongly_connected(g) || throw(DomainError())

    if any(diag(g.adjmx) .> 0)
        g.period = 1
        g.cyclic_components_proj = ones(Int, g.n)
        return Nothing
    end

    # Use the algorithm described in:
    # J. P. Jarvis and D. R. Shier,
    # "Graph-Theoretic Analysis of Finite Markov Chains," 1996.

    root = 1
    g_bfs_tree = LightGraphs.bfs_tree(g.g, root)
    level = LightGraphs.gdistances(g_bfs_tree, root)
    g_non_bfs_tree = LightGraphs.difference(g.g, g_bfs_tree)

    # Determine the period
    d = 0
    for (node_from, node_to) in LightGraphs.edges(g_non_bfs_tree)
        value = level[node_from] - level[node_to] + 1
        d = gcd(d, value)
        if d == 1
            g.period = 1
            g.cyclic_components_proj = ones(Int, g.n)
            return Nothing
        end
    end

    g.period = d
    g.cyclic_components_proj = level % d
end
