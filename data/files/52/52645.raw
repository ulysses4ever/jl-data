module WeightedStats

export weighted_mean, weighted_median

function weighted_mean{S<:Real,T<:Real}(data::Array{S,1}, weights::Array{T,1})
    data = float(data)
    weights = float(weights) / sum(weights)
    (data' * weights)[1]
end

function weighted_median{S<:Real,T<:Real}(data::Array{S,1}, weights::Array{T,1})
    sorted = sortrows([data weights])
    midpoint = 0.5 * sum(sorted[:,2])
    if any(weights .> midpoint)
        (data[weights .== maximum(weights)])[1]
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
