module NewtonISMP

function solve(f, g, H, x0)
  x = copy(x0);
  k = 0;
  while norm(g(x)) > 1e-6
    d = -H(x)\g(x);
    # Line search
    t = 1.0
    while f(x+t*d) >= f(x)+0.5*t*dot(g(x),d)
      t *= 0.9;
    end
    x += t*d;
    k += 1
  end
  return 0, x, f(x), g(x), k;
end

end
