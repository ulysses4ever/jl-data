module CutSeparator

using JuMP

export Separator, Oracle, CutPool,
       separate, separator_callback

abstract Separator
abstract Oracle <: Separator

type CutPool <: Separator
    pool::Vector{LinearConstraint}
    added::Vector{Bool}
    clear_used::Bool
end
CutPool() = CutPool(LinearConstraint[], Bool[], true)

function Base.push!(x::CutPool,y)
    push!(x.pool,y)
    push!(x.added,false)
end

function Base.append!(x::CutPool,y)
    append!(x.pool,y)
    append!(x.added,fill(false,length(y)))
end

const ε = 1e-4
const ratio_pool_reshuffle = 0.1

function separate(cutpool::CutPool)
    separated = LinearConstraint[]
    for it in 1:length(cutpool.pool)
        cutpool.added[it] && continue
        cut = cutpool.pool[it]
        val = getValue(cut.terms)
        lb, ub = cut.lb, cut.ub
        if (lb - val) / abs(min(lb,val,ε)) > ε ||
           (val - ub) / abs(min(ub,val,ε)) > ε
            push!(separated, cut)
            cutpool.added[it] = true
        end
    end

    if cutpool.clear_used &&
    length(separated) > ratio_pool_reshuffle*length(cutpool.pool)
        indices = filter(1:length(cutpool.pool)) do it
            !cutpool.added[it]
        end
        cutpool.pool  = cutpool.pool[indices]
        cutpool.added = fill(false, length(indices))
    end

    return separated
end

function __separator_callback(cb, cutpool::CutPool, maxnum::Int)
    tic()
    cuts_added = 0
    cuts = separate(cutpool)
    for cut in cuts
        cuts_added += 1
        addUserCut(cb, cut)
        cuts_added ≥ maxnum && break
    end
    el = toq()
    println("Adding $(min(length(cuts),maxnum)) cuts in $el seconds")
end

separator_callback(cutpool::CutPool; maxnum=100) =
    (cb -> __separator_callback(cb, cutpool, maxnum))

end
