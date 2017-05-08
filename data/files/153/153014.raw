# created by mooxmirror (25.12.2015)
# implementing the zeckendorf-theorem

using Base.Test

"Implements the Zeckendorf-theorem and outputs a Zeckendorf sequence {cᵪ | c ∈ {0, 1}}"
function zeckendorf{T <: Integer}(n::T)
    @assert n >= 0 "n is required to be larger or equal than zero"

    x, z = 2, 2
    fib_cache = [1, 1]

    # find fib(z-1) <= n <= fib(z)
    while z <= n
        x += 1
        z = fib_cache[x-1] + fib_cache[x-2]
        push!(fib_cache, z)
    end

    c = falses(x-1)

    for i in (x-1):-1:1
        if fib_cache[i] <= n
            n -= fib_cache[i]
            c[i] = true
        end
    end

    return c
end

"Generates a binary string from a boolean array in reverse order"
binary_string{T <: AbstractArray{Bool}}(A::T) = join(map(Int, reverse(A)))

"Tests the zeckendorf function"
function test_zeckendorf()
    @test(binary_string(zeckendorf(0)) == "0")
    @test(binary_string(zeckendorf(1)) == "1")
    @test(binary_string(zeckendorf(2)) == "100")
    @test(binary_string(zeckendorf(4)) == "1010")
    @test(binary_string(zeckendorf(6)) == "10010")

    println("All tests passed")
end
