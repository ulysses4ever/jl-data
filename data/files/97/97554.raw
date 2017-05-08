include("hello.jl")

function is_divisble(n, i)
    return n % i == 0
end

function is_prime(n::Int64)
    if n <= 3
         return true
    end

    if is_divisble(n, 2)
         return false
    end

    i = 3
    while i <= sqrt(n)
        if is_divisble(n, i)
            return false
        end
        i += 2
    end

    return true
end

function is_prime(n::Float64)
end
println(is_prime(101))


a = 1
b = 2
c = 3
f = (x) -> a * x^2 + b * x + c
println(f(10))


square_stuff = function(x)
    return x^2
end
println(square_stuff(3))


derivative = function(f)
    return function(x)
        h  = 0.000001
        f0 = f(x)
        f1 = f(x + h)
        return (f1 - f0)/h
    end
end

println(derivative((x) -> x^2 + x)(100))
