#!/usr/bin/env julia

# Implementing currying with a macro.

# At time of writing (2014 Feb 22) anonymous functions are funny.
# So this is not written with anonymous functions

import Base.apply

type CFunction
    fxn::Function
    args::Array
end

macro curry(funct, args...)
    quote
    function anon_curried(x...)
        $funct($(args...), x...)
    end
    end
end

function cfunct(funct::Function, args...)
    CFunction(funct, [(args...)])
end

## macro cfunct(funct::CFunction, args...)
##     quote
##     $(funct.args) = [$(funct.args), $(args...)]
##     end
## end

function apply(cf::CFunction, args...)
    apply(cf.fxn, args)
end
   

