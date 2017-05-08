using LeastSquares

test = @funclist :x [1, 2*:x]
test(5)

x = [0.0, 1.0, 3.0, 5.0]
y = [1.0, 0.0, 2.0, 4.0]

feq = lsfit([(x)->1, (x)->x], x, y)
feq(5)
feq.coef
linreg(x, y)
plot(x, y, "o")
plot(x, [feq(xi) for xi in x])

feq = lsfit([(x)->1, (x)->x, (x)->x^2], x, y)
feq(5)

x = [-π, -π/2.0, 0, π/2, π]
y = [4.0, 0.0, 1.0, -1.0, -4.0]
feq = lsfit([(x)->sin(x/2), (x)->sin(x), (x)->sin(2*x)], x, y)
feq(5)
plot(x, y, "o")
fx = linspace(-2π, 2π, 100)
fy = map(feq, fx)
plot(fx, fy)

v = [5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5.0]
x = 1:length(v)
lsfit([(x)->1,(x)->x,(x)->x^2], x, v)
lsfit([(x)->1,(x)->x,(x)->x^2,(x)->x^3,(x)->x^4], x, v)
