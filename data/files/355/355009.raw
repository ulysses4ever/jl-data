# implements a multi-agent policy assignment strategy
module PolicyAssignment

using DiscreteMDPs
using JuMP
using Gurobi

export AssignmentPolicy
export action
export merge

import DiscreteMDPs.Policy
import DiscreteMDPs.action


typealias SingleAgentPolicy Vector{Int64}
typealias SingleAgentValues Vector{Float64}


# this is an online policy
# TODO: only works for a single sniper and multiple target/monitor startegy
type AssignmentPolicy <: Policy
    nAgents::Int64
    policies::Vector{SingleAgentPolicy}
    values::Vector{SingleAgentValues}
    mdp::DiscreteMDP
end


function action(policy::AssignmentPolicy, sIdx::Int64)
    mdp      = policy.mdp
    nAgents  = policy.nAgents
    nActions = mdp.nFactoredActions # need this to get the final action
    p        = policy.policies
    v        = policy.values
    ds       = mdp.map.xSize

    # c[1,:] the values for all policies for a given agent
    c = zeros(nAgents, nAgents)
    saIdxs = zeros(Int64, nAgents) # single agent state indices
    saActions = zeros(Int64, nAgents) # single agent actions
    aSub = zeros(Int64, nAgents) + nActions # for combinig single agent actions
    dimSub = zeros(Int64, nAgents) + ds # only works for single sniper problems

    # get positions from sIdx
    i2x!(mdp, sIdx)
    x = mdp.tempSub1
    sp = [x[1], x[2]]
    # combine positions of sniper and each monitor to get single agent positions
    ai = 3 # agent counter assumes single sniper
    for i = 1:nAgents # assumes single sniper
        mp = [x[ai], x[ai+1]] 
        cp = [sp, mp] # combined position
        # convert positions to idx
        sa = sub2ind(dimSub, cp) # state of single agent
        saIdxs[i] = sa
        for j = 1:nAgents
            # fill the value matrix
            c[i,j] = v[j][sa]
        end
        ai += 2
    end

    y = assignment(policy, c)
    for i = 1:nAgents
        pp = indmax(y[i,:]) # policy to be assigned to an agent
        sa = saIdxs[i]
        saActions[i] = p[pp][sa]
    end

    return sub2ind(aSub, saActions)
end


# return individual actions for each agent
function assignment(policy::AssignmentPolicy, c::Matrix)
    # c is value-policy matrix
    n = policy.nAgents 
    m = Model(solver=GurobiSolver())
    # define the assignment matrix
    @defVar(m, 0 <= y[1:n,1:n] <= 1, Int)
    # the objective is double sum over the c and y values
    @setObjective(m, Max, sum{c[i,j]*y[i,j], i = 1:n, j = 1:n})
    # column and row constraints
    @addConstraints m begin
        col[i=1:n], sum(y[i,:]) == 1
        row[j=1:n], sum(y[:,j]) == 1
    end
    status = solve(m)
    # assign a policy to each agent based on y
    return getValue(y)
end


function merge{T}(a::Vector{T}...)
    l = length(a)
    n = [a[i] for i = 1:l]
    return n
end

end # module
