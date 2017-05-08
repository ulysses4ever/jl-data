module NewtonISMP

function solve(f, g, H, x0; eps=1e-6, kmax=1000, alpha=0.5, neg_thresh=1e-12)
  x = copy(x0);
  k = 0;
  while norm(g(x)) > eps
    d = -H(x)\g(x);
    # Negative curvature or near singular
    if -dot(g(x),d) < neg_thresh*dot(g(x),g(x))
      return 1, x, f(x), g(x), k
    end
    # Line search
    t = 1.0
    while f(x+t*d) >= f(x) + alpha*t*dot(g(x),d)
      t *= 0.9;
      if t < Base.eps()
        return 3, x, f(x), g(x), k
      end
    end
    x += t*d;
    k += 1
    if k >= kmax
      return 2, x, f(x), g(x), k;
    end
  end
  return 0, x, f(x), g(x), k;
end

end
