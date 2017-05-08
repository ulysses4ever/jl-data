export gaussian_quadrature

function gaussian_quadrature(f, a, b, n)
  x(t) = (a + b + t*(b-a))/2
  t = sqrt(3)/3
  approx = (f(x(t)) + f(x(-t)))*(b - a)/2
  return approx
end