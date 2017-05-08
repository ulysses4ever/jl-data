
function isPrime(n::Int64)
    ans = true
    for i = 2:sqrt(n)
        if n % i == 0
            ans = false
        end
    end
    return ans
end
     

function primeFactorize(n::Int64)

    testN = convert(Int64, sqrt(n))
    isPrime = zeros(Int64, testN)
    
    for i = 1:Sqrt(n)
        
