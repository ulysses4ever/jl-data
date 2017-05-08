module JinGen

export JinGenParams, JinGenBuilder, FlawedJinGen, generate

using RouletteWheels
using Compat

immutable JinGenParams
    r_0::Float64
    r_1::Float64
    γ::Float64
    z_star::Int
    barrier_iters::Int
    n::Int
end

JinGenParams(n) = JinGenParams(
    0.0005, 2.0, 0.005, 5, 1, n
)

immutable JinGenBuilder
    params::JinGenParams
    
    edges::Set{Tuple{Int,Int}}
    adj_list::Dict{Int,Vector{Int}}
    degrees::RouletteWheel
    mutual_meet_factors::RouletteWheel
    num_pairs::Int
    n_meetings::Int
    
    function JinGenBuilder(params)
        freqs = zeros(Int, params.n)
        num_pairs = @compat(round(Int, params.n * (params.n - 1) / 2))
        new(
            params,
            @compat(Set{Tuple{Int,Int}}()),
            @compat((Int => Vector{Int})[i => Vector{Int}() for i in 1:params.n]),
            StochasticAcceptance(freqs),
            StochasticAcceptance(freqs),
            num_pairs,
            @compat(round(Int, num_pairs * params.r_0))
        )
    end
end

"""
    :return: a random number, i, in [0, n), except for i == excluding.
"""
function random_idx(n, excluding)
    selected = excluding
    r = 1:n
    while selected == excluding
        selected = rand(r)
    end
    return selected
end
    
"""
    :return: a tuple of (i, j) representing an edge in a network of [0, n)
             nodes. This tuple has the property of i < j, forall edges.
"""
function random_edge_as_indices(n)
    a = rand(1:n)
    b = random_idx(n, a)
    
    # The following constraint is useful. Consider a set of edges in a
    # undirected graph. In this case, (1, 2) is semantically equivalent to
    # (2, 1). But, from the perspective of a set, these tuples are unique.
    # Using the canonical form of smaller number first enforces the correct
    # semantics.
    return a < b ? (a, b) : (b, a)  
end

"""
:return: A unique pair of randomly selected nodes in edge canonical form.
"""
function random_pair_from_list(nodes)
    i, j = random_edge_as_indices(length(nodes))
    a, b = nodes[i], nodes[j]

    return a < b ? (a, b) : (b, a)  # Canonical form.
end

############################################################################
# All add and remove operations on edges must use add_edge! and remove_edge!
# respectively. They maintain the set of edges, as expected. They
# also maintain the degrees and mutual meet factors (i.e. k * (k-1)) for
# each node. 
#
# Both these functions require edges in canonical form. That is, the smaller
# index must come first in the pair of indices representing the edge.
############################################################################

function inc_edge!(jingen::JinGenBuilder, a, b)
    push!(jingen.adj_list[a], b)
    jingen.degrees[a] += 1
    k = jingen.degrees[a]
    jingen.mutual_meet_factors[a] = k * (k - 1)
end

function add_edge!(jingen, edge)
    assert(edge[1] < edge[2])

    push!(jingen.edges, edge)
    inc_edge!(jingen, edge[1], edge[2])
    inc_edge!(jingen, edge[2], edge[1])
end

function dec_edge!(jingen::JinGenBuilder, a, b)
    deleteat!(
        jingen.adj_list[a], 
        findfirst(jingen.adj_list[a], b) # FIX: XXX: High z* problem
    )
    jingen.degrees[a] -= 1
    k = jingen.degrees[a]
    jingen.mutual_meet_factors[a] = k * (k - 1)
end

function remove_edge!(jingen, edge)
    assert(edge[1] < edge[2])

    delete!(jingen.edges, edge)
    dec_edge!(jingen, edge[1], edge[2])
    dec_edge!(jingen, edge[2], edge[1])
end

# From Jin et al (2001):
#   If a pair meet and there is not already a connection between them, a new
#   connection is established unless one of them already has z* connections,
#   in which case nothing happens. In other words, z* forms a hard upper
#   limit on the degree z of any vertex, beyond which no more edges can
#   be added.
function connection_can_be_made(jingen, edge)
    if edge in jingen.edges
        return false
    end
        
    a, b = edge
    return (
        jingen.degrees[a] < jingen.params.z_star &&
        jingen.degrees[b] < jingen.params.z_star
    )
end

# From Jin et al (2001):
#   At each time-step, we choose $n_p * r_0$ pairs of vertices
#   uniformly at random from the network to meet. If a pair 
#   meet who do not have a pre-existing connection, and if neither
#   of them has the maximum number of z* connections then a new 
#   connection is established between them.
function meet_randomly(jingen)
    for _ in 1:jingen.n_meetings
        edge = random_edge_as_indices(jingen.params.n)
        if connection_can_be_made(jingen, edge)
            add_edge!(jingen, edge)
        end
    end
end


# From Jin et al (2001):
#   At each time-step, we choose $n_m * r_1$ vertices at random, with
#   probabilities proportional to $z_i(z_i-1)$. For each vertex chosen
#   we randomly choose one pair of its neighbors to meet, and establish 
#   a new connection between them if they do not have a pre-existing
#   connection and if neither of them already has the maximum number
#   z* of connections.
function introduce_friends(jingen)
    num_mutual = @compat round(Int, 0.5 * sum(jingen.mutual_meet_factors))
    n_introductions = @compat round(Int, num_mutual * jingen.params.r_1)
        
    for _ in 1:n_introductions
        ego = rand(jingen.mutual_meet_factors)
        alters = jingen.adj_list[ego]
            
        # You can't introduce your friends if you only have 1 or none.
        # But, this property is true by the random proportional selection
        # algorithm. k * (k - 1) = 0 for k = 0 and k = 1. I don't have 
        # to check it in production code.
        assert(length(alters) >= 2)

        edge = random_pair_from_list(alters)
        if connection_can_be_made(jingen, edge)
            add_edge!(jingen, edge)
        end
    end
end

function lose_touch(jingen)
    n_lost = @compat round(Int, (length(jingen.edges) * jingen.params.γ))
    for _ in 1:n_lost
        ego = rand(jingen.degrees)
        alter = rand(jingen.adj_list[ego])
        edge = ego < alter ? (ego, alter) : (alter, ego)
        remove_edge!(jingen, edge)
    end
end

function noop(i, jingen)
end

function generate(jingen::JinGenBuilder, iterations=30000, callback=noop)
    for i in 1:iterations
        meet_randomly(jingen)
        introduce_friends(jingen)
        if i > jingen.params.barrier_iters
            lose_touch(jingen)
        end

        callback(i, jingen)
    end
    
    return jingen.edges
end

# See: https://github.com/jbn/agents/blob/6eef634f80fa048e4c2fc5c62d85b384545b0e02/Repast%20J/demos/src/uchicago/src/repastdemos/jinGirNew/JinGirNewModelII.java
immutable FlawedJinGen
    builder::JinGenBuilder
end

function lose_touch(flawed::FlawedJinGen)
    jingen = flawed.builder
    n_lost = @compat round(Int, (length(jingen.edges) * jingen.params.γ))
    for _ in 1:n_lost
        ego = rand(jingen.mutual_meet_factors)  # This is wrong
        alter = rand(jingen.adj_list[ego])
        edge = ego < alter ? (ego, alter) : (alter, ego)
        remove_edge!(jingen, edge)
    end
end

function generate(flawed::FlawedJinGen, iterations=30000, callback=noop)
    jingen = flawed.builder
    for i in 1:iterations
        meet_randomly(jingen)
        introduce_friends(jingen)
        if i > jingen.params.barrier_iters
            lose_touch(flawed)
        end

        callback(i, jingen)
    end
    
    return jingen.edges
end


end 
