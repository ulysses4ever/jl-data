export sinh_tanh

function sinh_tanh(f, a, b; n = 6)
  h = 0.5^n
  approx = f((a + b)/2)/4
  l = eps(Float64)

  for k = h:h:3.7
    qk = exp(-2sinh(k))
    d = (1 + qk)
    j = (b - a)*qk/d
    w = qk*cosh(k)/d^2
    j > l ? approx += (f(a + j) + f(b - j))*w : approx += (f(a + 2.3e-16) + f(b - 2.3e-16))*w
  end
  return approx*2*h*(b - a)
end

function sinh_tanh(f, a, b, tol; n = 6)
  h = 0.5^n
  approx = f((a + b)/2)/4
  sup = asinh(-log(tol)/2)
  hb = (b - a)

  for k = h:h:sup
    qk = exp(-2sinh(k))
    d = (1 + qk)
    j = hb*qk/d
    w = qk*cosh(k)/d^2
    approx += (f(a + j) + f(b - j))*w
  end
  return approx*2*h*hb
end

function sinh_tanh(f, a::BigFloat, b::BigFloat; n = 12)
  big_one = one(BigFloat)
  h = (big_one/2)^n
  approx = f((a + b)*(big_one/2))*big_one/4
  l = eps(BigFloat)

  for k = h:h:BigFloat(52)/10
    qk = exp(-big_one*2*sinh(k))
    d = (big_one + qk)
    j = (b - a)*qk/d
    w = qk*cosh(k)/d^(2*big_one)
    approx += (f(a + j) + f(b - j))*w
  end
  return approx*big_one*2*h*(b - a)
end

function sinh_tanh(f, a::BigFloat, b::BigFloat, lim::BigFloat; n = 12)
  big_one = one(BigFloat)
  h = (big_one/2)^n
  approx = f((a + b)*big_one/2)*big_one/4
  sup = asinh(-log(lim)/2)

  for k = h:h:sup
    qk = exp(-big_one*2*sinh(k))
    d = (big_one + qk)
    j = (b - a)*qk/d
    w = qk*cosh(k)/d^(big_one*2)
    approx += (f(a + j) + f(b - j))*w
  end
  return approx*big_one*2*h*(b - a)
end