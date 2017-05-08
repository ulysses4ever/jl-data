include("../src/Dolfin.jl")

using Dolfin

import Dolfin:dot, Function, det
import PyCall: PyDict

parameters["form_compiler"]["cpp_optimize"] = true

ffc_options = PyDict()
ffc_options["optimize"]= true
ffc_options["eliminate_zeros"]= true
ffc_options["precompute_basis_const"]= true
ffc_options["precompute_ip_const"]=true

# Create mesh and define function space
mesh = UnitCubeMesh(24, 16, 16)
V = VectorFunctionSpace(mesh, "Lagrange", 1)

# Mark boundary subdomians
left =  CompiledSubDomain("near(x[0], side) && on_boundary", side = 0.0)
right = CompiledSubDomain("near(x[0], side) && on_boundary", side = 1.0)

# Define Dirichlet boundary (x = 0 or x = 1)
c = Expression(("0.0", "0.0", "0.0"))
r = Expression(("scale*0.0",
                "scale*(y0 + (x[1] - y0)*cos(theta) - (x[2] - z0)*sin(theta) - x[1])",
                "scale*(z0 + (x[1] - y0)*sin(theta) + (x[2] - z0)*cos(theta) - x[2])"),
                scale = 0.5, y0 = 0.5, z0 = 0.5, theta = pi/3)

bcl = DirichletBC(V, c, left)
bcr = DirichletBC(V, r, right)
bcs = [bcl, bcr]

# Define functions
du = TrialFunction(V)            # Incremental displacement
v  = TestFunction(V)             # Test function
u  = Function(V)                 # Displacement from previous iteration
B  = Constant((0.0, -0.5, 0.0))  # Body force per unit volume
T  = Constant((0.1,  0.0, 0.0))  # Traction force on the boundary

# Kinematics
d = u["geometric_dimension"]()
I = Identity(d)             # Identity tensor
F = I + grad(u)             # Deformation gradient
C = F["T"]*F                   # Right Cauchy-Green tensor

# Invariants of deformation tensors
Ic = tr(C)
J  = det(F)

# Elasticity parameters
E, nu = 10.0, 0.3
mu, lmbda = Constant(E/(2*(1 + nu))), Constant(E*nu/((1 + nu)*(1 - 2*nu)))

# Stored strain energy density (compressible neo-Hookean model)
# change ** to ^
psi = (mu/Constant(2))*(Ic - Constant(3)) - mu*ln(J) + (lmbda/Constant(2))*(ln(J)) * (ln(J))

# Total potential energy
Pi = psi*dx - dot(B, u)*dx - dot(T, u)*ds

# Compute first variation of Pi (directional derivative about u in the direction of v)
F = derivative(Pi, u, v)

# Compute Jacobian of F
J = derivative(F, u, du)

# Solve variational problem
solve(F == Constant(0), u, bcs, J=J, form_compiler_parameters=ffc_options)

# Save solution in VTK format
# file = File("displacement.pvd");
# file << u;

# Plot and hold solution
plot(u, mode = "displacement", interactive = true)
