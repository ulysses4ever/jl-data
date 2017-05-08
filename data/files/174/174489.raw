# heuristic container
type DiscoveryHeuristic <: Policy
    probing::Policy
    guess::Policy
end
function action(pomdp::CommunityAffiliationPOMDP, p::DiscoveryHeuristic, b::Belief, act=create_action(pomdp))
    if b.budget > 0
        return action(pomdp, p.probing, b)
    else
        return action(pomdp, p.guess, b)
    end
end

# probing heuristics
type ProbeHighestDegree <: Policy
    target_first::Bool
end
ProbeHighestDegree() = ProbeHighestDegree(false)
function action(pomdp::CommunityAffiliationPOMDP, p::ProbeHighestDegree, b::RevealedGraph, a::ProbeNode=ProbeNode())
    if p.target_first && !(pomdp.node in b.probed)
        a.node = pomdp.node
    else
        node_vector = collect(setdiff(b.revealed_nodes, b.probed))
        a.node = node_vector[indmax([degree(b,n) for n in node_vector])]
    end
    return a
end

# guessing heuristic
type GuessBasedOnNeighbors <: Policy
    rng::AbstractRNG
end
function action(pomdp::CommunityAffiliationPOMDP, p::GuessBasedOnNeighbors, b::RevealedGraph, a::GuessAffiliation=GuessAffiliation())
    # guess neighbors affiliation
    ns = neighbors(b, pomdp.node)
    labels = Array(Int, length(ns))
    guessed = zeros(Bool, length(ns))
    for i in 1:length(ns)
        if haskey(b.known_labels, ns[i])
            labels[i] = b.known_labels[ns[i]]
            guessed[i] = true
        else
            label_sums = zeros(Int, pomdp.true_network.n_comms)
            nns = neighbors(b, ns[i])
            for n in nns 
                if haskey(b.known_labels, n)
                    label_sums[b.known_labels[n]] += 1
                end
            end
            maxcount = maximum(label_sums)
            if maxcount > 0
                guessed[i] = true
                cand = find(x->(x==maxcount), label_sums)
                labels[i] = cand[ceil(rand(p.rng)*length(cand))]
            end
        end
    end
    if any(guessed)
        bins,counts = hist(labels[guessed], 0:pomdp.true_network.n_comms)
        # assert bins == 1:pomdp.n_comms
        maxcount = maximum(counts)
        cand = find(x->(x==maxcount), counts)
        a.community = cand[ceil(rand(p.rng)*length(cand))]
    else
        a.community = ceil(rand(p.rng)*pomdp.true_network.n_comms)
    end
    return a
end
