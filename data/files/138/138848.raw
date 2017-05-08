## sgearray.jl.  Iterators for use in conjunction with Sun Grid Engine
## (c) 2014, 2016 David A. van Leeuwen
##

issgearray() = haskey(ENV, "SGE_TASK_ID") && haskey(ENV, "SGE_TASK_LAST") && ENV["SGE_TASK_ID"] != "undefined"

function Base.start(sge::SGEArray)
    sge.state = start(sge.iterator)
    state = 0
    while true
        if done(sge.iterator, sge.state)
            state = -1
            break
        end
        sge.next, sge.state = next(sge.iterator, sge.state)
        if state % sge.step == sge.first
            break
        end
        state += 1
    end
    return state
end
Base.done(sge::SGEArray, state::Int) = state < 0
function Base.next(sge::SGEArray, state::Int)
    item = sge.next
    while true
        if done(sge.iterator, sge.state)
            state = -1
            break
        end
        sge.next, sge.state = next(sge.iterator, sge.state)
        state += 1
        if state % sge.step == sge.first
            break
        end
    end
    return item, state
end
