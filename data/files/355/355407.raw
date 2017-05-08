export gaussian_quadrature

function gaussian_quadrature(f, a, b; n = 10)
  h = (b-a)/n
  atemp = a
  btemp = a + h
  approx = 0.0
  x1(atemp, btemp) = (atemp + btemp + sqrt(3)*h/3)/2
  x2(atemp, btemp) = (atemp + btemp - sqrt(3)*h/3)/2

  for k = 1:1:n
    approx += (f(x1(atemp, btemp)) + f(x2(atemp, btemp)))
    atemp+=h; btemp+=h;
  end

  return approx*h/2
end