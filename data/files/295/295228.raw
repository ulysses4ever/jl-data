export sinh_tanh

function sinh_tanh(f, a, b, n)
  h = 1.0/2^n
  q(k) = e^(-2*sinh(k))
  subs(k) = (b - a)*q(k)/(1 + q(k))
  g(k) = 2*(b - a)*h*q(k)*cosh(k)/(1 + q(k))^2
  i = 1

  approx = f((a+b)/2)*g(0)

  for k = h:h:4
    j = subs(k)
    if j < 1e-16
      j = BigFloat(subs(k))
    end
    f1 = f(a + j)
    f2 = f(b - j)

    dxdt = g(k)
    approx += (f1 + f2)*dxdt
  end
return approx
end
