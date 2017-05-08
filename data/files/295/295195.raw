export zero_to_inf
export double_inf
export simpsons_rule_inf
export mid_point
export clenshaw_rule
export clenshaw_rule2

function zero_to_inf(f; n = 10)
  h = 1/2^n
  x(k) = exp(pi*sinh(k))
  w(k) = x(k)*pi*cosh(k)
  approx = 0
  for k = -4.8:h:4.8
    f1 = f(x(k))*w(k)
    f2 = f(x(k + 1))*w(k + 1)
    approx += f1 + f2
  end
  return approx*h/2
end

function double_inf(f; n = 10)
  approx = 0; h = 1/2^n
  x(k) = sinh(pi*sinh(k)/2)
  w(k) = cosh(pi*sinh(k)/2)*pi*cosh(k)/2

  for k = -4.5:h:4.5
    approx += (f(x(k))*w(k) + f(x(k + 1))*w(k + 1))*h/2
  end
  return approx
end

function simpsons_rule_inf(f, a, b; n = 200)
  if a != 0
    return simpsons_rule(t->f(1/t)/t^2, 1/b, 1/a, n = n)
  else
    approx = simpsons_rule(f, 0, 1, n = n) + simpsons_rule(t->f(1/t)/t^2, 1/b, 1, n = n)
  end
end

function mid_point(f, a, b; n = 500)
  h = (b - a)/n
  approx = f(a + h/2)
  for i = 1 : n - 1
    approx += f(a + h/2 + i*h)
  end
  return h*approx
end

function clenshaw_rule(f, a, b, n)
  V = fill(1.0, n, n)
  F = Float64[]; W = fill(1.0, n)
  h = b - a; M = pi/(n - 1)

  for i = 1 : n
    if i != 1
      i % 2 != 0 ? W[i] = 2/(1 - (i - 1)^2) : W[i] = 0
      for j = 2 : n
        V[i, j] = cos((j - 1)*(i - 1)*M)
      end
    end
    V[i, n] *= 0.5
    V[i, 1] = 0.5
   push!(F, f((a + b + cos((i - 1)*M)*h)/2))
  end
  return (W'*(V*F))[1]*h/(n - 1)
end

function clenshaw_rule2(f, a, b, n)
  h = b - a; N = n - 1; M = pi/N
  x = (a + b + h.*cos((0:N)*M))./2
  F = map(f, x); W = x*0
  W[1:2:end] = 1./(1 - (0:2:N).^2)
  F = real(fft([F[1 : n]; F[n - 1 : -1 : 2]]))
  F = [F[1]; F[2 : N] + F[2N : -1 : n + 1]; F[n]]
  return (W'*F)[1]*h/2N
end