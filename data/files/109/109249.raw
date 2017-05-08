# This implements an efficient Gibbs sampler for the multivariate truncated
# normal distribution subject to linear constraints from:

# Y. Li and S. Ghosh (2015)
# "Efficient Sampling Methods for Truncated Multivariate Normal and Student-t
#  Distributions Subject to Linear Inequality Constraints"
# Journal of Statistical Theory & Practice
# doi: 10.1080/15598608.2014.996690
# http://dx.doi.org/10.1080/15598608.2014.996690

# using TruncatedMVN
# using Distributions
# using Convex, SCS

function GibbsTMVN(μ, Σ, c, d, R̃, NumSamples = 10000,
                   x_init = zeros(length(μ)))
  p = length(μ)
  m = size(R̃, 1)
  samples = zeros(p, NumSamples)
#   samples = zeros(NumSamples, p)
  Σhalf = chol(Σ)'
  Σhalfinv = Σhalf \ eye(m)
  R = R̃ * Σhalf
  a = c - R̃ * μ
  b = d - R̃ * μ
#   x = zeros(4)
#   x = copy(x_init)
  x = Σhalfinv * (x_init - μ)
  Rx = R * x
  # Make sure starting value is feasible:
  if !(all(Rx .>= a) && all(Rx .<= b))
    x = getFeasiblePoint(a, b, R)
  end

  astar = -Inf
  bstar = Inf
  tmp_l = zeros(m)
  tmp_u = zeros(m)
#   rx_mi = zeros(m)

  for iter = 1:NumSamples
    for i = 1:p
#       bds = GetBounds(a, b, R, x, i)
      GetBounds!(astar, bstar, tmp_l, tmp_u, a, b, R, x, i)
#       Spl = TruncatedNormalSampler(bds[1], bds[2])
      Spl = TruncatedNormalSampler(astar, bstar)
      x[i] = rand(Spl)
    end
#     samples[:, iter] = Σhalf * x + μ
#     samples[iter, :] = Σhalf * x + μ
    samples[:, iter] = x
  end

  @simd for iter = 1:NumSamples
     @inbounds samples[:, iter] = Σhalf * samples[:, iter] + μ
  end
  return samples
end

function getFeasiblePoint(a::Vector{Float64}, b::Vector{Float64}, R::Matrix{Float64})
  set_default_solver(SCSSolver(verbose=false))
  m = size(R, 2)
  x = Variable(m)
  # Convex solver doesn't work with Infinity constraints
  finiteidx_a = (1:m)[a .> -Inf]
  finiteidx_b = (1:m)[b .< Inf]
  problem = minimize(0)
  for i in finiteidx_a
    problem.constraints += R[i, :] * x >= a
  end
  for i in finiteidx_b
    problem.constraints += R[i, :] * x <= b
  end
  solve!(problem)
  return vec(x.value)
end

function GetBounds!(astar::Float64, bstar::Float64, tmp_l::Vector{Float64},
                    tmp_u::Vector{Float64}, # rx_mi::Vector{Float64},
                    a::Array{Float64}, b::Vector{Float64}, R::Matrix{Float64},
                    x::Vector{Float64}, i::Int)
  m = size(R, 1)
  p = size(R, 2)
  tmp_l[:] = 0.0
  tmp_u[:] = 0.0
#   rx_mi[:] = 0.0
  astar = -Inf
  bstar = Inf
#   for k = 1:p
#     for j = 1:m
#        k != i ? rx_mi[j] += R[j, k] * x[k] : continue
#     end
#   end

  for j = 1:m
    for k = 1:m
      if k != i
        tmp_l[j] -= R[j, k] * x[k]
      end
    end
    tmp_u[j] = copy(tmp_l[j])
    tmp_l[j] += a[j]
    tmp_l[j] /= R[j, i]
    tmp_u[j] += b[j]
    tmp_u[j] /= R[j, i]
  end

#   astar = -Inf
#   bstar = Inf
  for j = 1:m
    if R[j, i] > 0
      astar = max(tmp_l[j], astar)
      bstar = min(tmp_u[j], bstar)
    elseif R[j, i] < 0
      astar = max(tmp_u[j], astar)
      bstar = min(tmp_l[j], bstar)
    end
  end
#   astar = maximum([tmp_l[posidx], tmp_u[negidx]])
#   bstar = minimum([tmp_l[negidx], tmp_u[posidx]])
#   return (astar, bstar)
#   nothing
end

