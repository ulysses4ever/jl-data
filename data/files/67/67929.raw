# 
# CGRASP.jl
# Implementation of the Continuous GRASP optimization method
#
# Andrei de A. Formiga, 2013-04-27
#

#
# TODO
#
#  1. Verify copies and references of vectors between functions
#  2. Check the grid subdivision with MaxIterNoImprov
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
    xmin = Inf

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

function Ternary(n, dim)
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
    
    # fill result with zeroes up until dim
    if length(result) < dim
        append!(result, zeros(Int, dim - length(result)))
    end

    result
end

function GenerateRandomDirection(directions)
    @assert length(directions) > 0

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

        # if no coordinates improve the solution, stop
        # TODO: check
        if length(RCL) == 0 
            return 
        end

        j = RandomlySelectElement(RCL)
        x[j] = z[j]
        delete!(S, j)
    end
end

function LocalSearch(x, f, n, h, l, u, MaxDirToTry)
    improved = true
    xbest = copy(x)
    fbest = f(x)
    fx = fbest
    NumDirToTry = min(3^n - 1, MaxDirToTry)
    D = Int[]
    otherDirections = [1:(3^n-1)]
    while improved
        improved = false
        while (length(D) < NumDirToTry) && !improved
            #print("|D| = $(length(D))\n")
            r = GenerateRandomDirection(otherDirections)
            push!(D, r)
            d = Ternary(r, n)
            #print(d)
            x = xbest .+ (h * d)
            if l <= x && x <= u
                fx = f(x)
                if fx < fbest
                    xbest = copy(x)
                    fbest = fx
                    D = Int[]
                    otherDirections = [1:(3^n-1)]
                    improved = true
                end
            end
        end
    end
    (xbest, fx)
end

function CGRASP(n, l, u, f, MaxIters, MaxNumIterNoImprov, runs, MaxDirToTry, alpha)
    # verifies that dimensions agree
    @assert (length(l) == length(u)) && (length(l) == n)

    fbest = Inf
    xbest = []
    for j in 1:runs
        h = 1
        x = UnifRand(l, u)
        noImprov = 0
        for iter in 1:MaxIters
            ConstructGreedyRandomized(x, f, n, h, l, u, alpha)
            x, fx = LocalSearch(x, f, n, h, l, u, MaxDirToTry)
            if fx < fbest
                print("***** changed xbest, fx = $fx, fbest = $fbest \n")
                xbest = copy(x)
                fbest = fx
                noImprov = 0
            else
                noImprov += 1
            end
            if noImprov > MaxNumIterNoImprov
                h = h / 2
                noImprov = 0
            end
            print("$j,$iter xb $xbest fx $fx fb $fbest $noImprov\n")
        end
    end
    
    xbest
end


### Some test functions

function easom_l(n::Int)
    zeros(Float64, n) - 20.0
end

function easom_u(n::Int)
    zeros(Float64, n) + 20.0
end

function easom(x)
    fx = -1.0*cos(x[1])*cos(x[2])*exp(-1.0*(x[1] - pi)^2 - (x[2] - pi)^2)
    return fx
end

function test_easom()
    srand(127137177)
    #CGRASP(2, easom_l(2), easom_u(2), easom, 50000, 30, 100, 8, 0.4)
    CGRASP(2, easom_l(2), easom_u(2), easom, 500, 30, 100, 8, 0.4)
end
