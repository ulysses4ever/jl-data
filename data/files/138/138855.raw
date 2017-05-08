## sgetypes.jl.  Iterators for use in conjunction with Sun Grid Engine
## (c) 2014 David A. van Leeuwen
##

## The inner constructor returns the array itself if not running in 
## an SGE environment.  I don't know if that is the Julian way...
type SGEArray
    start::Int
    step::Int
    array::Array
    function SGEArray(a::Array)
        if !issgearray()
            a
        else
            start = int(ENV["SGE_TASK_ID"])
            step = int(ENV["SGE_TASK_LAST"])
            l = length(a)
            if step < start || start > length(a)
                error("Incorrect array parameters")
            end
            new(start, step, a)
        end
    end
end
