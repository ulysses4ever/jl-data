#! /usr/bin/julia

# Rosetta Code, MD4

macro f(x, y, z)
    return :(x&y | ~x&z)
end

macro g(x, y, z)
    return :(x&y | x&z | y &z)
end

macro h(x, y, z)
    return x$y$z
end

function md4message(s::String)
    mb = convert(Array{Uint8,1}, s)
    b = length(mb)
    push!(mb, 0x80)
    mbsize = (b+1)%64
    if mbsize < 56
        append!(mb, zeros(Uint8, 56-mbsize))
    elseif mbsize > 56
        append!(mb, zeros(Uint8, 120-mbsize))
    end
    mb = reinterpret(Uint32, mb) # convert from bytes to "words"
    mb = map(hton, mb) # get the endianess correct
    b = unsigned(b)<<3 # message length in bits
    if b <= typemax(Uint32)
        push!(mb, zero(Uint32))
        push!(mb, uint32(b))
    else
        bmask = convert(typeof(b), typemax(Uint32))
        push!(mb, convert(Uint32, b>>32 & bmask))
        push!(mb, convert(Uint32, b & bmask))
    end
    return mb
end

function md4(s::String)
    hnew = Uint32[0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210]
    m = md4message(s)
    for i in 1:16:length(m)
        hold = copy(hnew)
        for 
        
end
    
