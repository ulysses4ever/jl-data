# This implements an efficient sampler for the univariate truncated
# standard normal distribution from:

# Y. Li and S. Ghosh (2015)
# "Efficient Sampling Methods for Truncated Multivariate Normal and Student-t
#  Distributions Subject to Linear Inequality Constraints"
# Journal of Statistical Theory & Practice
# doi: 10.1080/15598608.2014.996690
# http://dx.doi.org/10.1080/15598608.2014.996690

immutable TruncatedNormalSampler <: Sampleable{Univariate, Continuous}
  a::Float64       # Lower bound
  b::Float64       # Upper bound
  m::ASCIIString   # Sampling method to use:
                   #   NR: Normal rejection sampling
                   #   HR: Half-Normal rejection sampling
                   #   UR: Uniform rejection sampling
                   #   ER: Translated exponential rejection sampling
  sgn::Int64       # Change sign of result to be returned?
end

function TruncatedNormalSampler(a::Float64, b::Float64)
  m::ASCIIString
  sgn = 1
  a0 = 0.2570

  # Needs to work for untruncated regions
  if a == -Inf && b == Inf
    return TruncatedNormalSampler(a, b, "NR", sgn)
  end

  # Symmetric case, return negative of result
  if b <= 0  || a == -Inf
    sgn = -1
    olda = a
    a = -b
    b = -olda
  end

  b1 = a + sqrt(π/2) * exp(a*a/2)
  b2 = a + 2 / (a + sqrt(a*a + 4)) * exp((a*a - a*sqrt(a*a +4))/4 + .5)

  # Determine method to use
  a < 0 ?
    b == Inf ? m = "NR" :
      b - a <= sqrt(2π) ? m = "UR" : m = "NR" :
    b == Inf ?
      a < a0 ? m = "HR" : m = "ER" :
      a < a0 ?
        b <= b1 ? m = "UR" : m = "HR" :
        b <= b2 ? m = "UR" : m = "ER"

  return TruncatedNormalSampler(a, b, m, sgn)
end

function rand(s::TruncatedNormalSampler)
#   a = s.a
#   b = s.b
#   sgn = s.sgn
  if s.m == "NR"
    while true
      x = randn()
      x >= s.a && x <= s.b && return x*s.sgn
    end
  elseif s.m == "HR"
    while true
      x = abs(randn())
      if x >= s.a && x <= s.b
        return x*s.sgn
      end
    end
  elseif s.m == "UR"
    Zd = Normal(0, 1)
    Uab = Uniform(s.a, s.b)
    pc = (cdf(Zd, s.b) - cdf(Zd, s.a))
    if s.a >= 0
      pc *= exp(s.a*s.a/2)
    elseif s.b <= 0
      pc *= exp(s.b*s.b/2)
    end
    u = 0.0
    x = 0.0
    while true
      u = rand()
      x = rand(Uab)
      if u < exp(-x*x/2) * pc
        return x*s.sgn
      end
    end
  elseif s.m == "ER"
    λ = (s.a + sqrt(s.a*s.a + 4)) / 2
    u = 0.0
    x = 0.0
    p = 0.0
    while true
      x = randexp() / λ + s.a
      u = rand()
      p = exp(-(x-λ)^2 / 2)
      u < p && x <= s.b && return x*s.sgn
    end
  end
end
