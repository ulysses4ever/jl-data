# This is just a place to test the code from Optimization
using Convex.jl
Pkg.update()
Pkg.add("Convex")

using Convex
m=100; n=30;
A=10*randn(m,n)
b=randn(m,1)

x = Variable(n)

# Minimizing Least Squares
prob = minimize(sum_squares(A*x-b), [x>=0])

solve!(prob)

prob.status