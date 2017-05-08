# Population initialization.

export randfull, randgrow

function randfull(funcs::FuncSet, consts::ConstSet, vars::VarSet, maxdepth::Int)
    root::Node

    numvars = length(vars)
    varprob = numvars / (numvars + 1) # 1 for the "ephemeral constant"

    if maxdepth > 0
        func = sample(funcs)
        argnames = funcargs(func)
        subtrees = [randfull(funcs, consts, vars, maxdepth - 1) for _=argnames]
        root = func(subtrees...)
    else
        if rand() < varprob
            root = sample(vars)
        else
            root = sample(consts)
        end
    end
    return root
end

function randgrow(funcs::FuncSet, consts::ConstSet, vars::VarSet, maxdepth::Int)
    root::Node

    numfuncs = length(funcs)
    numterms = length(vars) + 1 # 1 for the "ephemeral constant"
    funcprob = numfuncs / (numfuncs + numterms)

    numvars = length(vars)
    varprob = numvars / (numvars + 1) # 1 for the "ephemeral constant"

    if maxdepth > 0 && rand() < funcprob
        func = sample(funcs)
        argnames = funcargs(func)
        subtrees = [randgrow(funcs, consts, vars, maxdepth - 1) for _=argnames]
        root = func(subtrees...)
    else
        if rand() < varprob
            root = sample(vars)
        else
            root = sample(consts)
        end
    end
    return root
end
