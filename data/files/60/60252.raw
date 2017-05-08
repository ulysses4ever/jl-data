# finds the largest prime factor of 600851475143
function isPrime(x)
        for i=2:sqrt(x)
                if(x%i==0)
                        return false
                end
        end
    return true
end

function largestFactor(x)
        if(isPrime(x))
                return x
        end
        for i=2:sqrt(x)
                if(x%i==0)
                        if(isPrime(i))
                                return max(i,largestFactor(x/i))
                        end
                end
        end
        return "not found!"
end

println(largestFactor(600851475143))
