export sinh_tanh

function sinh_tanh(f, a, b; n = BigFloat(6.0))
  h = BigFloat(0.5)^n
  approx = f((BigFloat(a) + BigFloat(b))*BigFloat(0.5))*BigFloat(0.25)
  l = eps(BigFloat)

  for k = h:h:BigFloat(5.2)
    qk = exp(-BigFloat(2.0)*sinh(k))
    d = (BigFloat(1.0) + qk)
    j = (BigFloat(b) - BigFloat(a))*qk/d
    w = qk*cosh(k)/d^BigFloat(2.0)
    approx += (f(a + j) + f(b - j))*w
  end
  return approx*BigFloat(2.0)*h*(BigFloat(b) - BigFloat(a))
end
