using CVX

m = 20
x = CVX.Var(m, "x")
A = randn(m, m)
b = randn(m, 1)
objective = CVX.square(CVX.norm(A * x .- b))
p = CVX.Problem(objective)
