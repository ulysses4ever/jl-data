module Grisu

const SHORTEST = 1
const FIXED = 2
const PRECISION = 3

const BUFFER = Array(Uint8,309+17)

include("float.jl")
include("fastdtoa.jl")
include("fastfixedtoa.jl")
include("bignum-dtoa.jl")
#TODO
 #add Float16 support/tests
 #add grisu folder, rework grisu.jl in base
 #remove double-conversion from makefiles
 #what to do with tests? everything but mega files?

function grisu(v::FloatingPoint,mode,requested_digits,buffer=BUFFER)
    if signbit(v)
        neg = true
        v = -v
    else
        neg = false
    end
    if mode == PRECISION && requested_digits == 0
        buffer[1] = 0x00
        len = 0
        return 0, 0, neg, buffer
    end
    if v == 0.0
        buffer[1] = 0x30
        buffer[2] = 0x00
        len = point = 1
        return len, point, neg, buffer
    end
    if mode == SHORTEST
        status,len,point,buffer = fastdtoa(v,SHORTEST,0,buffer)
    elseif mode == FIXED
        status,len,point,buffer = fastfixedtoa(v,0,requested_digits,buffer)
    elseif mode == PRECISION
        status,len,point,buffer = fastdtoa(v,PRECISION,requested_digits,buffer)
    end
    status && return len, point, neg, buffer
    status, len, point, buffer = bignumdtoa(v,mode,requested_digits,buffer)
    return len, point, neg, buffer
end

end # module
