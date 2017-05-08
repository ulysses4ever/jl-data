export gauss_legendre
export gauss_lobatto

function gauss_legendre(f::Function, a, b; n::Int = 16)
  (F, W) = gausslegendre(n)
  const h = b - a
  for i = 1 : n
    F[i] = f((a + b + h*F[i])/2)
  end
  return (F'*W)[1]*h/2
end

function gauss_lobatto(f::Function, a, b; n::Int = 16)
  (F, W) = gausslobatto(n)
  const h = b - a
  for i = 1 : n
    F[i] = f((a + b + h*F[i])/2)
  end
  return (F'*W)[1]*h/2
end