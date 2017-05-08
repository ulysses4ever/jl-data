# This is just a place to test the code from Optimization
using Convex
Pkg.add("ECOS")
Pkg.update()
Pkg.add("Convex")
Pkg.add("SCS")
Pkg.update()
using Convex
using SCS
m=100; n=30;
A=10*randn(m,n)
b=randn(m,1)

x1 = Variable(n)
x2 = Variable(n)
xDead = Variable(n)
xLog = Variable(n)
λ=.5

# Minimizing Least Squares with various penalties
prob1 = minimize(sum_squares(A*x1-b)+λ*norm(x1,1))
prob2 = minimize(sum_squares(A*x2-b)+λ*norm(x2,2))
probDead = minimize(sum_squares(A*xDead-b)+λ*max(norm(xDead,1)-.5,0))
probLog = minimize(sum_squares(A*xLog-b)-λ*(sum(log(xLog+1)+log(1-xLog))))

solve!(prob1)
solve!(prob2)
solve!(probDead)
solve!(probLog)
prob1.status
prob2.status
probDead.status
probLog.status
using PyPlot

PyPlot.hist(x1.value); PyPlot.show()
plt.hist(x1.value,50)
plt
plt[:hist](x1.value,20)
PyPlot.show()
display(gcf())
pygui(true)
PyPlot.hist2D(x1.value,50);
PyPlot.show()
mu, sigma = 200, 25
x = mu + sigma*PyPlot.randn(10000)

# the histogram of the data with histtype='step'
[n, bins, patches] = plt[:hist](x, 50, "normed=1", "histtype='stepfilled'")
P.setp(patches, 'facecolor', 'g', 'alpha', 0.75)

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
