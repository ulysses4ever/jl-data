using NewtonISMP
using Base.Test

for n = [10:10:100;100:100:1000]
  c = randn();
  p = randn(n);
  G = randn(n,n);
  G = -G'*G-eye(n);
  f(x) = c+dot(p,x)+0.5*dot(x,G*x);
  g(x) = G*x+p;
  H(x) = G;

  x0 = zeros(n);

  (exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0)

  @test exitflag == 1
end
