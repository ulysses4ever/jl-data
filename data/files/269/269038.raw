module QuadProg

using Compat

function solve(G::Matrix, g::Vector, A::Matrix, Δ::Float64;
    null_matrix = false, ortho_null = false, eps = 1e-8, kmax = 1000,
    verbose = false)
  if null_matrix
    Z = A;
    n = length(g);
    m = n-size(Z,2);
    C = chol(Z'*Z);
  else
    (m,n) = size(A);
    (Q,R) = qr(A', thin=false);
    Z = Q[:,m+1:n];
    ortho_null = true;
  end
  q(d) = 0.5*dot(d, G*d) + dot(g,d);

  verbose && println("Δ = $Δ")
  u = zeros(n);
  r = -Z'*g
  t = (ortho_null ? r : C'\(C\r))
  p = Z*t
  theta0 = dot(r,t);
  if theta0 < eps*eps
    return u, q(u), 0
  end
  theta = theta0
  k = 1
  verbose && println("‖u_$k‖ = $(norm(u))")
  verbose && println("q(u_$k) = $(q(u))")
  while k < kmax
    if dot(p, G*p) <= 1e-8*dot(p,p)
      disc = sqrt(dot(u,p)^2 - dot(p,p)*(dot(u,u)-Δ^2));
      tau1 = (-dot(u,p)+disc)/dot(p,p);
      tau2 = (-dot(u,p)-disc)/dot(p,p);
      if q(u + tau1*p) < q(u + tau2*p)
        u = u + tau1*p
      else
        u = u + tau2*p
      end
      verbose && println("Negative curvature")
      break
    end
    α = dot(r,t)/dot(p, G*p)
    unew = u + α*p
    verbose && println("α = $α")
    if norm(unew) > Δ
      disc = sqrt(dot(u,p)^2 - dot(p,p)*(dot(u,u)-Δ^2));
      τ = (-dot(u,p)+disc)/dot(p,p);
      u = u + τ*p
      verbose && println("τ = $τ")
      verbose && println("Outside region")
      break
    end
    u = unew
    r = r - α*Z'*G*p
    t = (ortho_null ? r : C'\(C\r))
    verbose && println("t'r = $(dot(t,r))")
    thetanew = dot(t,r)
    if thetanew < eps^2*theta0
      verbose && println("Optimal")
      break
    end
    beta = thetanew/theta
    theta = thetanew
    p = Z*t + beta*p
    verbose && println("‖u_$k‖ = $(norm(u))")
    verbose && println("q(u_$k) = $(q(u))")
    k += 1
  end
  verbose && println("‖u‖ = $(norm(u))")
  verbose && println("q(u) = $(q(u))")
  return u, q(u), k
end

end
