# Problem 1
#
# If we list all the natural numbers below 10 that are multiples of 3 or
# 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
# Find the sum of all the multiples of 3 or 5 below 1000.

function multiples(num)
    mult_arr = Any[]
    for i = 1:num-1
        if (i % 3 == 0) || (i % 5 == 0)
            push!(mult_arr, i)
        end
    end
    return mult_arr
end

function sum_multiples(mult_arr)
    sum = 0
    for i = 1:length(mult_arr)
        sum += pop!(mult_arr)
    end
    return sum
end

mults = multiples(int(ARGS[1]))
println(mults)
result = sum_multiples(mults)
println(result)
