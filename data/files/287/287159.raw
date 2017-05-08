#   Project Euler
#   Problem:    3
#   Author:     Ben Hobbs
#   Date:       27/5/2015
#   Desc:       The prime factors of 13195 are 5, 7, 13 and 29.
#
#               What is the largest prime factor of the number 600851475143?

function factors(low,high,num)
    println("Hello")

    a = Int64[]
    for factor in low:high
        if mod(num,factor) == 0
            push!(a,factor)
        end
    end

    println("Goodbye")
    return a
end

function isPrime(num)
    for i in 2:sqrt(num)
        if mod(num,i) == 0
            return false
        end
    end

    return true
end
