function fact(num::Number)
    res = Dict{Int64, Int64}()
    if num == 0
        return res
    else
        res[2] = 1
        res
    end

    limit = floor(num/2)
end

function firstfactor(num, start)
    limit = floor(num/2)
    for i = start:limit
        if num % i == 0
            return (i, num/i)
        end
    end
    return (num, 1)
end
