# Evolutionary operators.

import StatsBase.sample

export mutsubtree, mutpoint, crosssubtree

function mutsubtree()
end

function mutpoint(t::Func, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    matchfuncs = filter(funcs) do f
        arity(f) == arity(typeof(t))
    end
    if rand() < mutprob
        func = sample(matchfuncs)
    else
        func = typeof(f)
    end
    subtrees = [mutpoint(st, funcs, terms, mutprob) for st=t.args]
    func(subtrees...)
end
function mutpoint(t::Term, funcs::FuncTypes, terms::Terms, mutprob::Float64)
    if rand() < mutprob
        term = sample(terms)
    else
        term = t
    end
    term
end

function crosssubtree(r1::Func, r2::Func)
end
