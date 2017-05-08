# TODO: it would be cool to have a macro so that I could do
# @funclist [:1, :x, :x^2]
# and have it make the list of anon functions

x = [0.0, 1.0, 3.0, 5.0]
y = [1.0, 0.0, 2.0, 4.0]

lsfit([(x)->1, (x)->x], x, y)
linreg(x, y)

ffit([(x)->1, (x)->x, (x)->x^2], x, y)

x = [-π, -π/2.0, 0, π/2, π]
y = [4.0, 0.0, 1.0, -1.0, -4.0]
lsfit([(x)->sin(x/2), (x)->sin(x), (x)->sin(2*x)], x, y)


v = [5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5.0]
x = 1:length(v)
lsfit([(x)->1,(x)->x,(x)->x^2], x, v)
lsfit([(x)->1,(x)->x,(x)->x^2,(x)->x^3,(x)->x^4], x, v)
