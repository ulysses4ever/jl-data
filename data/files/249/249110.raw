# Inverse CDF method
#
# copied from Distributions.jl, Feb 14, 2015
function randtn_invcdf(d::Truncated)
    d0 = d.untruncated
    if d.tp > 0.25
        while true
            r = rand(d0)
            if d.lower <= r <= d.upper
                return r
            end
        end
    else
        return quantile(d0, d.lcdf + rand() * d.tp)
    end
end


# Rejection sampler based on algorithm from Robert (1995)
#
#  - Available at http://arxiv.org/abs/0907.4010
#
# copied from Distributions.jl, Feb 14, 2015
function randtn_robert(d::Truncated{Normal})
    d0 = d.untruncated
    μ = mean(d0)
    σ = std(d0)
    a = (d.lower - μ) / σ
    b = (d.upper - μ) / σ
    z = randtn_robert_base(a, b, d.tp)
    return μ + σ * z
end

function randtn_robert_base(lb::Float64, ub::Float64, tp::Float64)
    r::Float64
    if tp > 0.3   # has considerable chance of falling in [lb, ub]
        r = randn()
        while r < lb || r > ub
            r = randn()
        end
        return r

    else 
        span = ub - lb
        if lb > 0 && span > 2.0 / (lb + sqrt(lb^2 + 4.0)) * exp((lb^2 - lb * sqrt(lb^2 + 4.0)) / 4.0)
            a = (lb + sqrt(lb^2 + 4.0))/2.0
            while true
                r = rand(Exponential(1.0 / a)) + lb
                u = rand()
                if u < exp(-0.5 * (r - a)^2) && r < ub
                    return r
                end
            end
        elseif ub < 0 && ub - lb > 2.0 / (-ub + sqrt(ub^2 + 4.0)) * exp((ub^2 + ub * sqrt(ub^2 + 4.0)) / 4.0)
            a = (-ub + sqrt(ub^2 + 4.0)) / 2.0
            while true
                r = rand(Exponential(1.0 / a)) - ub
                u = rand()
                if u < exp(-0.5 * (r - a)^2) && r < -lb
                    return -r
                end
            end
        else 
            while true
                r = lb + rand() * (ub - lb)
                u = rand()
                if lb > 0
                    rho = exp((lb^2 - r^2) * 0.5)
                elseif ub < 0
                    rho = exp((ub^2 - r^2) * 0.5)
                else
                    rho = exp(-r^2 * 0.5)
                end
                if u < rho
                    return r
                end
            end
        end
    end
end
