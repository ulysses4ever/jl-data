# Population initialization.

export treefull, treegrow

# ------------------------------------------------------------------------------
# Full method
# Builds a random tree using the "full" method.
# ------------------------------------------------------------------------------

function treefull(funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    tree::Tree

    numvars = length(vars)
    varprob = numvars / (numvars + 1) # 1 for the ephemeral constant

    if maxdepth > 0
        func = funcs[rand(1:end)]
        subtrees = [treefull(funcs, consts, vars, maxdepth-1) for _=1:arity(func)]
        tree = func(subtrees...)
    else
        if rand() < varprob
            tree = vars[rand(1:end)]
        else
            tree = consts[rand(1:end)]
        end
    end
    tree
end
function treefull(funcs::FuncTypes, consts::Consts, maxdepth::Int64)
    treefull(funcs, consts, vars(), maxdepth)
end

# ------------------------------------------------------------------------------
# Grow method
# Builds a random tree using the "grow" method.
# ------------------------------------------------------------------------------

function treegrow(funcs::FuncTypes, consts::Consts, vars::Vars, maxdepth::Int64)
    tree::Tree

    numfuncs = length(funcs)
    numterms = length(vars) + 1 # 1 for the ephemeral constant
    funcprob = numfuncs / (numfuncs + numterms)

    numvars = length(vars)
    varprob = numvars / (numvars + 1)

    if maxdepth > 0 && rand() < funcprob
        func = funcs[rand(1:end)]
        subtrees = [treegrow(funcs, consts, vars, maxdepth-1) for _=1:arity(func)]
        tree = func(subtrees...)
    else
        if rand() < varprob
            tree = vars[rand(1:end)]
        else
            tree = consts[rand(1:end)]
        end
    end
    tree
end
function treegrow(funcs::FuncTypes, consts::Consts, maxdepth::Int64)
    treegrow(funcs, consts, vars(), maxdepth)
end
