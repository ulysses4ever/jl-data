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
using PolicyAssignment


map = UrbanMap(1, [0.5], [0.5], [0.42], [0.22], 10, 10)
mapPath = "/Users/megorov/Desktop/projects/stanford/sniper/egorov/sniperRepo/new-version/maps/demo_map_border2D.dae"
coll = ColladaObjects(mapPath)
#map = UrbanMap(coll, 15, 15) # 15x15 map

#t   = [(2.0,8.0), (2.0,1.0), (5.0,2.0), (7.0,3.0)]
t   = [(2.0,8.0), (2.0,1.0)]
#t   = [(7.0,7.0), (2.0,14.0), (8.0,4.0), (11.0,13.0)]
mdp = SniperMDP(map, nSnipers = 1, nMonitors = 2, targets=t)

p1 = load_policy("policies/mdp-1.policy")
p2 = load_policy("policies/mdp-2.policy")
p3 = load_policy("policies/mdp-3.policy")
p4 = load_policy("policies/mdp-4.policy")


#policies = merge(p1.policy,p2.policy,p3.policy,p4.policy)
policies = merge(p1.policy,p2.policy)
#values   = merge(p1.V,p2.V,p3.V,p4.V)
values   = merge(p1.V,p2.V)

policy = AssignmentPolicy(2, policies, values, mdp)

# create the simulation type
#init  = 8_888_888_803 # sniper at (3,1), all monitors at (9,9) for 10x10 4 agent world
#init = 97 # sniper at (7,7), all monitors at (1,1) for 15x15 4 agent world
#init = 20_583_164_347 # sniper at (7,7), all monitors at (1,i) for 15x15 4 agent world
init = 480_872 
sim  = MDPSimulation(mdp, init, 100)

# set up the server
socket = 4444
server = SniperServer(socket)

# begin simulation and send results to client
#simAndSend(server, sim, mdp, policy)


# begin batch sim
n = 10
rewards = zeros(n)
shot    = zeros(Int64, n)
obs     = zeros(Int64, n)
for i = 1:n
    res = simulate(policy, mdp, 100, initState=init) 
    rewards[i] = sum(res.rewards)
    shot[i]    = res.nKills
    obs[i]     = res.nObs
end

