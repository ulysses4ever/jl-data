#!/usr/bin/env julia

# If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
# Find the sum of all the multiples of 3 or 5 below 1000.

function find_multiples(max)
    sum = 0
    for p=1:max-1
        if p % 5 == 0 || p % 3 == 0
            sum += p
        end
    end
    return sum
end

max = 1000

println(find_multiples(max))