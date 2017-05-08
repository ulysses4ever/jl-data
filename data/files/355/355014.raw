push!(LOAD_PATH, "/Users/megorov/Desktop/projects/stanford/sniper/egorov/sniperRepo/new-version")

using Collada_
using UrbanMap_
using SniperPOMDP_
using SniperMDP_
using ValueIterations
using Helpers
using RayCaster_
using Simulator
using SimServers
using RolloutPolicies


map = UrbanMap(1, [0.5], [0.5], [0.42], [0.22], 10, 10)
#t   = [(2.0,8.0), (2.0,1.0), (5.0,2.0), (7.0,3.0)]
t   = [(2.0,8.0), (2.0,1.0)]
#t   = [(7.0,7.0), (2.0,14.0), (8.0,4.0), (11.0,13.0)]
mdp = SniperMDP(map, nSnipers = 1, nMonitors = 2, targets=t)

policy = RolloutPolicy(mdp, d=10, n=3000, c=0.4)

# create the simulation type
#init  = 8_888_888_803 # sniper at (3,1), all monitors at (9,9)
init = 470_872
sim  = MDPSimulation(mdp, init, 100)

# set up the server
socket = 4444
server = SniperServer(socket)

# begin simulation and send results to client
#simAndSend(server, sim, mdp, policy)

# batch sim
nSims = 10
obs = zeros(Int64, nSims)
kills = zeros(Int64, nSims)
rewards = zeros(n)

for i = 1:nSims
    println("On sim: $i")
    res = simulate(policy, mdp, 100, initState=init)
    rewards[i] = sum(res.rewards)
    obs[i] = res.nObs
    kills[i] = res.nKills
end
