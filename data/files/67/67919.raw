# 
# CGRASP.jl
# Implementation of the Continuous GRASP optimization method
#
# Andrei de A. Formiga, 2013-04-27
#

# return a vector of size n with floats uniformly distributed between l and u
function UnifRand(l, u)
    return (rand(length(l)) .* (u .- l)) .+ l
end

function CGRASP(n, l, u, f, MaxIters, MaxNumIterNoImprov, runs, MaxDirToTry, alpha)
    assert(length(l) == length(u))

    bestVal = Inf
    for j in 1:runs
        h = 1
        x = UnifRand(l, u)
        noImprov = 0
        for iter in 1:MaxIters
            x = ConstructGreedyRandomized(x, f, n, h, l, u, alpha)
        end
    end
end
