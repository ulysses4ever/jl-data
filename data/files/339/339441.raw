using LeastSquares
using PyPlot

# so I need to check the arg list better
badlst = push!([], [1, 2, 3])
tmp = @funclist x badlst
tmp[1](5)

tex = :(hcat([1, 2, 3], [5, 6, 7]))

# so I need to check the arg list better, how do I make sure these are simple functions...
tmp = @funclist x hcat([1, 2, 3], [5, 6, 7])
tmp[1](5)

test = @funclist x [1, 5 + 2*sin(x)]
test[2](6)

test = @funclist x [1, 2*x]
test[1](5)

x = [0.0, 1.0, 3.0, 5.0]
y = [1.0, 0.0, 2.0, 4.0]

feq = lsfit(@funclist(x, [1, x]), x, y)
feq(5)
feq.coef
linreg(x, y)
plot(x, y, "o")
plot(x, map(feq, xi))

feq = lsfit(@funclist(x, [1, x, x^2]), x, y)
feq(5)

x = [-π, -π/2.0, 0, π/2, π]
y = [4.0, 0.0, 1.0, -1.0, -4.0]
feq = lsfit(@funclist(x, [sin(x/2), sin(x), sin(2*x)]), x, y)
feq(5)
plot(x, y, "o")
xi = linspace(-2π, 2π, 100)
plot(xi, map(feq, fx))

v = Float64[5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5]
size(v)
x = 1:length(v)
size(x)
quad = lsfit(@funclist(x, [1, x, x^2]), x, v)
quart = lsfit(@funclist(x, [1, x, x^2, x^3, x^4]), x, v)
plot(x, v, "o")
xvals = linspace(1, length(v), 100)
plot(xvals, map(quad, xvals))
plot(xvals, map(quart, xvals))
