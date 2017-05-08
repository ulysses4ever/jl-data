function sinh_tanh(f, a, b; Nf = 2^5)

  h = 9.0/(Nf - 1)
  nt = 0

  q(k) = e^(-2*sinh(k))
  subs(k) = (b - a)*q(k)/(1 + q(k))
  g(k) = 2*(b - a)*q(k)*cosh(k)/(1 + q(k))^2
  approx = f((a + b)/2)*g(0)*h
  nt+=1

  for k = h:h:4.5
    j = subs(k)
    dxdt = g(k)
    f1 = f(a + j)
    f2 = f(b - j)

    if abs(f1) == Inf || abs(f2) == Inf
      break
    end
    
    nt += 2

    if nt > Nf
      break
    end

  approx += (f1 + f2)*dxdt*h
  end
return approx
end

function zero_to_inf(f; Nf = 2^5)

  h = 18.0/(Nf - 2)
  nt = 0

  x(k) = e^(pi*sinh(k))
  w(k) = x(k)*pi*cosh(k)
  approx = 0
  for k = -4.5:h:4.5
    f1 = f(x(k))*w(k)
    f2 = f(x(k + 1))*w(k + 1)
    nt += 2

    if nt > Nf
      break
    end

    approx += f1 + f2
  end
  approx = approx*h/2
  return approx
end

function simpsons_rule_inf(f, a, b; Nf = 2^5)
  h = 18/Nf
  x(t) = 1/t
  g(t) = f(x(t))/t^2
  approx = simpsons_rule(g, 1/b, 1/a, Nf = Nf)
  return approx
end

function mid_point(f, a, b; Nf = 2^5)

  h = (b - a)/Nf
  sum = f(a + h/2)
  for i = 1:Nf-1
    sum += f(a + h/2 + i*h)
  end
  approx = h*sum
  return approx
end

function double_inf(f; Nf = 2^5)

  approx = 0
  h = 18/(Nf-1)
  nt = 0
  x(k) = sinh(pi*sinh(k)/2)
  w(k) = cosh(pi*sinh(k)/2)*pi*cosh(k)/2

  for k = -4.5:h:4.5
    approx += (f(x(k))*w(k) + f(x(k + 1))*w(k + 1))*h/2
    nt += 2

    if nt > Nf
      break
    end

  end
  return approx
end

function simpsons_rule(f, a, b; Nf = 2^5)

  n = Nf - 2
  nt = 0

  if n%2 != 0
    n += 1
  end
  h = (b - a)/n
  approx = (f(a) + f(b) + 4f(a + h))
  nt += 3 
  for i = 2:2:n-1
    x = a + i*h
    approx += 2f(x) + 4f(x + h)
    nt += 2

    if nt > Nf
      break
    end 

  end
  return approx*(h/3)
end

function trapezoidal_rule(f, a, b; Nf = 2^5)

  n = Nf - 1
  nt = 0

  h = (b - a)/n
  approx = (f(a) + f(b))/2
  nt += 2
  for i = 1:n-1
    x = a + i*h
    approx += f(x)
    nt += 1

    if nt > Nf
      break
    end
  end
  return approx*h
end

function open_formula(f, a, b; Nf = 200)
  n = Nf + 2
  h = (b - a)/n
  approx = 3/2(f(a + h) + f(b - h))

  for i = 2:n - 2
    approx += f(a + i*h)
  end
  return h*approx
 end
 
function gaussian_quadrature(f, a, b; Nf = 16.0)
  h = 2(b-a)/Nf
  atemp = 0.0
  btemp = h
  approx = 0.0
  x1(atemp, btemp) = (atemp + btemp + sqrt(3)/3*h)/2
  x2(atemp, btemp) = (atemp + btemp - sqrt(3)/3*h)/2

  for k = 1:1:Nf/2
    approx += (f(x1(atemp, btemp)) + f(x2(atemp, btemp)))
    atemp+=h; btemp+=h;
  end

  return approx*h/2
end