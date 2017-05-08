

function generate_network(rng::AbstractRNG, n_nodes::Int, n_comms::Int, p_intra_community::Float64, p_inter_community::Float64)
    network = CommunityNetwork()
    network.graph = Graph(n_nodes)
    network.n_comms = n_comms
    network.labels = Array(Int, n_nodes)
    for i in 1:n_nodes
        network.labels[i] = ceil(rand(rng)*n_comms)
    end
    # generate with SBM
    for i in 1:n_nodes
        for j in i+1:n_nodes
            if network.labels[i] == network.labels[j]
                if rand(rng) < p_intra_community
                    add_edge!(network.graph, i, j)
                end
            else
                if rand(rng) < p_inter_community
                    add_edge!(network.graph, i, j)
                end
            end
        end
    end
    return network
end

function generate_problem(rng::AbstractRNG, net::CommunityNetwork, budget::Int, node::Int, reward::Float64, n_known_labels::Int, n_known_edges::Int, p_intra::Float64, p_inter::Float64)
    problem = CommunityAffiliationPOMDP(budget,
                                        node,
                                        reward,
                                        net,
                                        Set{Int}(),
                                        Set{Edge}(),
                                        Dict{Int,Int}(),
                                        p_intra,
                                        p_inter)


    problem.true_network.budget = budget
                                        
    edge_vector = collect(net.graph.edges)
    available = ones(Bool, length(edge_vector))
    for i in 1:n_known_edges
        r = ceil(rand(rng)*sum(available))
        ed = edge_vector[available][r]
        push!(problem.known_edges, ed)
        push!(problem.known_nodes, ed.first)
        push!(problem.known_nodes, ed.second)
        available[available][r] = false
    end

    node_vector = collect(problem.known_nodes)
    available = ones(Bool, length(node_vector))
    available[find(n->(n==node),node_vector)] = false
    for i in 1:n_known_labels
        r = ceil(rand(rng)*sum(available))
        n = node_vector[available][r]
        problem.known_labels[n] = problem.true_network.labels[n]
        available[available][r] = false
    end

    return problem
end
