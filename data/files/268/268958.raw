immutable ContinuousPowerLaw <: ContinuousUnivariateDistribution
    α::Float64
    β::Float64

    function ContinuousPowerLaw(α::Real, β::Real)
        (α > zero(α) && β > zero(β)) || error("ContinuousPowerLaw: shape and scale must be positive")
        @compat new(Float64(α), Float64(β))
    end

    ContinuousPowerLaw(α::Real) = ContinuousPowerLaw(α, 1.0)
    ContinuousPowerLaw() = new(2.0, 1.0)
end

@distr_support ContinuousPowerLaw d.β Inf

#### Parameters

shape(d::ContinuousPowerLaw) = d.α
scale(d::ContinuousPowerLaw) = d.β
params(d::ContinuousPowerLaw) = (d.α, d.β)


#### Statistics

mean(d::ContinuousPowerLaw) = ((α, β) = params(d); α -= 1; α > 1.0 ? α * β / (α - 1.0) : Inf)
median(d::ContinuousPowerLaw) = ((α, β) = params(d); α -= 1; β * 2.0 ^ (1.0 / α))
mode(d::ContinuousPowerLaw) = d.β

function var(d::ContinuousPowerLaw)
    (α, β) = params(d)
    α -= 1
    α > 2.0 ? (β^2 * α) / ((α - 1.0)^2 * (α - 2.0)) : Inf
end

function skewness(d::ContinuousPowerLaw)
    α = shape(d)
    α -= 1
    α > 3.0 ? ((2.0 * (1.0 + α)) / (α - 3.0)) * sqrt((α - 2.0) / α) : NaN
end

function kurtosis(d::ContinuousPowerLaw)
    α = shape(d)
    α -= 1
    α > 4.0 ? (6.0 * (α^3 + α^2 - 6.0 * α - 2.0)) / (α * (α - 3.0) * (α - 4.0)) : NaN
end

entropy(d::ContinuousPowerLaw) = ((α, β) = params(d); α -= 1; log(β / α) + 1.0 / α + 1.0)


#### Evaluation

function pdf(d::ContinuousPowerLaw, x::Float64)
    (α, β) = params(d)
    α -= 1
    x >= β ? α * (β / x)^α * (1.0 / x) : 0.0
end

function logpdf(d::ContinuousPowerLaw, x::Float64)
    (α, β) = params(d)
    α -= 1
    x >= β ? log(α) + α * log(β) - (α + 1.0) * log(x) : -Inf
end

function ccdf(d::ContinuousPowerLaw, x::Float64)
    (α, β) = params(d)
    α -= 1
    x >= β ? (β / x)^α : 1.0
end

cdf(d::ContinuousPowerLaw, x::Float64) = 1.0 - ccdf(d, x)

function logccdf(d::ContinuousPowerLaw, x::Float64)
    (α, β) = params(d)
    α -= 1
    x >= β ? α * log(β / x) : 0.0
end

logcdf(d::ContinuousPowerLaw, x::Float64) = log1p(-ccdf(d, x))

cquantile(d::ContinuousPowerLaw, p::Float64) = d.β / p^(1.0 / (d.α - 1.0))
quantile(d::ContinuousPowerLaw, p::Float64) = cquantile(d, 1.0 - p)


#### Sampling

rand(d::ContinuousPowerLaw) = d.β * exp(randexp() / (d.α -1.0))

#rand(d::PowerLaw) = d.β / (1.0 - rand())^(1.0 / (d.α - 1.0))


#### Fit model

function fit_mle{T<:Real}(::Type{ContinuousPowerLaw}, x::Vector{T}, β=findxmin(ContinuousPowerLaw, x)[1]; return_all::Bool=false)
    x = x[x.>=β]
    n = length(x)
    α = 1.0 + n/(sum(log(x)) - n*log(β))
    if return_all
        ContinuousPowerLaw(α, β), (α - 1.0)/sqrt(n)
    else
        ContinuousPowerLaw(α, β)
    end
end