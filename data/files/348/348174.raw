#   Project Euler
#   Problem:    3
#   Author:     Ben Hobbs
#   Date:       28/5/2015
#   Desc:       The prime factors of 13195 are 5, 7, 13 and 29.
#
#               What is the largest prime factor of the number 600851475143?

function isPrime(num)
    for i in 2:sqrt(num)
        if mod(num,i) == 0
            return false
        end
    end
    return true
end

number = 600851475143
divisor = 2
factor = 0

while divisor < ceil(number/2)
    if rem(number,divisor) == 0
        factor = number/divisor
        if isPrime(factor)
            break
        end
    end
    divisor += 1
end

println(factor)