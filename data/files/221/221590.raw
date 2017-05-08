#!/usr/bin/env julia

# The prime factors of 13195 are 5, 7, 13 and 29.
# What is the largest prime factor of the number 600851475143 ?


function find_prime_factor(num)
    factor = 0
    d = 2
    while num > 1
        while num % d == 0
            factor = d
            num = num / d
        end
        d = d + 1
    end
    return factor
end

println(find_prime_factor(600851475143))
