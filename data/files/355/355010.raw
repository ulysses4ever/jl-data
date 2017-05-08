# implements a rollout policy
module RolloutPolicies

using DiscreteMDPs

export RolloutPolicy
export action

import DiscreteMDPs.Policy
import DiscreteMDPs.action


type RolloutPolicy <: Policy
    d::Int64               # search depth
    n::Int64               # number of iterations
    c::Float64             # explortaion constant
    Q::Vector{Float64}     # Q values at the root state
    N::Vector{Int64}       # Number of visits to each state
    actions::Vector{Int64} # Vector of allowable actions
    mdp::DiscreteMDP      
end

function RolloutPolicy(mdp::DiscreteMDP; d::Int64=20, n::Int64=100, c::Float64=0.1)
    nActions = numActions(mdp)
    Q = zeros(nActions)
    N = zeros(Int64, nActions)
    actions = [1:nActions]
    return RolloutPolicy(d, n, c, Q, N, actions, mdp)
end


function action(policy::RolloutPolicy, sIdx::Int64)
    n = policy.n
    fill!(policy.Q, 0.0)
    fill!(policy.N, 0)
    for i = 1:n
        simulate(policy, sIdx)
    end
    a = policy.actions
    return a[indmax(policy.Q)]
end


function simulate(policy::RolloutPolicy, s::Int64)
    Q = policy.Q
    N = policy.N
    c = policy.c
    d = policy.d
    actions = policy.actions
    mdp = policy.mdp
    discount = mdp.discount
    i = indmax(Q + c .* real(sqrt(complex(log(sum(N)) ./ N))))
    a = actions[i]
    sp = nextState(mdp, s, a)
    q = reward(mdp, s, a) + discount*rollout(policy, sp, d)
    N[i] += 1
    Q[i] += (q - Q[i]) / N[i]
    return 
end


function rollout(policy::RolloutPolicy, s::Int64, depth::Int64)
    mdp = policy.mdp
    discount = mdp.discount
    if depth == 0
        return 0.0
    else
        a  = getAction(mdp, s)
        sp = nextState(mdp, s, a)
        return reward(mdp, s, a) + discount*rollout(policy, sp, depth-1)
    end
end

end # module
