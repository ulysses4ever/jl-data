
# for pomcp solver
function sparse_actions(pomdp::CommunityAffiliationPOMDP, s::CommunityNetwork, b::RevealedGraph, n::Int)
    @assert n <= 0 # doesn't work with a limited number of actions
    if s.budget > 0
        # println("ProbeNode actions (budget=$(s.budget))")
        return [ProbeNode(i) for i in b.revealed_nodes]
    else
        # println("GuessAffiliation actions (budget=$(s.budget))")
        return [GuessAffiliation(i) for i in 1:b.n_comms]
    end
end
