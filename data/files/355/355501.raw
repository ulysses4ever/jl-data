export sinh_tanh

function sinh_tanh(f, a, b, n)
  h = 1.0/2^n
  q(k) = e^(-2*sinh(k))
  subs(k) = (b - a)*q(k)/(1 + q(k))
  g(k) = 2*(b - a)*q(k)*cosh(k)/(1 + q(k))^2
  approx = f((a + b)/2)*g(0)*h

  for k = h:h:4.5
    j = subs(k)
    dxdt = g(k)
    if j < eps(b)
      break
    end
    f1 = f(a + j)
    f2 = f(b - j)
  approx += (f1 + f2)*dxdt*h
  end
return approx
end
