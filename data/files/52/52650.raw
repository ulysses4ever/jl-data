module WeightedStats

export weighted_mean, weighted_median

function weighted_mean{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    weights = float(weights) / sum(weights)
    first(float(data)' * weights)
end

function weighted_median{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    mask = weights .> 0
    if any(mask)
        data = data[mask]
        weights = weights[mask]
        midpoint = 0.5 * sum(weights)
        if any(weights .> midpoint)
            first(data[weights .== maximum(weights)])
        else
            permute = sortperm(data)
            i = cumulative_weight = 0
            for (i, p) in enumerate(permute)
                if cumulative_weight > midpoint
                    cumulative_weight -= weights[p]
                    break
                end
                cumulative_weight += weights[p]
            end
            if cumulative_weight == midpoint
                0.5 * (data[permute[i-2]] + data[permute[i-1]])
            else
                data[permute[i-1]]
            end
        end
    end
end

end # module
