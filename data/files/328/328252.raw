using NewtonISMP
using Base.Test

for n = [10:10:100;100:100:1000]
  c = randn();
  p = randn(n);
  G = randn(n,n);
  G = G'*G+eye(n);
  f(x) = c+dot(p,x)+0.5*dot(x,G*x);
  g(x) = G*x+p;
  H(x) = G;

  sol = -G\p;
  x0 = zeros(n);

  (exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0)

  @test exitflag == 0
  @test_approx_eq_eps x sol 1e-4
  @test_approx_eq_eps f(x) f(sol) 1e-4
  @test norm(gx) < 1e-6
end
