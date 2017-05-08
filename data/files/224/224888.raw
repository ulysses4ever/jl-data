function rand_cat(w::Vector)
    cw = cumsum(w)
    r = cw[end] * rand()
    i = 1
    while r > cw[i]
        i = i + 1
    end
    i
end

function rand_exp(l::Float64)
    u = rand()
    while u == 1
        u = rand()
    end
    -log(u)/l
end

# Copied from the lightspeed MATLAB tolbox
# (http://research.microsoft.com/en-us/um/people/minka/software/lightspeed/)
# Algorithm:
# G. Marsaglia and W.W. Tsang, A simple method for generating gamma
# variables, ACM Transactions on Mathematical Software, Vol. 26, No. 3,
# Pages 363-372, September, 2000.
# http://portal.acm.org/citation.cfm?id=358414
function rand_gamma(a::Float64, b::Float64)
    if a < 1.0
        # boost using Marsaglia's (1961) method: gam(a) = gam(a+1)*U^(1/a)
        boost = exp(log(rand()) / a)
        aa = a + 1
    else
        boost = 1
        aa = a
    end
    d = aa - 1.0/3.0
    c = 1.0 / sqrt(9*d)
    while true
        x = randn()
        v = 1 + c*x
        while v <= 0
            x = randn()
            v = 1 + c*x
        end
        v = v*v*v
        x = x*x
        u = rand()
        if (u < 1 - 0.0331*x*x) || (log(u) < 0.5*x + d*(1-v+log(v)))
            return (boost*d*v / b)
        end
    end
end

function rand_gamma(a::Float64, b::Float64, dim::Int)
    x = zeros(dim)
    for i = 1 : dim
        x[i] = rand_gamma(a, b)
    end
    x
end

function rand_gamma(a::Float64, b::Float64, dims::Dims)
    X = zeros(dims)
    for i in eachindex(X)
        @inbounds X[i] = rand_gamma(a, b)
    end
    X
end

function rand_dirichlet(a::Vector)
    x = zeros(length(a))
    for i = 1 : length(a)
        x[i] = rand_gamma(a[i], 1.0)
    end
    x / sum(x)
end

function rand_beta(a::Float64, b::Float64)
    x = rand_gamma(a, 1.0)
    y = rand_gamma(b, 1.0)
    x / (x+y)
end

function rand_beta(a::Float64, b::Float64, dim::Int)
    x = rand_gamma(a, 1.0, dim)
    y = rand_gamma(b, 1.0, dim)
    x ./ (x + y)
end

# Sample from Wishart distribution using Bartlett decomposition
# http://en.wikipedia.org/wiki/Wishart_distribution
# df: degree of freedom
# cScale: cholesky decomposition of Scale matrix (Scale = cScale * cScale')
# return cholesky decomposition of sampled matrix
function rand_wishart(df::Int, cScale::LowerTriangular)
    d = size(cScale)[1]
    A = zeros(d, d)
    for i = 1 : d
        A[i, i] = sqrt(rand_gamma(0.5*(df-i+1), 0.5))
        for j = 1 : i-1
            A[i, j] = randn()
        end
    end
    cScale * A
end

# random mixture models
# supported distributions:
# - gaussian (params["dist"] = "gaussian", params["d"] = 2, params["τ"] = 0.1, params["ν"] = 4)
# - multinomial (paramas["dist"] = "mult", params["d"] = 100, params["β"] = 0.1, params["M"] = 50)
include("corpus.jl")
typealias ParamDict Dict{UTF8String, Any}
function rand_mixture(gt_labels::Vector{Int}, params::ParamDict, K = 0)
    if K == 0
        K = length(unique(gt_labels))
    end
    N = length(gt_labels)
    dist = get(params, "dist", "err")
    if dist == "err"
        println("error; distribution must be specified")
        return []
    end
    if dist == "gaussian"
        d = get(params, "d", 2)
        τ = get(params, "τ", 0.1)
        ν = get(params, "ν", 4)
        @assert(ν > d - 1)
        X = zeros(d, N)
        Scale = randn(d, d)
        Scale = Scale*Scale' + eye(d)
        cScale = chol(Scale, Val{:L})
        sτ = sqrt(τ)        
        for k = 1 : K
            cΛ = rand_wishart(ν, cScale)
            cΣ = inv(cΛ)'
            μ = cΣ * randn(d) / sτ
            ind = find(gt_labels .== k)
            Nk = length(ind)
            X[:,ind] = repmat(μ, 1, Nk) + cΣ*randn(d, Nk)
        end
        return X
    elseif dist == "mult"
        d = get(params, "d", 100)
        β = get(params, "β", 0.1)
        M = get(params, "M", 50)
        X = Corpus(N, d)
        θ = Array(Vector, K)
        for k = 1 : K
            θ[k] = rand_dirichlet(fill(β, d))
        end        
        for n = 1 : N
            ntrials = rand(1:M)
            θn = θ[gt_labels[n]]
            for i = 1 : ntrials
                w = rand_cat(θn)
                if get(X.doc[n], w, 0) == 0
                    X.doc[n][w] = 1
                else
                    X.doc[n][w] += 1
                end
            end
        end
        return X
    else
        println("error; unsupported distribution")
        return []
    end
end

function rand_mixture(K::Int, N::Int, params::ParamDict)
    gt_labels = zeros(Int, N)
    for n = 1 : N
        gt_labels[n] = rand(1:K)
    end
    (rand_mixture(gt_labels, params, K), gt_labels)
end

function rand_crp(α::Float64, N::Int)
    labels = zeros(Int, N)
    Nk = zeros(0)
    for n = 1 : N
        p = [Nk; α]
        k = rand_cat(p)
        labels[n] = k
        if k <= length(Nk)
            Nk[k] += 1
        else
            Nk = vcat(Nk, 1.0)
        end
    end
    labels
end

function rand_pyp(α::Float64, σ::Float64, N::Int)
    labels = zeros(Int, N)
    Nk = zeros(0)
    for n = 1 : N
        p = [Nk - σ; α + length(Nk)*σ]
        k = rand_cat(p)
        labels[n] = k
        if k <= length(Nk)
            Nk[k] += 1
        else
            Nk = vcat(Nk, 1.0)
        end
    end
    labels
end
