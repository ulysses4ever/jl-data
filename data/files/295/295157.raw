export zero_to_inf
export double_inf
export simpsons_rule_inf
export mid_point

function zero_to_inf(f, n)
  approx = 0
  s = 2.0^n
  h = 4.5/2.0^n
  x(k) = e^(pi*sinh(k*h))
  w(k) = x(k)*pi*cosh(k*h)

  for k = -s:s-1
    approx += (f(x(k))*w(k) + f(x(k + 1))*w(k + 1))*h/2
  end
  return approx
end

function double_inf(f, n)
  approx = 0
  s = 2.0^n
  h = 4.5/2.0^n
  x(k) = sinh(pi*sinh(k*h)/2)
  w(k) = cosh(pi*sinh(k*h)/2)*pi*cosh(k*h)/2

  for k = -s:s-1
    approx += (f(x(k))*w(k) + f(x(k + 1))*w(k + 1))*h/2
  end
  return approx
end

function simpsons_rule_inf(f, a, b, n)
  x(t) = 1/t
  g(t) = f(x(t))/t^2
  approx = simpsons_rule(g, 1/b, 1/a, n)
  return approx
end

function mid_point(f, a, b, n)
  h = (b - a)/n
  sum = f(a + h/2)
  for i=1:n-1
    sum += f(a + h/2 + i*h)
  end
  approx = h*sum
  return approx
end
