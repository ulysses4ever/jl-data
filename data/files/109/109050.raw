# In main.jl

function is_divisible(n, i)
    return n % i == 0
end

function is_prime6(n)
    if is_divisible(n, 2)
        return false
    end

    # Fails if n is small (say, 5)
    i = 3

    while i <= sqrt(n)
        println(i)
        if is_divisible(n, i)
            return false
        end

        i += 2
    end

end


println("Hello, World!")
println(is_prime6(100))

