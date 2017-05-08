push!(LOAD_PATH, "/Users/megorov/Desktop/projects/stanford/sniper/egorov/sniperRepo/new-version")

using UrbanMap_
using Collada_
using SniperMDP_
using ValueIterations
using Simulator
using SimServers


mapPath = "/Users/megorov/Desktop/projects/stanford/sniper/egorov/sniperRepo/new-version/maps/demo_map_border2D.dae"
coll = ColladaObjects(mapPath)
map = UrbanMap(coll, 15, 15) # 15x15 map

mdp = SniperMDP(map, nSnipers = 1, nMonitors = 1, targets=[(2.0,14.0)])

vi = SerialSolver(maxIterations = 15)

policy = solve(vi, mdp, verbose=true)

#policy = load_policy("policies/demo-mdp-1.policy")
