using DSP
using Base.Test

function extrema(X, extrema_type=:both)
    # return a boolean array of extrema (peaks, troughs or both)
    n = length(X)
    X1 = diff(X)
    X2 = diff(diff(X))

    Z1 = X2.*X1[1:n-2]
    Z2 = X2.*X1[2:n-1]

    E = zeros(Int, n-2)

    if extrema_type == :peaks
        E = (X2 .< 0) & (Z1 .< 0) & (Z2 .> 0)
    elseif extrema_type == :troughs
        E = (X2 .> 0) & (Z1 .< 0) & (Z2 .> 0)
    elseif extrema_type == :both
        E = (Z1 .< 0) & (Z2 .> 0)
    end

    return [false, E..., false]
end

function bin_sum(X :: Vector, bins :: Int)
    parts = int(round(linspace(1, length(X), bins+1)))
    map(i -> sum(X[parts[i]:parts[i+1]]), 1:bins)
end


