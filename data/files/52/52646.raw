module WeightedStats

export weighted_mean, weighted_median

function weighted_mean{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    data = float(data)
    weights = float(weights) / sum(weights)
    (data' * weights)[1]
end

function weighted_median{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    mask = weights .> 0
    if any(mask)
        data = data[mask]
        weights = weights[mask]
        sorted = sortrows([data weights])
        midpoint = 0.5 * sum(weights)
        if any(weights .> midpoint)
            (data[weights .== maximum(weights)])[1]
        else
            cumulative_weight = 0
            below_midpoint_index = 0
            while cumulative_weight <= midpoint
                below_midpoint_index += 1
                cumulative_weight += sorted[below_midpoint_index,2]
            end
            cumulative_weight -= sorted[below_midpoint_index,2]
            below_midpoint_index -= 1
            if cumulative_weight == midpoint
                mean(sorted[below_midpoint_index:below_midpoint_index+1,1])
            else
                sorted[below_midpoint_index+1,1]
            end
        end
    end
end

end # module
