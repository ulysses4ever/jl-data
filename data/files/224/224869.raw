function rand_cat(w::Vector{Float64})
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

function rand_beta(a::Float64, b::Float64)
    x = rand_gamma(a, 1.0)
    y = rand_gamma(b, 1.0)
    x / (x+y)
end

# Sample from Wishart distribution using Bartlett decomposition
# http://en.wikipedia.org/wiki/Wishart_distribution
# df: degree of freedom
# cScale: cholesky decomposition of Scale matrix (Scale = cScale * cScale')
# return cholesky decomposition of sampled matrix
function rand_wishart(df::Int, cScale::Triangular{Float64})
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

function rand_mog(d::Int, n::Int; k=-1, gt_labels=zeros(0), df=2*d, r=0.08)
    if isempty(gt_labels)
        if k == -1
            println("error; you must specify the number of clusters or ground truth labels.")
        end
        gt_labels = zeros(n)
        w = ones(k)
        for i = 1 : n
            gt_labels[i] = rand_cat(w)
        end
    else
        k = length(unique(gt_labels))
    end
    X = zeros(d, n)
    Scale = randn(d, d)
    Scale = Scale*Scale' + eye(d)
    cScale = chol(Scale, :L)
    sr = sqrt(r)
    for j = 1 : k
        cLambda = rand_wishart(df, cScale)
        cSigma = inv(cLambda)'
        mu = cSigma * randn(d) / sr
        ind = gt_labels .== j
        nk = sum(ind)
        X[:, ind] = repmat(mu,1,nk) + cSigma*randn(d,nk)
    end
    X, gt_labels
end
