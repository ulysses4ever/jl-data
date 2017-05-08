function bisearch(mn::Int, mx::Int, func::Function, target::Float64)
    if func(mn) < target || func(mx) > target
        return -1
    end
    while true
        if mx == mn + 1
            return mn
        end
        m = div(mn+mx, 2)
        value = func(m)
        if value > target
            mn = m
        elseif value < target
            mx = m
        else
            return m
        end
    end
end

pdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [pdf(d, x) for x in X]
ccdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [ccdf(d, x) for x in X]
cdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [cdf(d, x) for x in X]
logpdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [logpdf(d, x) for x in X]
logccdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [logccdf(d, x) for x in X]
logcdf{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}) = [logcdf(d, x) for x in X]

# Loglikelihood ratio test
function lrt{T<:Real}(X::AbstractArray{T}, d1::UnivariateDistribution, d2::UnivariateDistribution)
    n = length(X)
    R = sum(logpdf(d1,X) - logpdf(d2, X))
    l̄1 = mean(logpdf(d1, X))
    l̄2 = mean(logpdf(d2, X))
    σ² = sum([(logpdf(d1,x)-logpdf(d2,x)-l̄1+l̄2)^2 for x in X])/n
    σ = sqrt(σ²)
    p = abs(erfc(R/σ/sqrt(2n)))
    R, σ, p
end

# Empirical CCDF
function eccdf{T<:Real}(X::AbstractArray{T})
    Xs = sort(X)
    n = length(X)
    ef(x::Real) = (n - searchsortedfirst(Xs, x) + 1) / n
    function ef{R<:Real}(v::AbstractArray{R})
        ord = sortperm(v)
        m = length(v)
        r = Array(T, m)
        r0 = 0
        i = 1
        for x in Xs
            while i <= m && x >= v[ord[i]]
                r[ord[i]] = n - r0
                i += 1
            end
            r0 += 1
            if i > m
            	break
            end
        end
        while i <= m
            r[ord[i]] = 1
            i += 1
        end
        return r / n
    end
    return ef
end

# KS test
function ks{T<:Real}(X::AbstractArray{T}, d::UnivariateDistribution)
    ef = eccdf(X)
    X = X[X .>= d.β]
    X = unique(X)
    δp = maximum(ef(X) - ccdf(d, X))
    δn = -minimum(ef(X) - ccdf(d, X))
    max(δp, δn)
end


# Search for the best fit parameters for the target distribution on this data, may be take a while
function findxmin{T<:Real, DType<:UnivariateDistribution}(DistributionType::Type{DType}, x::Vector{T}, xmin=minimum(x), xmax=maximum(x); return_all::Bool=false)
    D(β) = ks(x, fit_mle(DistributionType, x, β))
    xmins = x[xmin .<= x .<= xmax]
    xmins = unique(xmins)
    Ds = map(D,xmins)
    Dmin, idx = findmin(Ds)
    if return_all
        xmins, Ds
    else
        xmins[idx], Dmin
    end
end


# Generate synthetic data sets for estimating p-value
function generate_synthetic_data{T<:Real}(X::Vector{T}, d::UnivariateDistribution)
    n = length(X)
    Y = zeros(X)
    Xtail = X[X .< d.β]
    ntail = length(Xtail)
    p = ntail/n
    if ntail>0
        for i=1:n
            if rand() < p
                Y[i] = Xtail[rand(1:ntail)]
            else
                Y[i] = rand(d)
            end
        end
    else
        Y = rand(d,n)
    end
    Y
end


# p-value,  p_eps is the required precision, default 0.01
#For a given precision p_eps, plfit will use 1 / (4 * eps^2) iterations, so be prepared for a long wait when eps is small
function pvalue{T<:Real}(d::UnivariateDistribution, X::AbstractArray{T}, p_eps::T=0.01)
    D = ks(X, d)
    cnt = 0
    N = int(0.25/p_eps/p_eps)
    for i=1:N
        Y = generate_synthetic_data(X, d)
        if ks(Y, d) > D
            cnt += 1
        end
    end
    cnt/N
end
