#! /usr/bin/julia

# Rosetta Code, Abundant, deficient and perfect number classifications

# A natural number, n, can be written as a product of powers of it's
# prime factors, n = Prod(p_i^(a_i)).  The sum of all of n's divisors,
# including n itself, is dsum = Prod((p_i^(a_i+1) - 1)/(p_i - 1)).

const L = 2*10^4

function pcontrib(p::Int64, a::Int64)
    # (p^(a+1) - 1)/(p_i - 1) = p^a + p^(a-1) + ... + p + 1, Perhaps
    # this could be made more efficient by caching results to avoid
    # repeated calculations.
    n = one(p)
    pcon = one(p)
    for i in 1:a
        n *= p
        pcon += n
    end
    return pcon
end

function divisorsum(n::Int64)
    #the "proper divisor sum", or aliquot sum of n's divisors,
    #excluding n itself
    dsum = one(n)
    for (p, a) in factor(n)
        dsum *= pcontrib(p, a)
    end
    dsum -= n
end

# Work with a three element array, rather than three separate
# variables, and take advantage of the fact that the sign of dsum - n
# depends upon its class to increment this array of classifications.

iclasslabel = ["Deficient", "Perfect", "Abundant"]
iclass = zeros(Int64, 3)
iclass[1] = one(Int64) #by convention 1 is deficient

for n in 2:L
    if isprime(n)
        iclass[1] += 1
    else
        iclass[sign(divisorsum(n)-n)+2] += 1
    end
end


println("Classification of integers from 1 to ", L)
for i in 1:3
    println("   ", iclasslabel[i], ", ", iclass[i])
end


    
