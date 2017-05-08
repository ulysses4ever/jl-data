println("Reloading Modules...")
include("sem.jl")

println("Reading mesh...")
msh = Nektar.nektar("meshes/circle.rea")

println("Creating Basis...")
Q = 15
b = sem.Basis2d(Q)


println("Creating Elements...")
elems = [sem.Element2d(b, el, msh.curves) for el in msh.elems];

Nel = length(elems)
x = sem.new_var(Q, Nel)
y = sem.new_var(Q, Nel)

for e = 1:Nel
    x[:,:,e] = elems[e].x
    y[:,:,e] = elems[e].y
end

fun(x,y) = 1 .+ x.*x .+ y.*y/2 .+ x.*y

dfdx(x,y) = 2x .+ y
dfdy(x,y) = y .+ x


f = fun(x, y)
dx = dfdx(x, y)
dy = dfdy(x,y)
ws = zeros(Q,Q)
dxc = similar(f)
dyc = similar(f)
sem.deriv_x!(elems, f, dxc);
sem.deriv_y!(elems, f, dyc);






