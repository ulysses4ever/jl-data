module ModelsGenerators

using Distributions

export
  randiv, randiv_ts


chisq_02 = Chisq(2)
tstud_02 = TDist(2)
bdist_05 = Bernoulli(.5)

function normm!(y::Array{Float64, 1}, x::Array{Float64, 2})
    n, m = size(x)
    for j=1:n
        for s=1:m        
           y[j] += x[j,s]^2
        end
        y[j] = y[j]^.5
    end
    return y
end

function normm(x::Array{Float64, 2})
    y = zeros(Float64, size(x,1))
    normm!(y, x)
end


function genma_one!(y::Vector, u::Vector, nu)    
    for j = 2:length(u)
        y[j] = u[j]+nu*u[j-1]
    end 
end

function genar_one!(y::Vector, u::Vector, rho)    
    for j = 2:length(u)
        y[j] = rho*y[j-1] + u[j]
    end 
end



############################################################################
## Instrumental Variables
##
############################################################################

function sim_iv_d01(;
                    n::Int64        = 100,
                    m::Int64         = 5,                    
                    theta0::Float64  = 0.0,
                    rho::Float64     = 0.9,
                    CP::Int64        = 20)
    ## OLS design with Homo-skedasticity
    ## from: http://economics.mit.edu/files/7422
    randiv(n, m, theta0, rho, CP)
end

function randiv(n::Int64        = 100,
                m::Int64        = 5,
                theta0::Float64 = 0.0,
                rho::Float64    = 0.9,
                CP::Int64       = 20)
    tau     = fill(sqrt(CP/(m*n)), m)
    z       = randn(n, m)
    vi      = randn(n, 1)
    eta     = randn(n, 1)
    epsilon = rho*eta+sqrt(1-rho^2)*vi   
    BLAS.gemm!('N', 'N', 1.0, z, tau, 1.0, eta)
    BLAS.gemm!('N', 'N', 1.0, eta, [theta0], 1.0, epsilon)
    return epsilon, eta, z
end


function sim_iv_d02!(Y::Vector, X::Matrix, Z::Matrix;
                     ρ::Float64 = 0.3, ϕ::Float64 = 0.1, μ²::Float64 = 8.)
    ## http://www.cemmap.ac.uk/wps/cwp2207.pdf
    ## Problem how to choose ϕ is not clear
    nx, p = size(X)
    nz, K = size(Z)
    ny    = length(Y)
    
    @assert nx==nz && nx==ny
    @assert p == 2
    
    mnk    = min(4, (K-1))
    z₁     = randn(nx)
    X[:,2] = randn(nx)
    
    @inbounds Z[:, 1:(mnk+1)] = hcat([(z₁.^i) for i = 0:mnk]...)
    
    if K>5
        @inbounds Z[:, 6:K] = hcat([z₁.*float(randn(nx).>0) for i = 1:(K-5)]...)
    end

    Π   = zeros(2, 1)
    fill!(Π, sqrt(μ²/nx))

    U₂ = randn(nx)
    υ₁ = randn(nx).*z₁
    υ₂ = randn(nx).*.86
    ϵ  = ρ*U₂ + sqrt((1-ρ^2)/(ϕ^2+.86^4))*(ϕ*υ₁ + 0.86*υ₂)

    Y[:] = X*Π + ϵ

end


function sim_iv_d03(; n = 100, m = 5, theta0 = 0.0, rho = 0.9, Pi = 0.1,
                    design = 1, heteroskedastic = false)
    Z = randn(n, m)
    X = randn(n, 1)
    if design == 1
        u = randn(n)
        V = randn(n)
    elseif design == 2
        w = rand(chisq_02, n)        
        u = randn(n)/(w/2.0).^.5
        V = rand(tstud_02, n)
    elseif design == 3
        u = randn(n).^2-1
        V = randn(n)
    elseif design == 4
        b = rand(bdist_05, n)
        u = randn(n)
        u = b.*abs(u+2)-(1-b)*abs(u-2)
        V = randn(n)
    else
        throw("Wrong design selected")
    end
    
    if heteroskedastic
        u = u.*normm(z)
    end 

    Y = X*theta0 + u
    X = Z[:,1]*Pi + V

    return Y, X, Z
end 


function dgp_hh(n::Int64 = 200, m::Int64 = 2, s::Float64 = 0.2,
                chisqmom::Int64 = 0, chisqdf::Int64 = 2, tmom::Int64 = 0,
                tdf::Int64 = 3, minus::Bool = false)
    ## Adapted from Hall and Horowitz (1996)
    ## They consider s = {0.2, 0.4}
    
    X = randn(n, 1).*s
    Z = randn(n, 1).*s
    W = Z
    if chisqmom > 0
        z_chisq = (rand(Chisq(chisqdf), (n, chisqmom)) - chisqdf)./sqrt(2*chisqdf)
        W = [W z_chisq]        
    end
    if tmom > 0
        z_tstud = rand(TDist(tdf), (n, chisqmom))./sqrt(tdf/(tdf-2))
        W = [W z_tstud]
    end    
    return X, Z, W
end


function dgp_hh(;n::Int64 = 200, m::Int64 = 2, s::Float64 = 0.2,
                chisqmom::Int64 = 0, chisqdf::Int64 = 2, tmom::Int64 = 0,
                tdf::Int64 = 3, minus::Bool = false)
    ## Adapted from Hall and Horowitz (1996)
    ## They consider s = {0.2, 0.4}
    ## Notice that mu = - 9s^2/2
    dgp_hh(n, m, s, chisqmom, chisqdf, tmom, tdf, minus)
end
                

function momfhh_s02(theta::Vector)
    n, m = size(W)
    g = Array(eltype(theta), n, m+1)
    mu = -9*0.2^2/2
    for i = 1:n
        @inbounds g[i, 1] = exp(mu - theta*X[i,1]+(3-theta)*Z[i,1])[1] - 1.0
    end
    for j = 2:m+1
        for i = 1:n
            @inbounds g[i, j] = g[i, 1]*W[i, j-1]
        end
    end
    return g
end

function momfhh_s04(theta)
    n, m = size(W)
    g = Array(Float64, n, m+1)
    mu = -9*0.4^2/2
    for i = 1:n
        @inbounds g[i, 1] = exp(mu - theta[1]*X[i,1]+(3-theta[1])*Z[i,1]) - 1.0
    end

    for j = 2:m+1
        for i = 1:n
            @inbounds g[i, j] = g[i, 1]*W[i, j-1]
        end
    end
    return g
end


function randiv_ts(n::Int64  =128,
                   m::Int64  = 2,
                   σ₁₂::Real = 0.9,
                   ϕ::Real = .5,
                   θ::Real = .5,
                   β::Real = 1.0,
                   burnin::Int64 = 1000)
  ## Same design as in
  ##
  ## http://faculty.georgetown.edu/gk232/research/KGMM.pdf
  ## Guido's parametrization
  ## ρ ∈ {.1, .5, .9}
  ## ϕ ∈ {.1, .3, .5}   # control quality instrument, low value weak
  ## θ ∈ {-.9, -.5, 0. .5, .9}

  nt  = n+m+burnin
  out = (burnin + 1):(n + burnin)
  #    y <- u <- x <- v <- rep(0, nt + 1)
  y1   = Array(Float64, nt+1)
  y2   = Array(Float64, nt+1)

  y1[1] = 0.0
  y2[1] = 0.0

  u₁  = randn(nt, 2)
  ρ   = [1.0 σ₁₂; σ₁₂ 1.0]
  u₁  = u₁*chol(ρ)

  y1[1] = β*y2[1] + u₁[1, 2]

  for j=2:nt
      @inbounds y2[j] = ϕ * y2[j-1] + u₁[j, 1]
      @inbounds y1[j] = β*y2[j] + u₁[j, 2] - θ*u₁[j-1, 2]
  end

  z = Array(Float64, n, 2*m)
  for j = 1:m
      @inbounds z[:, j] = y2[out-j]
  end

  for j = m+1:2*m
      @inbounds z[:, j] = y1[out-j]
  end

  return y1[out], y2[out], z

end


end
