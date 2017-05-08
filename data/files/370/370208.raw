#! /usr/bin/julia

# Rosetta Code, Order two numerical lists

function isallreal{T<:AbstractArray}(a::T)
    all(map(x->isa(x, Real), a))
end

function islexfirst{T<:AbstractArray,U<:AbstractArray}(a::T, b::U)
    isallreal(a) && isallreal(b) || throw(DomainError())
    for i in 1:min(length(a), length(b))
        x = a[i]
        y = b[i]
        x != y || continue
        return x < y
    end
    return length(a) < length(b)
end

tests = {[1, 2, 3],
         primes(10),
         0:2:6,
         [-Inf, 0.0, Inf],
         [π, e, φ, catalan],
         [2015, 5],
         [-sqrt(50.0), 50.0^2],
         }

println("Testing islexfirst:")
for (a, b) in combinations(tests, 2)
    tres = islexfirst(a, b) ? " is " : " is not "
    tres *= "lexically prior to\n    "
    println("\n    ", a, tres, b)
end

        
        
