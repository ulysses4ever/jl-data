
function isPrime(n::Int64)
    ans = true
    for i = 2:sqrt(n)
        if n % i == 0
            ans = false
        end
    end
    return ans
end

function isPrime(n::UnitRange{Int64})
    answ = falses(length(n))
    cnt = 0
    for i = n
        cnt+=1
        answ[cnt] = isPrime(i)
    end
    return answ
end

function maxPrimeDiv(n::Int64)
    maxDiv = 1
    for i = 1:sqrt(n)
        if isPrime(i) && n % i == 0
            maxDiv = i
        end
    end
    maxDiv
end

print(isPrime(2:13))
