module Problem12

## What is the value of the first triangle number to have over five hundred divisors?

function properdivisors{T<:Integer}(n::T)
    ## https://rosettacode.org/wiki/Proper_divisors#Julia

    0 < n || throw(ArgumentError("number to be factored must be ≥ 0, got $n"))
    1 < n || return T[]
    !isprime(n) || return T[one(T), n]
    f = factor(n)
    d = T[one(T)]
    for (k, v) in f
        c = T[k^i for i in 0:v]
        d = d*c'
        d = reshape(d, length(d))
    end
    sort!(d)
    return d[1:end-1]
end

n = 1
t = 1

while length(properdivisors(t)) <= 500
  n += 1
  t += n
end

problem12 = t

end