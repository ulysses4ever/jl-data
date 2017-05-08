using Calculus
using NLopt

# assign in place
function (.=){T}(a::T, b::T)
    for f in names(a)
        setfield(a, f, getfield(b, f))
    end
end

type Cov
    f     :: Function
    f_x1  :: Function
    f_x2  :: Function
    f_xx  :: Function
end

function Cov(f::Function)
    f_x1(x1,x2,θ) = gradient(x -> f(x,x2,θ), x1)
    f_x2(x1,x2,θ) = gradient(x -> f(x1,x,θ), x2)

    function f_xx(x1,x2,θ)
        n = length(x1)
        C = zeros(n,n)
        for i=1:n
            C[i,:] = gradient(x -> f_x2(x,x2,θ)[i], x1)
        end
        return C
    end
  
    Cov(f, f_x1, f_x2, f_xx)
end

squared_exp = Cov((x, y, r) -> exp(-sum(0.5*(x-y).^2/r.^2)))                  

abstract Observation
immutable Val <: Observation end
immutable Deriv{n} <: Observation end    

cov     (cf::Cov, ::Val,      ::Val,      x1, x2, θ) = cf.f(x1, x2, θ)         :: Float64
cov{n}  (cf::Cov, ::Deriv{n}, ::Val,      x1, x2, θ) = cf.f_x1(x1, x2, θ)[n]   :: Float64
cov{n}  (cf::Cov, ::Val,      ::Deriv{n}, x1, x2, θ) = cf.f_x2(x1, x2, θ)[n]   :: Float64
cov{n,m}(cf::Cov, ::Deriv{n}, ::Deriv{m}, x1, x2, θ) = cf.f_xx(x1, x2, θ)[n,m] :: Float64

abstract GP

type DenseGP <: GP
    # the covariance function
    cf   :: Cov
    # noise model
    ν    :: Float64
    # hyperparameters for the covariance function
    θ    :: Vector{Float64}
    # inputs
    xs   :: Vector
    # observations
    ts   :: Vector{Float64}
    # types of the observations (value or derivative)
    Ts   :: Vector{Observation}
    # covariance matrix and its inverse
    C    :: Matrix{Float64}
    invC :: Matrix{Float64}
end

function DenseGP(cf::Cov, ν::Float64, θ::Vector{Float64}, xs::Vector, ts::Vector{Float64}, 
                 Ts::Vector{Observation})

    noise = diagm([(T == Val())?ν:1e-8 for T=Ts])
    C = [cov(cf, T1, T2, x1, x2, θ) for (T1,x1)=zip(Ts,xs), (T2,x2)=zip(Ts,xs)] + noise + 1e-4 * eye(length(Ts))
    DenseGP(cf, ν, θ, xs, ts, Ts, C, inv(C))
end

function set_hyperparameters!(gp::DenseGP, hypers::Vector{Float64})
    if (gp.ν != hypers[1]) || (gp.θ != hypers[2:])
        gp .= DenseGP(gp.cf, hypers[1], hypers[2:], gp.xs, gp.ts, gp.Ts)
    end
end

function gp_predict(gp::DenseGP, xnew, Tnew=Val())
    k = [cov(gp.cf, Tnew, T, xnew, x, gp.θ) for (x,T)=zip(gp.xs, gp.Ts)]
    kappa = cov(gp.cf, Tnew, Tnew, xnew, xnew, gp.θ) + gp.ν
    mean = (k' * gp.invC * gp.ts)[1]
    var = kappa - (k' * gp.invC * k)[1]
    (mean, var)
end

function log_lik(gp::DenseGP)
    -0.5 * (logdet(gp.C) + gp.ts' * gp.invC * gp.ts)[1]
end

type SparseGP <: GP
    m :: Int

    cf :: Cov
    ν :: Float64    
    θ :: Vector{Float64}

    xs :: Vector
    Ts :: Vector
    ts :: Vector

    Kmn_ts :: Vector{Float64}

    invKmm :: Matrix{Float64}
    Q :: Matrix{Float64}
    invQ :: Matrix{Float64}
end

function SparseGP(m::Int, cf::Cov, ν::Float64, θ::Vector{Float64}, xs::Vector, ts::Vector{Float64}, Ts::Vector{Observation})
    n = length(Ts)
    noise = zeros(n,m)
    noise[1:m,:] = diagm([(T == Val())?ν:1e-6 for T=Ts[1:m]])
    Knm = [cov(cf, T1, T2, x1, x2, θ) for (T1,x1)=zip(Ts,xs), (T2,x2)=zip(Ts[1:m],xs[1:m])] + 1e-10 * eye(n)[:,1:m]
    Kmn = Knm'
    Kmm = Knm[1:m,:]
    Kmn_ts = Kmn * ts
    invKmm = inv(Kmm)
    Q = Kmm * noise[1:m,:] + Kmn * Knm + 1e-10 * eye(m)
    invQ = inv(Q)

    SparseGP(m, cf, ν, θ, xs, Ts, ts, Kmn_ts, invKmm, Q, invQ)
end

function set_hyperparameters!(gp::SparseGP, hypers::Vector{Float64})
    if (gp.ν != hypers[1]) || (gp.θ != hypers[2:])
        gp .= SparseGP(gp.m, gp.cf, hypers[1], hypers[2:], gp.xs, gp.ts, gp.Ts)
    end
end

function gp_predict(gp::SparseGP, xnew, Tnew=Val())
    km = [cov(gp.cf, Tnew, T, xnew, x, gp.θ) for (x,T)=zip(gp.xs[1:gp.m], gp.Ts[1:gp.m])]
    kappa = cov(gp.cf, Tnew, Tnew, xnew, xnew, gp.θ) + 1e-5
    mean = (km' * gp.invQ * gp.Kmn_ts)[1]
    var = kappa - (km' * gp.invKmm * km - gp.ν * km' * gp.invQ * km)[1]
    (mean, var)
end

function log_lik(gp::SparseGP)
    m = gp.m
    n = length(gp.xs)
    -0.5 * ((n-m)log(gp.ν) + logdet(gp.Q) + (gp.ts'*gp.ts - gp.Kmn_ts' * gp.invQ * gp.Kmn_ts)[1]/gp.ν)
end

function log_lik!(gp::GP, hypers::Vector, grad::Vector)
    set_hyperparameters!(gp, hypers)

    ll = log_lik(gp)
    
    strify(vec) = chomp(string(vec'))
    print("log_lik! : ν=$(hypers[1])\t θ=[$(strify(hypers[2:]))]\t log(likelihood)=$ll\n")

    return ll
end

function log_lik_optim!(gp::GP, lbounds, ubounds; iterations=20, ftol_rel=1e-2)
    f(hypers,g) = log_lik!(gp,hypers,g)
    opt = Opt(:LN_BOBYQA, length(gp.ν)+length(gp.θ))
    max_objective!(opt, f)
    lower_bounds!(opt, lbounds)
    upper_bounds!(opt, ubounds)
    ftol_rel!(opt, ftol_rel)
    maxeval!(opt, iterations)
    (maxf, maxx, ret) = optimize(opt, [gp.ν, gp.θ])
end
