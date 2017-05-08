export sinh_tanh

function sinh_tanh(f, a, b; n = 6)
  h = 0.5^n
  approx = f((a + b)/2)*0.25
  l = eps(Float64)

  for k = h:h:3.7
    qk = exp(-2sinh(k))
    d = (1 + qk)
    j = (b - a)*qk/d
    w = qk*cosh(k)/d^2
    if j > l
      approx += (f(a + j) + f(b - j))*w
    else
      approx += (f(a + 2.3e-16) + f(b - 2.3e-16))*w
    end
  end
  return approx*2*h*(b - a)
end