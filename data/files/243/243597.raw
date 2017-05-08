# Population initialization.

import StatsBase.sample

export treefull, treegrow

# Builds a random tree using the "full" method
function treefull(funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    tree::Tree

    numvars = length(vars)
    varprob = numvars / (numvars + 1) # 1 for the ephemeral constant

    if maxdepth > 0
        func = sample(funcs)
        subtrees = [treefull(funcs, consts, vars, maxdepth-1) for _=1:arity(func)]
        tree = func(subtress...)
    else
        if rand() < varprob
            tree = sample(vars)
        else
            tree = sample(consts)
        end
    end
    tree
end

# Builds a random tree using the "grow" method
function treegrow(funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    tree::Tree

    numfuncs = length(funcs)
    numterms = length(vars) + 1 # 1 for the ephemeral constant
    funcprob = numfuncs / (numfuncs + numterms)

    numvars = length(vars)
    varprob = numvars / (numvars + 1)

    if maxdepth > 0 && rand() < funcprob
        func = sample(funcs)
        subtrees = [treegrow(funcs, consts, vars, maxdepth-1) for _=1:arity(func)]
        tree = func(subtrees...)
    else
        if rand() < varprob
            tree = sample(vars)
        else
            tree = sample(consts)
        end
    end
    tree
end
