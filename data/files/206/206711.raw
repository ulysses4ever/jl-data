module ModelsGenerators

export
  randiv, randiv_ts

# package code goes here
function randiv(;n::Int64        = 100,
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
    x       = z*tau .+ eta
    if k>1
        x_ex = randn(n, k-1)
        x = [x  x_ex]
        z = [z  x_ex]
    end
    y       = x[:,1]*theta0 + epsilon
    return y, x, z
end


function randiv_ts(n::Int64; m::Int64 = 2, σ₁₂::Real = 0.9, ϕ::Real = .5, θ::Real = .5, β::Real = 1.0, burnin::Int64 = 1000)
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
  y    = Array(Float64, nt+1)
  x    = Array(Float64, nt+1)
  x[1] = 0.0
  y[1] = 0.0

  u₁  = randn(nt, 2)
  ρ   = [1.0 σ₁₂; σ₁₂ 1.0]
  u₁  = u₁*chol(ρ)

  y[1] = β*x[1] + u₁[1, 2]

  for j=2:nt
    x[j] = ϕ * x[j-1] + u₁[j-1, 1]
    y[j] = β*x[j] + u₁[j, 2] - θ*u₁[j-1, 2]
  end

  z = ones(n, 2*m+1)
  for j = 2:m+1
    z[:, j] = x[out-j]
  end

  for j = m+2:2*m+1
    z[:, j] = y[out-j]
  end

  return y[out], [ones(n) x[out]], z

end


end
