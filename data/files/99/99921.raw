function multipleSum(min::Int, max::Int, factors...)
    sum = 0
    count = 0
    for i in min:max
        for f in factors
            count += 1
            if i % f == 0
                sum += i
                break # avoids summing i multiple times
            end # end if
        end # end for f
    end # end for i
    return sum
end # end func

using Base.Test
@test multipleSum(1, 5, 1) == 15
@test multipleSum(1, 9, 3, 5) == 23
