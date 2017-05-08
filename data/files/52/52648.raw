module WeightedStats

export weighted_mean, weighted_median

function weighted_mean{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    weights = float(weights) / sum(weights)
    first(float(data)' * weights)
end

function weighted_median{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    mask = (weights .> 0)::BitArray{1}
    if any(mask)
        data = data[mask]
        weights = weights[mask]
        sorted = sortrows([data weights])
        midpoint = 0.5 * sum(weights)
        if any(weights .> midpoint)
            first(data[weights .== maximum(weights)])
        else
            cumulative_weight = below_midpoint_index = 0
            while cumulative_weight <= midpoint
                below_midpoint_index += 1
                cumulative_weight += sorted[below_midpoint_index,2]
            end
            cumulative_weight -= sorted[below_midpoint_index,2]
            if cumulative_weight == midpoint
                mean(sorted[below_midpoint_index-1:below_midpoint_index,1])
            else
                sorted[below_midpoint_index,1]
            end
        end
    end
end

end # module
