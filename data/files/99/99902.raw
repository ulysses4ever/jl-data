function fact(num::Number)
    res = Dict{Int64, Int64}()
    # assume num > 2
    temp_res = firstfactor(num, 2)
    while temp_res[2] != 1
        res[temp_res[1]] = get!(res, temp_res[1], 0) + 1
        temp_res = firstfactor(temp_res[2], temp_res[1])
    end
    res[temp_res[1]] = get!(res, temp_res[1], 0) + 1
    res
end

function firstfactor(num, start)
    limit = ceil(sqrt(num))
    for i = start:limit
        if num % i == 0
            return (i, num/i)
        end
    end
    return (num, 1)
end

# more tail-recursive like variant
function fact_pls(num)
    limit = ceil(sqrt(num))
    fact_rec(num, 2, limit, Dict{Int64, Int64}())
end

function fact_rec(num, start, limit, list)
    for i = start:limit
        if num % i == 0
            list[i] = get!(list, i, 0) + 1
            return fact_rec(num/i, i, ceil(sqrt((num/i))), list)
        end
    end
    list[num] = get!(list, num, 0) + 1
    return list
end

