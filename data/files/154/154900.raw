module FastGaussTransforms

export fastgausstransform, slowgausstransform, evaluate

type FastGaussTransform{T<:Real}
  centers::Vector{T} # In general, an array of points
  coefficients::Array{T, 2} # In general, a rank-d tensor for every point
  h::T # sqrt(2)*std
  ry::Int # neighbor radius used in evaluation
end

# Relative error is bounded above by
#
# (2*rx*ry)^order/factorial(order) + exp(-ry^2)
#
# Choose ry=iceil(sqrt(-log(rtol))), rx=0.5, and
# find order s.t. the error bound is less than rtol
function errorconstants(rtol)
  T = typeof(rtol)
  half = one(T)/2
  lrtol = log(rtol)
  rx = half
  ry = iceil(sqrt(-log(rtol/2.0)))
  order = 0
  # numerical prefactor here is determined empirically. Theory says it should be
  # 2, but in practice it appears that a smaller number of terms is sufficient.
  c = half*rx*ry
  error = one(T)
  while rtol<error
    order += 1
    error *= c/order
  end
  return rx, ry, order
end

function fastgausstransform(xs, qs, std; rtol=-1.0, order=-1.0, rx=-1.0, ry=-1.0)
  T = promote_type(eltype(xs), eltype(qs))
  rtol < 0 && (rtol = eps(T))
  _rx, _ry, _order = errorconstants(rtol)
  order < 0 && (order = _order)
  rx < 0 && (rx = _rx)
  ry < 0 && (ry = _ry)
  h = convert(T, sqrt(2)*std)
  xmin, xmax = extrema(xs)
  range = xmax - xmin
  centers = linspace(xmin, xmax, iceil(range/(2*h*rx)) + 1)
  ncenters = length(centers)
  coefficients = zeros(T, order + 1, ncenters)
  for (x, q) in zip(xs, qs)
    k = ncenters == 1 ? 1 : iround(((x-xmin)*ncenters+(xmax-x))/range)
    center = centers[k]
    t = (x-center)/h
    c = q*exp(-t^2)
    z = one(T)
    coefficients[1, k] += c
    for n in 1:order
      # nth term is q e^(-t^2) 2^n/n! t^n
      z *= 2/n*t
      coefficients[n + 1, k] += c*z
    end
  end
  return FastGaussTransform(centers, coefficients, h, ry)
end

function evaluate{T}(f::FastGaussTransform{T}, x)
  h = f.h
  g = zero(T)
  for (k, center) in enumerate(f.centers)
    t = (x - center)/h
    abs(t) > f.ry && continue

    s = f.coefficients[end, k]
    for n in size(f.coefficients,1)-1:-1:1
      s = f.coefficients[n, k] + t*s
    end
    g += exp(-t^2)*s

  end
  return g
end

# Dummy type used for comparison that just stores points directly,
# and then performs naive summation
type SlowGaussTransform{T<:Real}
  xs::Vector{T}
  qs::Vector{T}
  h::T
end

function slowgausstransform(xs, qs, std)
  T = promote_type(eltype(xs), eltype(qs))
  return SlowGaussTransform(xs, qs, convert(T, sqrt(2)*std))
end

function evaluate{T}(f::SlowGaussTransform{T}, x)
  g = zero(T)
  for (xp, q) in zip(f.xs, f.qs)
    g += q*exp(-(x-xp)^2/f.h^2)
  end
  return g
end

end # module
