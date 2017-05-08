## sgetypes.jl.  Iterators for use in conjunction with Sun Grid Engine
## (c) 2014 David A. van Leeuwen
##

## The inner constructor returns the iterator itself if not running in
## an SGE environment.  I don't know if that is the Julian way...
type SGEArray{T}
    first::Int
    step::Int
    iterator::T
    state::Any
    next::Any
    function SGEArray(it::T)
        if !issgearray()
            new(0, 1, it)
        else
            first = parse(Int, ENV["SGE_TASK_ID"]) - 1
            step = parse(Int, ENV["SGE_TASK_LAST"])
            if step < first
                error("Incorrect SGE array parameters")
            end
            new(first, step, it)
        end
    end
end
## There is something about inner constructors, they need this:
SGEArray{T}(it::T) = SGEArray{T}(it)
