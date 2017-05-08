module NetworkDiscovery

using LightGraphs
import LightGraphs: add_edge!, neighbors, degree
import POMDPs: POMDP
import POMDPs: reward
import POMDPs: create_state, create_transition_distribution, transition
import POMDPs: create_observation, create_observation_distribution, observation
import POMDPs: Belief, belief, create_belief
import POMDPs: Policy, action, create_action
import POMDPs: AbstractDistribution
import POMDPs: initial_belief, isterminal
import POMDPs: discount
import POMCP: sparse_actions

export CommunityNetwork, CommunityAffiliationPOMDP
export ProbeNode, GuessAffiliation
export Neighborhood

export DiscoveryHeuristic, RevealedGraph
export ProbeHighestDegree, GuessBasedOnNeighbors

export generate_network, generate_problem

# state
type CommunityNetwork <: Belief
    graph::Graph
    n_comms::Int
    labels::Vector{Int}
    budget::Int
    CommunityNetwork() = new()
end

# pomdp
type CommunityAffiliationPOMDP <: POMDP
    budget::Int
    node::Int
    reward::Float64
    true_network::CommunityNetwork
    known_nodes::Set{Int}
    known_edges::Set{Edge}
    known_labels::Dict{Int,Int}
    p_intra::Float64
    p_inter::Float64
end
Base.length(p::CommunityAffiliationPOMDP) = length(p.true_network.graph.vertices)

isterminal(::CommunityAffiliationPOMDP, s::CommunityNetwork) = s.budget < 0

# actions
create_action(pomdp::CommunityAffiliationPOMDP) = nothing
type ProbeNode
    node::Int
    ProbeNode()=new()
    ProbeNode(i)=new(i)
end
type GuessAffiliation
    community::Int
    GuessAffiliation()=new()
    GuessAffiliation(i)=new(i)
end

# reward
reward(p::CommunityAffiliationPOMDP, s, a::ProbeNode) = 0.0
function reward(p::CommunityAffiliationPOMDP, s, a::GuessAffiliation)
    return p.reward*(a.community==s.labels[p.node])
end

# state transitions
create_state(::CommunityAffiliationPOMDP) = CommunityNetwork()
create_transition_distribution(p::CommunityAffiliationPOMDP) = CommunityNetwork()
function transition(p::CommunityAffiliationPOMDP, s, a, d=create_transition_distribution(p))
    d.graph = s.graph
    d.n_comms = s.n_comms
    d.labels = s.labels
    d.budget = s.budget-1
    return d
end
function Base.rand!(rng::AbstractRNG, s, d::CommunityNetwork)
    s.graph = d.graph
    s.n_comms = d.n_comms
    s.labels = d.labels
    s.budget = d.budget
end

# observations
type Neighborhood <: AbstractDistribution
    neighbors::Vector{Int}
    Neighborhood() = new()
end
create_observation(::CommunityAffiliationPOMDP) = Neighborhood()
create_observation_distribution(::CommunityAffiliationPOMDP) = Neighborhood()
function observation(p::CommunityAffiliationPOMDP, s, a::ProbeNode, d=create_observation_distribution(p))
    d.neighbors = neighbors(s.graph, a.node)
    return d
end
function observation(p::CommunityAffiliationPOMDP, s, a::GuessAffiliation, d=create_observation_distribution(p))
    d.neighbors = []
    return d
end
function Base.rand!(rng::AbstractRNG, o, d::Neighborhood)
    o.neighbors = d.neighbors
end

discount(::CommunityAffiliationPOMDP) = 1.0

include("heuristic_belief.jl")
include("heuristics.jl")
include("pomdp.jl")
include("problems.jl")
include("visualization.jl")

end # module
