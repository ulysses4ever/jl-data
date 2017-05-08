module ModelsGenerators

export
  randiv, randiv_ts


## OLS design with Homo-skedasticity
## from: http://economics.mit.edu/files/7422


## IV many + heteroskedasticity
## from: http://econ.arizona.edu/docs/Seminar_Papers/Tiemen%20hetiv%202012%20feb.pdf
    
function sim_iv_d01!(Y::Vector, X::Matrix, Z::Matrix, ρ::Float64 = 0.3, ϕ::Float64 = 0.1, μ²::Float64 = 8.) 
    ## http://econ.arizona.edu/docs/Seminar_Papers/Tiemen%20hetiv%202012%20feb.pdf
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


function randiv(;n::Int64        = 100,
                m::Int64         = 5,
                k::Int64         = 1,
                theta0::Float64  = 0.0,
                rho::Float64     = 0.9,
                CP::Int64        = 20)

    ## Generate IV Model with CP

    randiv(n, m, k, theta0, rho, CP)
end

function randiv(n::Int64        = 100,
                m::Int64         = 5,
                k::Int64         = 1,
                theta0::Float64  = 0.0,
                rho::Float64     = 0.9,
                CP::Int64        = 20)

    ## Generate IV Model with CP
    tau     = fill(sqrt(CP/(m*n)), m)
    z       = randn(n, m)
    vi      = randn(n, 1)
    eta     = randn(n, 1)
    epsilon = rho*eta+sqrt(1-rho^2)*vi   
    BLAS.gemm!('N', 'N', 1.0, z, tau, 1.0, eta)
    #x      = z*tau .+ eta    
    #y      = x[:,1]*theta0 + epsilon
    BLAS.gemm!('N', 'N', 1.0, eta, [theta0], 1.0, epsilon)
    return epsilon, eta, z
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
