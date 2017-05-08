#!/usr/bin/julia
#=
The sum of the squares of the first ten natural numbers is,
1^2 + 2^2 + ... + 10^2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)^2 = 552 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
=#

function diff(n)
    s = 0 
    for i in range(1,n)
        s += sum(i * range(1,n)) - i^2
    end
    return s
end

println(diff(100))
