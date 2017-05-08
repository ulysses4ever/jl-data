function weighted_mean{T<:Real,W<:Real}(data::Array{T,1}, weights::Array{W,1})
    weights = float(weights) / sum(weights)
    first(float(data)' * weights)
end
