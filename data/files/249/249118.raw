# Fast sampling from truncated normal distributions

using Distributions

include("randtn_zigtables.jl")

const log2π = 1.83787706641
const tnzig_kmin = 5

# returns sample x ~ N(0,1) truncated at [a,b], using rejection sampling with
# a truncated exponential proposal
function randtn_truncexp(a::Real, b::Real)
    twoasq = 2abs2(a)
    c = exp(-a*(b - a)) - 1
    while true
        z = log(1 + c * rand())
        if -twoasq * log(rand()) > abs2(z)
            return a - z/a
        end
    end
end

# returns sample x ~ N(0,1) truncated at [a,b], using rejection sampling with
# a standard normal proposal
function randtn_norm(a::Real, b::Real)
    while true
        z = randn()
        if z >= a && z <= b
            return z
        end
    end
end


# returns sample x ~ N(0,1) truncated at [a,b], assuming b > a and |a| < |b|.
function randtnstdord(a::Real, b::Real, tp::Real)
    # a in left tail, or large mass, implies b > -a, use normal proposal
    if a < tnzig_xmin || tp > 0.3
        return randtn_norm(a, b)
    end

    # a in right tail implies b > a, use truncated exponential proposal
    if a > tnzig_xmax
        return randtn_truncexp(a, b)
    end

    # tnzig_xmin <= a <= tnzig_xmax, use Chopin's algorithm
    N = length(tnzig_x) - 1
    # a in interval ka or ka+1
    ka = tnzig_ncell[tnzig_i0 + ifloor(a * tnzig_invh)]  
    kb = b < tnzig_xmax ?               # b in interval kb-1 or kb
        min(tnzig_ncell[tnzig_i0 + floor(b * tnzig_invh)] + 1, N) :
        N + 1                                     # b in right tail

    # for small kb - ka use rejection sampling with truncated exponential prop.
    if abs(kb - ka) < tnzig_kmin
        return randtn_truncexp(a, b)
    end

    while true
        # sample integer k from range [ka, kb]
        k = ka + ifloor((kb - ka + 1) * rand())

        if k == N + 1
            # right tail, rejection sampling with truncated exponential proposal
            xN1 = tnzig_x[end]
            z = -log(rand()) / xN1
            if abs2(z) < -2log(rand()) && z < b - xN1
                return xN1 + z
            end

        elseif k > ka + 1 && (k < kb - 1 || b >= tnzig_xmax)
            # all other intervals, away from boundaries
            u = rand()
            simy = tnzig_yu[k] * u;
            if simy < tnzig_yl[k]
                # happens most of the time
                return tnzig_x[k] + u * tnzig_delta[k]
            end
            # check if we are below the pdf curve
            sim = tnzig_x[k] + tnzig_d[k] * rand()
            if abs2(sim) + 2log(simy) + log2π < 0
                return sim
            end

        else
            # boundary intervals ka, ka+1, kb-1, kb
            sim = tnzig_x[k] + tnzig_d[k] * rand()
            if sim >= a && sim <= b
                simy = tnzig_yu[k] * rand()
                if simy < tnzig_yl[k] || abs2(sim) + 2log(simy) + log2π < 0
                    return sim
                end
            end
        end
    end
end
# same as randtnstdord, but does not require |a| < |b|
randtnstd(a::Real, b::Real, tp::Real) = abs(a) > abs(b) ? 
                                        -randtnstdord(-b, -a, tp) : 
                                        randtnstdord(a, b, tp)


function randtn(d::Truncated{Normal})
    d0 = d.untruncated
    μ = mean(d0)
    σ = std(d0)
    a = (d.lower - μ) / σ
    b = (d.upper - μ) / σ
    z = abs(a) > abs(b) ? -randtnstdord(-b, -a, d.tp) : randtnstdord(a, b, d.tp)
    return μ + σ * z
end
