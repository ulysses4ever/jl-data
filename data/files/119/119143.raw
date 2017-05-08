using Dolfin

import Dolfin:dot, Function, det
import PyCall: PyDict

mesh = UnitSquareMesh(32, 32)

# Define function spaces and mixed (product) space
DRT = FunctionSpace(mesh, "DRT", 2)
CG  = FunctionSpace(mesh, "CG", 3)
W = DRT * CG

# Define trial and test functions
(sigma, u) = TrialFunctions(W)
(tau, v) = TestFunctions(W)

# Define source functions
f = Expression("10*exp(-(pow(x[0] - 0.5, 2) + pow(x[1] - 0.5, 2)) / 0.02)")
g = Expression("sin(5.0*x[0])")

# Define variational form
a = (dot(sigma, tau) + dot(grad(u), tau) + dot(sigma, grad(v)))*dx
L = - f*v*dx - g*v*ds

bc = DirichletBC(W[:sub](1), 0.0, "x[0] < DOLFIN_EPS || x[0] > 1.0 - DOLFIN_EPS")

# Compute solution
w = Function(W)
solve(a==L, w, bc)
(sigma, u) = w["split"]()

plot(sigma, interactive=true)
