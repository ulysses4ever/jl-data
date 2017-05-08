# 
# CGRASP.jl
# Implementation of the Continuous GRASP optimization method
#
# Andrei de A. Formiga, 2013-04-27
#

### Utility functions

# return a vector of size n with floats uniformly distributed between l and u
function UnifRand(l, u)
    return (rand(length(l)) .* (u .- l)) .+ l
end

# build an IntSet based on a range
function BuildSet(r::Range1{Int})
    res = IntSet()
    for i in r
        add!(res, i)
    end

    res
end

function RandomlySelectElement(is)
    is[rand(1:length(is))]
end

function LineSearch(x, h, i, n, f, l, u)
    xcopy = x
    x[i] = l[i]
    fmin = Inf

    while xcopy[i] <= u[i]   # FIX: tolerance
        fx = f(xcopy)
        if fx < fmin
            fmin = fx
            xmin = xcopy[i]
        end
        xcopy[i] += h        
    end

    (xmin, fmin)
end


### Main algorithm routines

function ConstructGreedyRandomized(x, f, n, h, l, u, alpha)
    S = BuildSet(1:n)
    g = zeros(Float64, n)
    z = zeros(Float64, n)
    while !isempty(S)
        gmin = Inf
        gmax = -Inf
        for i in 1:n 
            if contains(S, i)
                z[i], g[i] = LineSearch(x, h, i, n, f, l, u)
                gmin = min(g[i], gmin)  # updates gmin and/or gmax if needed
                gmax = max(g[i], gmax)               
            end
        end
        RCL = Int[]
        threshold = ((1-alpha) * gmin + alpha * gmax)
        for i in 1:n 
            if contains(S, i) && g[i] <= threshold
                push!(RCL, i)
            end
        end
        j = RandomlySelectElement(RCL)
        x[j] = z[j]
        delete!(S, j)
    end
end

function LocalSearch(x, f, n, h, l, u, MaxDirToTry)
    
end

function CGRASP(n, l, u, f, MaxIters, MaxNumIterNoImprov, runs, MaxDirToTry, alpha)
    assert(length(l) == length(u))

    fbest = Inf
    for j in 1:runs
        h = 1
        x = UnifRand(l, u)
        noImprov = 0
        for iter in 1:MaxIters
            ConstructGreedyRandomized(x, f, n, h, l, u, alpha)
            x = LocalSearch(x, f, n, h, l, u, MaxDirToTry)
            fx = f(x)
            if fx < fbest
                xbest = x
                fbest = fx
                noImprov = 0
            else
                noImprov += 1
            end
            if noImprov > MaxNumIterNoImprov
                h = h / 2
                noImprov = 0
            end
        end
    end
    
    xbest
end
