using Dolfin
using Base.Test

import Dolfin:dot, Function
import PyCall: PyDict
# mesh = UnitSquareMesh(32, 32)
#
# # Define function spaces and mixed (product) space
# DRT = FunctionSpace(mesh, "DRT", 2)
# CG  = FunctionSpace(mesh, "CG", 3)
# W = DRT * CG
#
# # Define trial and test functions
# (sigma, u) = TrialFunctions(W)
# (tau, v) = TestFunctions(W)
#
# # Define source functions
# f = Expression("10*exp(-(pow(x[0] - 0.5, 2) + pow(x[1] - 0.5, 2)) / 0.02)")
# g = Expression("sin(5.0*x[0])")
#
# # Define variational form
# a = (dot(sigma, tau) + dot(grad(u), tau) + dot(sigma, grad(v)))*dx
# L = - f*v*dx - g*v*ds
#
# bc = DirichletBC(W[:sub](1), 0.0, "x[0] < DOLFIN_EPS || x[0] > 1.0 - DOLFIN_EPS")
#
#
# # Compute solution
# w = Function(W)
# solve(isequal(a, L), w, bc)
# (sigma, u) = w["split"]()
#
# plot(sigma, interactive=true)

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
solver_parameters=PyDict()
solver_parameters["linear_solver"]="lu"
solve(a==L, u, bc, solver_parameters=solver_parameters)
# Solve equation a = L with respect to u and the given boundary
# conditions, such that the estimated error (measured in M) is less
# than tol
plot(u, interactive=true)

