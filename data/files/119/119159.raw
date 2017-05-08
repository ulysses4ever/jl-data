using Dolfin
using Base.Test

import Dolfin:dot, Function
import PyCall: PyDict

mesh = UnitSquareMesh(80, 80)
V = FunctionSpace(mesh, "Lagrange", 1)

# Define boundary condition
u0 =  Function(V)
bc =  DirichletBC(V, u0, "x[0] < DOLFIN_EPS || x[0] > 1.0 - DOLFIN_EPS")

# Define variational problem
u =  TrialFunction(V)
v =  TestFunction(V)
f =  Expression("10*exp(-(pow(x[0] - 0.5, 2) + pow(x[1] - 0.5, 2)) / 0.02)",
               degree=1)
g = Expression("sin(5*x[0])", degree=1)
a = inner(grad(u), grad(v))*dx
L = f*v*dx+ g*v*ds
# Define function for the solution
u = Function(V)
# Define error tolerance

# create a PyObject for parameters
solver_parameters=PyDict()

solver_parameters["linear_solver"]="lu"
solve(a==L, u, bc, solver_parameters=solver_parameters)
# Solve equation a = L with respect to u and the given boundary
# conditions, such that the estimated error (measured in M) is less
# than tol
plot(u, interactive=true)
