# This is just a place to test the code from Optimization
using Convex
Pkg.update()
Pkg.add("Convex")
Pkg.add("SCS")
Pkg.update()
using Convex
using SCS
m=100; n=30;
A=10*randn(m,n)
b=randn(m,1)

x = Variable(n)

# Minimizing Least Squares
sum_squares(A*x-b)
minimize(sum_squares(A * x - b),[x>=0])
prob = minimize(sum_squares(A*x-b)+)

solve!(prob)

prob.status
prob.optval
W =DataFrame(X=1:4,Y=rand(4))
W("X")
Pkg.add("PyPlot")
using PyPlot
pygui(false)
x = linspace(0,2*pi,1000); y = sin(3*x + 4*cos(2*x))
PyPlot.pygui(true)
q=PyPlot.plot(x, y, color="red", linewidth=2.0, linestyle="--")
plt.show() # Atom
using Gadfly
using DataArrays, DataFrames
DataFrame(X=x.value)
x.value
Gadfly.plot(x=x.value, Geom.histogram,W,Geom.density)
x.value
