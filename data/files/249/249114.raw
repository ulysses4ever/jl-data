# Fast sampling from truncated normal distributions

include("randtn_zigtables.jl")

const log2π = 1.83787706641
const tnzig_kmin = 5

# returns sample x ~ N(0,1) truncated at [a,b], using rejection sampling with
# a truncated exponential proposal
function randtn_truncexp(a, b)
    twoasq = 2abs2(a)
    c = exp(-a*(b - a)) - 1
    while true
        z = log(1 + c * rand())
        (-twoasq * log(rand()) > abs2(z)) && return a - z/a        
    end
end

# returns sample x ~ N(0,1) truncated at [a,b], using rejection sampling with
# a standard normal proposal
function randtn_norm(a, b)
    while true
        z = randn()
        (z >= a && z <= b) && return z
    end
end


# returns sample x ~ N(0,1) truncated at [a,b], assuming b > a and |a| < |b|.
function randtnstd(a::Real, b::Real)
    const N = length(tnzig_x) - 1
    @assert N == length(tnzig_yl) == length(tnzig_yu) == length(tnzig_d) == length(tnzig_delta)
    
    # a in left tail implies b > -a, use normal proposal
    a < tnzig_xmin && return randtn_norm(a, b)

    # a in right tail implies b > a, use truncated exponential proposal
    a > tnzig_xmax && return randtn_truncexp(a, b)

    # tnzig_xmin <= a <= tnzig_xmax, use Chopin's algorithm
    # a in interval ka or ka+1
    ka = tnzig_ncell[tnzig_i0 + ifloor(a * tnzig_invh)]  
    kb = b < tnzig_xmax ?                         # b in interval kb-1 or kb
        min(tnzig_ncell[tnzig_i0 + floor(b * tnzig_invh)] + 1, N) :
        N + 1                                     # b in right tail

    # for small kb - ka use rejection sampling with truncated exponential prop.
    abs(kb - ka) < tnzig_kmin && return randtn_truncexp(a, b)

    while true
        # sample integer k from range [ka, kb]
        k = ka + ifloor((kb - ka + 1) * rand())

        if k == N + 1
            # right tail, rejection sampling with truncated exponential proposal
            xN1 = tnzig_x[end]
            z = -log(rand()) / xN1
            (abs2(z) < -2log(rand()) && z < b - xN1) && return xN1 + z

        elseif k > ka + 1 && (k < kb - 1 || b >= tnzig_xmax)
            # all other intervals, away from boundaries
            u = rand()
            simy = tnzig_yu[k] * u;
            if simy < tnzig_yl[k]
                return tnzig_x[k] + u * tnzig_delta[k]  # happens most of the time
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


# returns sample x ~ N(0,1) truncated at [a,b], assuming b > a
randtn(a::Real, b::Real) = abs(a) > abs(b) ? -randtnstd(-b, -a) : randtnstd(a, b)

# returns sample x ~ N(μ,σ) truncated at [a,b], assuming b > a
randtn(μ::Real, σ::Real, a::Real, b::Real) = σ * randtn((a - μ) / σ, (b - μ) / σ) + μ
