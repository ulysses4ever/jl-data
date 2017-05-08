# Evolutionary operators.

export mutsubtree, mutpoint, crosssubtree

function mutsubtree(t::Func, funcs::FuncTypes, consts::Consts, vars::Vars, funcprob::Float64)
    oldst = randsubtree(t, funcprob)
    newst = treegrow(funcs, consts, vars, maxdepth(oldst))
    replacesubtree(t, oldst, newst)
end
function mutsubtree(t::Term, funcs::FuncTypes, consts::Consts, vars::Vars, funcprob::Float64)
    treegrow(funcs, consts, vars, 2)
end

function mutpoint(t::Func, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    matchfuncs = filter(funcs) do f
        arity(f) == arity(typeof(t))
    end |> collect
    if rand() < mutprob
        func = matchfuncs[rand(1:end)]
    else
        func = typeof(t)
    end
    subtrees = [mutpoint(st, funcs, terms, mutprob) for st=t.args]
    func(subtrees...)
end
function mutpoint(t::Term, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    if rand() < mutprob
        term = terms[rand(1:end)]
    else
        term = t
    end
    term
end

function crosssubtree(tleft::Func, tright::Func, funcprob::Float64)
    leftst = randsubtree(tleft, funcprob)
    rightst = randsubtree(tright, funcprob)
    (replacesubtree(tleft, leftst, rightst), replacesubtree(tright, rightst, leftst))
end
