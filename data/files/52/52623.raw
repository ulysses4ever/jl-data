function weighted_median{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1};
                                          checknan::Bool=true)
    isempty(data) && error("median of an empty array is undefined")
    if length(data) != length(weights)
        error("data and weight vectors must be the same size")
    end
    if checknan
        for (i, x) in enumerate(data)
            (isnan(x) || isnan(weights[i])) && return NaN
        end
    end
    mask = weights .!= 0
    if any(mask)
        data = data[mask]
        weights = weights[mask]
        maxval, maxind = findmax(weights)
        midpoint = 0.5 * sum(weights)
        if maxval > midpoint
            data[maxind]
        else
            permute = sortperm(data)
            cumulative_weight = zero(eltype(weights))
            i = 0
            for (i, p) in enumerate(permute)
                if cumulative_weight > midpoint
                    cumulative_weight -= weights[p]
                    break
                end
                cumulative_weight += weights[p]
            end
            if cumulative_weight == midpoint
                middle(data[permute[i-2]], data[permute[i-1]])
            else
                middle(data[permute[i-1]])
            end
        end
    else
        error("No positive weights found")
    end
end
