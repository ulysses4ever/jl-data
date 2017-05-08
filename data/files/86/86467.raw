module Grisu

include("float.jl")
include("fastdtoa.jl")
include("fastfixedtoa.jl")
include("bignum-dtoa.jl")
#TODO
 #performance benchmarks
 #remove Float dependency?
 #

const SHORTEST = 1
const SHORTEST_SINGLE = 2
const FIXED = 3
const PRECISION = 4

function grisu(
            v::Float64,
            mode,
            requested_digits::Int,
            buffer::Vector{Char},
            buffer_length::Int)
    if sign(x) < 0
        sign = true
        v = -v
    else
        sign = false
    end
    if mode == PRECISION && requested_digits == 0
        len = 0
        return buffer, sign, len, point
    end
    if v == 0.0
        buffer[1] = '0'
        len = point = 1
    end
    if mode == SHORTEST
        status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST, 0,buffer)
    elseif mode == SHORTEST_SINGLE
        status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_SHORTEST_SINGLE, 0,buffer)
    elseif mode == FIXED
        status,len,point,buffer = Grisu.fastfixeddtoa(v,requested_digits,buffer)
    elseif mode == PRECISION
        status,len,point,buffer = Grisu.fastdtoa(v, Grisu.FAST_DTOA_PRECISION, requested_digits,buffer)
    end
    status && return status,len,point,buffer
    return Grisu.bignumdtoa(v,mode,requested_digits,buffer)
end

end # module
