#!/usr/bin/julia
## The prime factors of 13195 are 5, 7, 13 and 29.
## What is the largest prime factor of the number 600851475143 ?

# n = 13195
n = 600851475143
d = 1
factors = Int64[]
while true 
    d += 1
    if (n % d == 0)
        push!(factors,d)
        n = n / d
        d = 1 
    end
    if (n == d)
        break
    end 
end 

println(maximum(factors))
