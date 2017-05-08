#! /usr/bin/julia

# Rosetta Code, Amicable pairs

function pcontrib{T<:Integer}(p::T, a::T)
    n = one(T)
    pcon = one(T)
    for i in 1:a
        n *= p
        pcon += n
    end
    return pcon
end

function divisorsum{T<:Integer}(n::T)
    dsum = one(T)
    for (p, a) in factor(n)
        dsum *= pcontrib(p, a)
    end
    dsum -= n
end

function aliquotclassifier{T<:Integer}(n::T)
    a = T[n]
    b = divisorsum(a[end])
    len = 1
    while len < 17 && !(b in a) && 0 < b && b < 2^47+1
        push!(a, b)
        b = divisorsum(a[end])
        len += 1
    end
    if b in a
        1 < len || return ("Perfect", a)
        if b == a[1]
            2 < len || return ("Amicable", a)
            return ("Sociable", a)
        elseif b == a[end]
            return ("Aspiring", a)
        else
            return ("Cyclic", push!(a, b))
        end
    end
    push!(a, b)
    b != 0 || return ("Terminating", a)
    return ("Non-terminating", a)
end

println("Classification Tests:")
tests = [1:12, 28, 496, 220, 1184, 12496, 1264460, 790, 909, 562, 1064, 1488]
for i in tests
    (class, a) = aliquotclassifier(i)
    println(@sprintf("%8d => ", i), @sprintf("%16s, ", class), a)
end

    
