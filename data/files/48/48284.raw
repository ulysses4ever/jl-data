include("approximate.jl")
include("file.jl")

using DataFrames
using MDPs

# ============
# Data loading
# ============
filename = "data/small"
# filename = "data/medium"
standardize = grid2standard

println(@sprintf("Reading data from %s", filename))
data = readtable(@sprintf("%s.csv", filename))
# datamedium = readtable("data/medium.csv")
# datahuge = readtable("data/huge.csv")

println("Loading variables")
data = standardize(data)
S, A, nxt, T, R = getAttributes(data)

println("Loading MDP")
mdp = DiscreteMDP(S, A, nxt, T, R; discount=0.99)
U, n = valueIteration(mdp)

println("Dumping policy")
policy = bestAction(mdp, U)
dump(@sprintf("%s.policy", filename), policy)
