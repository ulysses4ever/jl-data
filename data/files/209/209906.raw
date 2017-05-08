using CVX

X = CVX.Var(2,2,"X")
CVX.curvature(CVX.square(X))

x = CVX.Var(1,1,"x")
f = CVX.sqrt(CVX.square(x) + 1)
CVX.curvature(f)

g = CVX.sqrt(CVX.sqrt(x) + 1)
CVX.curvature(g)

x = CVX.Var(20,1,"x")
CVX.curvature(2*x)
