module WeightedStats

export weighted_mean, weighted_median, NumericArray

NumericArray = Union(Array{Int,1}, Array{Float32,1}, Array{Float64,1})

function weighted_mean(data::NumericArray, weights::NumericArray)
    data = float(data)
    weights = float(weights)
    (data' * (weights ./ sum(weights)))[1]
end

function weighted_median(data::NumericArray, weights::NumericArray)
    sorted = sortrows([data weights])
    midpoint = 0.5 * sum(sorted[:,2])
    if any(weights .> midpoint)
        median(data[weights .== maximum(weights)])
    else
        cumulative_weight = cumsum(sorted[:,2])
        below_midpoint_index = find(cumulative_weight .<= midpoint)[end]
        if cumulative_weight[below_midpoint_index] == midpoint
             mean(sorted[below_midpoint_index:below_midpoint_index+1,1])
        else
             sorted[below_midpoint_index+1,1]
        end
    end
end

end # module
