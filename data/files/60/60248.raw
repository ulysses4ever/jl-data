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
        return "not found, prkl!"
end
