export gauss_legendre
export gauss_lobatto

function gauss_legendre(f, a, b, n)
  (F, W) = gausslegendre(n)
  h = b - a
  for i = 1 : n
    F[i] = f((a + b + h*F[i])/2)
  end
  return (F'*W)[1]*h/2
end

function gauss_lobatto(f, a, b, n)
  (F, W) = gausslobatto(n)
  h = b - a
  for i = 1 : n
    F[i] = f((a + b + h*F[i])/2)
  end
  return (F'*W)[1]*h/2
end

