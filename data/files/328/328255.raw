using NewtonISMP
using Base.Test

for n = 10:10:100
  f(x) = dot(x,x);
  g(x) = ones(n)*(dot(x,x)+1);
  H(x) = eye(n);

  x0 = ones(n);

  (exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0);

  @test exitflag == 3
end
