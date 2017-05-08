reload("gencond.jl")

function genba( kappa, m, n, kind )
  kappa = log10(kappa)
  sqrt_kappa = sqrt(kappa)
  V = qr(randn(m,m))[1]
  D = logspace(0, -kappa, m)
  B = scale(V, D)*V'
  W = qr(randn(n,n))[1]
  if kind == 1
    A = scale(V[:,m-n+1:m], logspace(0,-sqrt_kappa,n))*W'
  elseif kind == 2
    A = scale(V[:,1:n], logspace(0,-sqrt_kappa,n))*W'
  elseif kind == 3
    A = scale([V[:,m-cld(n,2)+1:m] V[:,1:fld(n,2)]],logspace(0,-sqrt_kappa,n))*W'
  elseif kind == 4
    A = gencond(10^sqrt_kappa, m, n)
  else
    U = [V[:,m-cld(n,2)+1:m] V[:,1:fld(n,2)]]
    S = [D[m-cld(n,2)+1:m]; D[1:fld(n,2)]]
    A = scale(U,1./sqrt(S))*W'
  end
  return sparse(triu(B)),A
end
