## 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
## What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

function divall(n, max = 20)
    for i in range(1, max)
        if (n % i != 0)
            return false
        end 
    end
    return true 
end

n = 20
while true
    if divall(n, 20)
        break
    end
    n += 1
end 
println(n)
