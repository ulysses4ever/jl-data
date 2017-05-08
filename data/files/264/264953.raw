using NewtonISMP
using Base.Test

b = 100
f(x) = (1-x[1])^2 + b*(x[2]-x[1]^2)^2;
g(x) = [2*x[1]-2+4*b*x[1]^3-4*b*x[1]*x[2]; 2*b*(x[2]-x[1]^2)];
H(x) = [12*b*x[1]^2-4*b*x[2]+2 -4*b*x[1]; -4*b*x[1] 2*b]

sol = [1.0;1.0]
x0 = [-3.0;-4.0];

(exitflag, x, fx, gx, k) = NewtonISMP.solve(f, g, H, x0)

println("k = ", k)

@test exitflag == 0
@test_approx_eq_eps x sol 1e-6
@test_approx_eq_eps f(x) f(sol) 1e-6
@test norm(gx) < 1e-6
