export zero_to_inf
export double_inf
export simpsons_rule_inf
export mid_point

function zero_to_inf(f; n = 10)
  h = 1/2.0^n
  x(k) = e^(pi*sinh(k))
  w(k) = x(k)*pi*cosh(k)
  approx = 0
  for k = -4.8:h:4.8
    f1 = f(x(k))*w(k)
    f2 = f(x(k + 1))*w(k + 1)
    approx += f1 + f2
  end
  approx = approx*h/2
  return approx
end

function double_inf(f; n = 10)
  approx = 0
  h = 1.0/2.0^n
  x(k) = sinh(pi*sinh(k)/2)
  w(k) = cosh(pi*sinh(k)/2)*pi*cosh(k)/2

  for k = -4.5:h:4.5
    approx += (f(x(k))*w(k) + f(x(k + 1))*w(k + 1))*h/2
  end
  return approx
end

function simpsons_rule_inf(f, a, b; n = 200)
  x(t) = 1/t
  g(t) = f(x(t))/t^2
  approx = simpsons_rule(g, 1/b, 1/a, n = n)
  return approx
end

function mid_point(f, a, b; n = 500)
  h = (b - a)/n
  sum = f(a + h/2)
  for i = 1:n-1
    sum += f(a + h/2 + i*h)
  end
  approx = h*sum
  return approx
end
