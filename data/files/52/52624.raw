macro array(ex, num_sets)
    data = (Expr)[]
    for i = 1:eval(num_sets)
        push!(data, eval(ex))
    end
    map(eval, data)
end

function timer(data, weights)
    num_tests = length(data)
    @time time_weighted_median(data, weights, num_tests)
end

function time_weighted_median(data, weights, num_tests)
    for i = 1:num_tests
        weighted_median(data[i], weights[i])
    end
end
