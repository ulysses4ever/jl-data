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

const NEG    = Array(Bool)
const DIGITS = Array(Uint8,309+17)
const BUFLEN = int32(length(DIGITS)+1)
const LEN    = Array(Int32)
const POINT  = Array(Int32)

function grisu(
            v::Float64,
            mode,
            requested_digits::Int,
            buffer::Vector{Uint8}=DIGITS,
            buffer_length=BUFLEN)
    if sign(v) < 0
        s = true
        v = -v
    else
        s = false
    end
    if mode == PRECISION && requested_digits == 0
        len = 1
        return len, point, buffer, s
    end
    if v == 0.0
        buffer[1] = 0x30
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
    status && return len, point, buffer, s
    len, point, buffer = Grisu.bignumdtoa(v,mode,requested_digits,buffer)
    return len, point, buffer, s
end

end # module
