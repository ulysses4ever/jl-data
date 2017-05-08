module QuadProg

using Compat

function solve (G::Matrix, g::Vector, A::Matrix, Delta::Float64;
    null_matrix = false, ortho_null = false, eps = 1e-8, kmax = 1000)
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

  u = zeros(n);
  r = -Z'*g
  t = (ortho_null ? r : C'\(C\r))
  p = Z*t
  theta0 = dot(r,t);
  theta = 2*theta0
  k = 0
  while k < kmax
    if dot(p, G*p) <= 1e-8*dot(p,p)
      disc = sqrt(dot(u,p) - dot(p,p)*(dot(u,u)-Delta));
      tau1 = (-dot(u,p)+disc)/dot(p,p);
      tau2 = (-dot(u,p)-disc)/dot(p,p);
      if q(u + tau1*p) < q(u + tau2*p)
        u = u + tau1*p
      else
        u = u + tau2*p
      end
      break
    end
    alpha = dot(r,t)/dot(p, G*p)
    unew = u + alpha*p
    if norm(unew) > Delta
      disc = sqrt(dot(u,p) - dot(p,p)*(dot(u,u)-Delta));
      tau1 = (-dot(u,p)+disc)/dot(p,p);
      tau2 = (-dot(u,p)-disc)/dot(p,p);
      tau = (tau1 > 0 ? tau1 : tau2)
      u = u + tau*p
      break
    end
    u = unew
    r = r - alpha*Z'*G*p
    t = (ortho_null ? r : C'\(C\r))
    thetanew = dot(t,r)
    if thetanew < eps^2*theta0
      break
    end
    beta = thetanew/theta
    theta = thetanew
    p = Z*t + beta*p
    k += 1
  end
  return u, q(u), k
end

end
