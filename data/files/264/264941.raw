using NewtonISMP
using Base.Test

for n = 10:10:100
  f(x) = sum(x.^4);
  g(x) = 4*x.^3;
  H(x) = 12*diagm(x.^2);

  x0 = ones(n);

  (exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0; kmax=5);

  @test exitflag == 2
end
