export simpsons_rule
export trapezoidal_rule
export midpoint_rule
export romberg_rule

function simpsons_rule(f, a, b; n = 200)
  if n%2 != 0
    n += 1
  end
  h = (b - a)/n
  approx = f(a) + f(b) + 4f(a + h)
  for i = 2 : 2 : n - 1
    x = a + i*h
    approx += 2f(x) + 4f(x + h)
  end
  return approx*(h/3)
end

function trapezoidal_rule(f, a, b; n = 500)
  h = (b - a)/n
  approx = (f(a) + f(b))/2
  for i = 1 : n - 1
    x = a + i*h
    approx += f(x)
  end
  return approx*h
end

function midpoint_rule(f, a, b; n = 500)
  h = (b - a)/n
  approx = f(a + h/2)
  for i = 1 : n - 1
    approx += f(a + h/2 + i*h)
  end
  return h*approx
end

function romberg_rule(f, a, b, n)
  const h = (b - a)/n
  x = [a + i*h for i = 0 : n]
  F = map(f, x)
  r = 1 + Int(log(2, n))
  I = Float64[]
  const si = (F[1] + F[n + 1])/2

  for i = 1 : r
    s = si
    nn = 2^(i - 1)
    d = div(n, nn)
    for k = 1 : nn - 1
      s += F[1 + k*d]
    end
    push!(I, s*(b - a)/nn)
  end
  
  for i = 1 : r - 1
    I = [I[j + 1] + (I[j + 1] - I[j])/(4^i - 1) for j = 1 : r - i]
  end
  return I[1]
end