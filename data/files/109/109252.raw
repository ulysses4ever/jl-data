immutable TruncatedNormalSampler <: Sampleable{Univariate, Continuous}
  a::Float64       # Lower bound
  b::Float64       # Upper bound
  m::ASCIIString   # Sampling method to use: NR, HR, UR or ER
  sgn::Int64       # Change sign of result to be returned?
end

function TruncatedNormalSampler(a, b)
  m::ASCIIString
  sgn = 1
  a0 = 0.2570

  # Needs to work for untracated regions
  a == -Inf && b == Inf && return TruncatedNormalSampler(a, b, "NR", sgn)

  # Symmetric case, return negative of result
  if b <= 0  || a == -Inf
    sgn = -1
    olda = a
    a = -b
    b = -olda
  end

  b1 = a + sqrt(π/2) * exp(a^2/2)
  b2 = a + 2 / (a + sqrt(a^2 + 4)) * exp((a^2 - a*sqrt(a^2 +4))/4 + .5)

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
  a = s.a
  b = s.b
  sgn = s.sgn
  if s.m == "NR"
    while true
      x = randn()
      x >= a && x <= b && return x*sgn
    end
  elseif s.m == "HR"
    while true
      x = abs(randn())
      x >= a && x <= b && return x*sgn
    end
  elseif s.m == "UR"
#     pc::Float64   # Constant in acceptance probability
    Zd = Normal(0, 1)
    Uab = Uniform(a, b)
    pc = (cdf(Zd, b) - cdf(Zd, a))
    if a >= 0
      pc *= exp(a^2/2)
    elseif b <= 0
      pc *= exp(b^2/2)
    end
    while true
      u = rand()
      x = rand(Uab)
      u < exp(-x^2/2) * pc && return x*sgn
    end
  elseif s.m == "ER"
    while true
      λ = (a + sqrt(a^2 + 4)) / 2
      x = randexp() / λ + a
      u = rand()
      p = exp(-(x-λ)^2 / 2)
      u < p && x <= b && return x*sgn
    end
  end
end
