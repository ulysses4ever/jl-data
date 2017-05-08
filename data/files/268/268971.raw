immutable DiscretePowerLaw <: DiscreteUnivariateDistribution
    α::Float64
    β::Int64

    function DiscretePowerLaw(α::Real, β::Real)
        (α > zero(α) && β > zero(β)) || error("DiscretePowerLaw: shape and scale must be positive")
        @compat new(Float64(α), Int64(β))
    end

    DiscretePowerLaw(α::Real) = DiscretePowerLaw(α, 1)
    DiscretePowerLaw() = new(2.0, 1)
end

@distr_support DiscretePowerLaw d.β Inf

# Parameters
shape(d::DiscretePowerLaw) = d.α
scale(d::DiscretePowerLaw) = d.β
params(d::DiscretePowerLaw) = (d.α, d.β)

# Statistics
mean(d::DiscretePowerLaw) = ((α, β) = params(d); α > 1.0 ? zeta(α) : Inf)

function median(d::DiscretePowerLaw)
    x = 1
    while ccdf(d, x) < 0.5
        x += 1
    end
    x
end

mode(d::DiscretePowerLaw) = d.β

# Evaluation
function pdf(d::DiscretePowerLaw, x::Int64)
    (α, β) = params(d)
    x >= β ? x^-α/zeta(α, β) : 0.0
end

function logpdf(d::DiscretePowerLaw, x::Int64)
    (α, β) = params(d)
    x >= β ? -α*log(x) - log(zeta(α, β)) : -Inf
end

function ccdf(d::DiscretePowerLaw, x::Int64)
    (α, β) = params(d)
    x >= β ?  zeta(α, x)/zeta(α, β) : 1.0
end

cdf(d::DiscretePowerLaw, x::Int64) = 1.0 - ccdf(d, x)

function logccdf(d::DiscretePowerLaw, x::Int64)
    (α, β) = params(d)
    α -= 1
    x >= β ? log(zeta(α, x)) - log(zeta(α, β)) : 0.0
end

logcdf(d::DiscretePowerLaw, x::Int64) = log1p(-ccdf(d, x))


# Sampling
function rand(d::DiscretePowerLaw; estimate=true)
    if estimate
        while true
            x = (d.β - 0.5)*(1.0 - rand())^(-1.0/(d.α - 1)) + 0.5
            if x<=typemax(Int)
                return iround(x)
            end
        end
    else
        while true
            r = rand()
            x2 = d.β
            while ccdf(d, x2) >= 1-r
                x1 = x2
                x2 = 2x1
            end
            func(x) = ccdf(d, x)
            xx = bisearch(div(x2, 2), x2, func, 1-r)
            if xx > 0
                return xx
            end
        end
    end
end


# Fit model
function fit_mle{T<:Real}(::Type{DiscretePowerLaw}, x::Vector{T}, β=findxmin(DiscretePowerLaw, x)[1]; return_all::Bool=false, estimate::Bool=true)
    x = x[x.>=β]
    n = float(length(x))
    if estimate
        α = 1 + n/sum(log(x/(β-0.5)))
        if return_all
            DiscretePowerLaw(α, β), (α - 1.0)/sqrt(n)
        else
            DiscretePowerLaw(α, β)
        end
    else
        c = sum(log(x))
        L(α) = n*log(zeta(α, β)) + α*c
        opt = optimize(L, [3.0], method=:bfgs)
        obj.gr_converged || error("can not optimize log likehood")
        α = obj.minimum
        if return_all
            f(x) = zeta(x, β)
            σ = 1/sqrt(n*(f''(α)/f(α) - (f'(α)/f(α))^2))
            DiscretePowerLaw(α, β), σ
        else
            DiscretePowerLaw(α, β)
        end
    end
end
