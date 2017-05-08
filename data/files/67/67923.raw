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

function Ternary(n)
    result = Int[]
    while n != 0
        digit = mod(n, 3)
        if digit == 2
            push!(result, -1)
        else
            push!(result, digit)
        end
        n = div(n, 3)
    end
    result
end

function GenerateRandomDirection(directions)
    ix = rand(1:length(directions))
    res = directions[ix]
    delete!(directions, ix)
    res
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
    improved = true
    xbest = x
    fbest = f(x)
    NumDirToTry = min(3^n - 1, MaxDirToTry)
    D = Int[]
    otherDirections = [1:(3^n-1)]
    while improved
        improved = false
        while length(D) <= NumDirToTry && (not improved)
            r = GenerateRandomDirection(otherDirections)
            push!(D, r)
            d = Ternary(r)
            x = xbest .+ (h * d)
            if l <= x && x <= u
                fx = f(x)
                if fx < fbest
                    xbest = x
                    fbest = fx
                    D = Int[]
                    improved = true
                end
            end
        end
    end
    xbest
end

function CGRASP(n, l, u, f, MaxIters, MaxNumIterNoImprov, runs, MaxDirToTry, alpha)
    # verifies that dimensions agree
    @assert (length(l) == length(u)) && (length(l) == n)

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
