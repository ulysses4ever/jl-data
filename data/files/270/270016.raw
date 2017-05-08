function gencond( kappa, m, n )
  A = randn(m,n)
  (U,S,V) = svd(A)
  S = logspace(0, -log10(kappa), n)
  return U*diagm(S)*V'
end
