push!(LOAD_PATH, "/Users/megorov/Desktop/projects/stanford/sniper/egorov/sniperRepo/new-version")

using UrbanMap_
using SniperMDP_
using ValueIterations
using Simulator
using SimServers


# create a map and the MDP
map = UrbanMap(1, [0.5], [0.5], [0.42], [0.22], 10, 10)
mdp = SniperMDP(map, nSnipers = 1, nMonitors = 2, targets=[(2.0,8.0), (2.0,1.0)])

# load the policy
policy = load_policy("policies/mmdp-10-iter-1.policy")

# set up the server
socket = 4444
server = SniperServer(socket)

# create the simulation type
init = 470872
sim  = MDPSimulation(mdp, init, 100)

# begin simulation and send results to client
#simAndSend(server, sim, mdp, policy)

# begin batch sim
n = 500
rewards = zeros(n)
shot    = zeros(Int64, n)
obs     = zeros(Int64, n)
for i = 1:n
    res = simulate(policy, mdp, 100, initState=init) 
    rewards[i] = sum(res.rewards)
    shot[i]    = res.nKills
    obs[i]     = res.nObs
end
