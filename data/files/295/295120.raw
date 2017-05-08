export gaussian_quadrature

function gaussian_quadrature(f, a, b, Nf)
  h = (b-a)/(Nf-1)
  atemp = 0.0
  btemp = h

  for h:h:b
    x1 = (a + b + sqrt(3)/3*(btemp-atemp))/2
    x2 = (a + b - sqrt(3)/3*(btemp-atemp))/2
    approx = (f(x1) + f(x2))(btemp - atemp)/2
    atemp+=h; btemp+=h;
  end

  return approx
end