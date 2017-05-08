export simpsons_rule
export trapezoidal_rule
export midpoint_rule
export romberg_rule

function simpsons_rule(f::Function, a, b; n::Int = 200)
  if n%2 != 0
    n += 1
  end
  const h = (b - a)/n
  approx = f(a) + f(b) + 4f(a + h)
  for i = 2 : 2 : n - 1
    x = a + i*h
    approx += 2f(x) + 4f(x + h)
  end
  return approx*(h/3)
end

function trapezoidal_rule(f::Function, a, b; n::Int = 500)
  const h = (b - a)/n
  approx = (f(a) + f(b))/2
  for i = 1 : n - 1
    x = a + i*h
    approx += f(x)
  end
  return approx*h
end

function midpoint_rule(f::Function, a, b; n::Int = 500)
  const h = (b - a)/n
  approx = f(a + h/2)
  for i = 1 : n - 1
    approx += f(a + h/2 + i*h)
  end
  return h*approx
end

function romberg_rule(f::Function, a, b; n::Int = 4)
  const h = (b - a)/n
  const r = 1 + Int(log2(n))
  I = [trapezoidal_rule(f, a, b, n = 2^i) for i = 0 : r - 1]
  for i = 1 : r - 1
    I = [I[j + 1] + (I[j + 1] - I[j])/(4^i - 1) for j = 1 : r - i]
  end
  return I[1]
end