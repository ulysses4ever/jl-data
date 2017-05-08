function eratosthenes(upperval::Integer)
    i = 1
    primes = Array(Int64, upperval)
    numberlist = trues(upperval)
    numberlist[1] = false
    for index in 2:bound
        if numberlist[index] && isprime(index)
            primes[i] = index
            i += 1
            multiples = index:index:(index * fld(upperval, index))
            for multiple in multiples
                numberlist[multiple] = false
            end
        end
    end
    return primes[1:(i - 1)]
end
