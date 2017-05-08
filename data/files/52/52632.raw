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

# Throwaway timings (compiling)
@time time_weighted_median(data, weights, num_tests)

# Performance tests
num_points = int(1e6)
num_sets = 50
data_range = 10000
wt_range = 100

println(num_sets, " data sets (", num_points, " data points each)")

# weights: [0, wt_range)
wt = @array(:($wt_range * rand($num_points)), num_sets)

# data:
#   [-data_range/2, data_range/2),
#   [0, data_range),
#   [-data_range, 0)
data_expr = (:($data_range * (rand($num_points) - 0.5)),
             :($data_range * rand($num_points)),
             :(-$data_range * rand($num_points)))

timer(@array(data_expr[1], num_sets), wt)
timer(@array(data_expr[2], num_sets), wt)
timer(@array(data_expr[3], num_sets), wt)
