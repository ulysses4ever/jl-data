# really bad divisors counting
function divisor_count(n)
    div_num = 0
    sqrt_n = sqrt(n)
    for i in 1:floor(sqrt_n)
        if mod(n, i) == 0
            div_num += 1
        end
    end
    sqrt_n^2 == n ? 2div_num - 1 : 2div_num # in case n is a perfect square
end

function first_triangular_500_divisors()
    n = 0
    i = 1
    while true
        n += i
        i += 1
        if divisor_count(n) >= 500
            return n
        end
    end
end

# this is two orders of magnitude faster than the other
function first_triangular_500_divisors_primes()
    n = 0
    i = 1
    while true
        n += i
        i += 1
        tau = [v+1 for k, v in values(factor(n))]
        if prod(tau) >= 500
            return n
        end
    end
end


@time first_triangular_500_divisors()
@time first_triangular_500_divisors_primes()
