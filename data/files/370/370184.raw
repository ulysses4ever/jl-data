#! /usr/bin/julia

# Rosetta Code, Find largest left truncatable prime in a given base

function addmsdigit{T<:Integer}(p::T, b::T, s::T)
    a = T[]
    q = p
    for i in 1:(b-1)
        q += s
        isprime(q) || continue
        push!(a, q)
    end
    return a
end

function lefttruncprime{T<:Integer}(pbase::T)
    b = convert(BigInt, pbase)
    a = BigInt[]
    append!(a, primes(b-1))
    mlt = zero(BigInt)
    s = one(BigInt)
    while !isempty(a)
        mlt = maximum(a)
        s *= b
        for i in 1:length(a)
            p = shift!(a)
            append!(a, addmsdigit(p, b, s))
        end
    end
    return mlt
end

lo, hi = 3, 17
print("The largest left truncatable primes for bases")
println(@sprintf " %d to %d." lo hi)
for i in 1:5
    print("  Base = ", i, "\n  ")
    @ time mlt = lefttruncprime(12)
    println(@sprintf "   %3d %d\n" i mlt)
end

