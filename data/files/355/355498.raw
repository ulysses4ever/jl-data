export sinh_tanh

function sinh_tanh(f, a, b, n)
  s = 2.0^n
  h = 4.5/2^n
  q(k) = e^(-2*sinh(k*h))
  subs(k) = (b-a)*q(k)/(1+q(k))
  g(t) = 2*(b - a)*t
  w_k(k) = h*q(k)*cosh(k*h)/(1+q(k))^2
  x_k(k) = tanh(sinh(k*h))

  approx = f((a+b)/2)*g(w_k(0))

  for k = 1:s
    j = subs(k)
    if j < 1e-16
      j = 1e-16
    end
    approx += f(a + j)*g(w_k(k)) + f(b - j)*g(w_k(k))
  end
return approx
end
