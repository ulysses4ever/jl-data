module FastGaussTransforms

export fastgausstransform, slowgausstransform, evaluate

type FastGaussTransform
  centers::Vector{Float64} # In general, an array of points
  coefficients::Array{Float64, 2} # In general, a rank-d tensor for every point
  h::Float64 # sqrt(2)*std
  ry::Float64 # neighbor radius used in evaluation
end

# Relative error is bounded above by
#
# (2*rx*ry)^order/factorial(order) + exp(-ry^2)
#
# Choose ry=iceil(sqrt(-log(rtol))), rx=0.5, and
# find order s.t. the error bound is less than rtol
function errorconstants(rtol)
  lrtol = log(rtol)
  rx = 0.5
  ry = sqrt(-log(rtol))
  order = 0
  c = (2/e)*rx*ry
  error = 1.0
  while rtol<error
    order += 1
    error *= c/order
  end
  return rx, ry, order
end

function fastgausstransform(xs, qs, std; rtol=eps(1.0))
  rx, ry, order = errorconstants(rtol)
  h = sqrt(2)*std
  xmin, xmax = extrema(xs)
  range = xmax - xmin
  centers = linspace(xmin, xmax, iceil(range/(2*h*rx)) + 1)
  ncenters = length(centers)
  coefficients = zeros(order + 1, ncenters)
  for (x, q) in zip(xs, qs)
    k = ncenters == 1 ? 1 : iround(((x-xmin)*ncenters+(xmax-x))/range)
    center = centers[k]
    t = (x-center)/h
    c = q*exp(-t^2)
    z = 1.0
    coefficients[1, k] += c
    for n in 1:order
      # nth term is q e^(-t^2) 2^n/n! t^n
      z *= 2/n*t
      coefficients[n + 1, k] += c*z
    end
  end
  return FastGaussTransform(centers, coefficients, h, ry)
end

function evaluate(f::FastGaussTransform, x)
  h = f.h
  g = 0.0
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
type SlowGaussTransform
  xs::Vector{Float64}
  qs::Vector{Float64}
  h::Float64
end

function slowgausstransform(xs, qs, std)
  return SlowGaussTransform(xs, qs, sqrt(2)*std)
end

function evaluate(f::SlowGaussTransform, x)
  g = 0.0
  for (xp, q) in zip(f.xs, f.qs)
    g += q*exp(-(x-xp)^2/f.h^2)
  end
  return g
end

end # module
