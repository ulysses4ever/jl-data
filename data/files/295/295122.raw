export gaussian_quadrature

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