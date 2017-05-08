# Evolutionary operators.

import StatsBase.sample

export mutsubtree, mutpoint, crosssubtree

function mutsubtree()
end

# TODO Handle different arities in funcs
function mutpoint(r::Func, funcs::FuncSet, terms::TermSet, mutprob::Float64)
    if rand() < mutprob
        newfunc = sample(funcs)
    else
        newfunc = typeof(r)
    end
    newargs = [mutpoint(c, funcs, terms, mutprob) for c=r.args]
    newfunc(newargs...)
end

function mutpoint(r::Term, funcs::FuncSet, terms::TermSet, mutprob::Float64)
    if rand() < mutprob
        newterm = sample(terms)
    else
        newterm = r
    end
    newterm
end

function crosssubtree(r1::Func, r2::Func)
end
