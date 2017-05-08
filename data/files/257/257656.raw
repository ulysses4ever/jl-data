module CutPools

using JuMP

export Separator, Oracle, CuttingPlane, CutPool,
       separate, separator_callback, addfamily!

abstract Separator
abstract Oracle <: Separator

type CuttingPlane
    ineq::LinearConstraint
    added::Bool
    CuttingPlane(ineq::LinearConstraint) = new(ineq,false)
end

type CutFamily
    cuts::Vector{CuttingPlane}
    name::String
end

type CutPool <: Separator
    pool::Vector{CuttingPlane}
    clear_used::Bool
    groups::Vector{CutFamily}
end
CutPool() = CutPool(CuttingPlane[], true, CutFamily[])

function addfamily!(pool::CutPool, cp::Vector{LinearConstraint}, name::String)
    cuts = [CuttingPlane(c) for c in cp]
    append!(pool.pool, cuts)
    push!(pool.groups, CutFamily(cuts,name))
end

Base.push!(x::CutPool,y) = push!(x.pool,CuttingPlane(y))
Base.append!(x::CutPool,y) = append!(x.pool,[CuttingPlane(c) for c in y])

const ε = 1e-4
const ratio_pool_reshuffle = 0.1

function separate(cutpool::CutPool)
    separated = CuttingPlane[]
    num_sep = 0
    for cut in cutpool.pool
        if cut.added
            num_sep += 1
            continue
        end
        val = getValue(cut.ineq.terms)
        lb, ub = cut.ineq.lb, cut.ineq.ub
        if (lb - val) / abs(min(lb,val,ε)) > ε ||
           (val - ub) / abs(min(ub,val,ε)) > ε
            push!(separated, cut)
            cut.added = true
            num_sep += 1
        end
    end

    if cutpool.clear_used &&
    num_sep > ratio_pool_reshuffle*length(cutpool.pool)
        filter!(cutpool.pool) do cut
            !cut.added
        end
    end

    return separated
end

function _separator_callback(cb, cutpool::CutPool, maxnum::Int)
    tic()
    cuts_added = 0
    cuts = separate(cutpool)
    for cut in cuts
        cuts_added += 1
        addUserCut(cb, cut.ineq)
        cuts_added ≥ maxnum && break
    end
    el = toq()
    # println("Adding $(min(length(cuts),maxnum)) cuts in $el seconds")
end

separator_callback(cutpool::CutPool; maxnum=100) =
    (cb -> _separator_callback(cb, cutpool, maxnum))

end
