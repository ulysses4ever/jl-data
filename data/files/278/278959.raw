#==============================================================================#
# OpenSCADCube
# December 2014
#==============================================================================#

# This module uses OpenSCADPolyhedron to build a cube.
# This application is simple enough that it could easily be done by hand, but
# it provides a good illustration of how the OpenSCADPolyhedron module is used.

#-------------------------------------------------------------------------------
module OpenSCADCube
using OpenSCADPolyhedron
export cubePoints, cubeFace, cubeBase, cubeTransforms, cubeSymmetries

#-------------------------------------------------------------------------------
# To start, we need the points and face of one square of a cube.
cubePoints = [
  Point3{Float64}([ 1.0,  1.0, -1.0]),
  Point3{Float64}([-1.0,  1.0, -1.0]),
  Point3{Float64}([-1.0, -1.0, -1.0]),
  Point3{Float64}([ 1.0, -1.0, -1.0]),
]
cubeBase = Polyhedron{Float64}(cubePoints)
cubeFace = Int[1, 2, 3, 4]
append!(cubeBase, cubeFace)

# These six transformations generate the six faces of a cube.
cubeTransforms = Function[
  p::Point3{Float64} -> p,
  p::Point3{Float64} -> Point3{Float64}(Float64[ 0  0 -1;  0  1  0;  1  0  0] * p.x),
  p::Point3{Float64} -> Point3{Float64}(Float64[ 1  0  0;  0  0 -1;  0  1  0] * p.x),
  p::Point3{Float64} -> Point3{Float64}(Float64[ 0  0  1;  0  1  0; -1  0  0] * p.x),
  p::Point3{Float64} -> Point3{Float64}(Float64[ 1  0  0;  0  0  1;  0 -1  0] * p.x),
  p::Point3{Float64} -> Point3{Float64}(Float64[ 1  0  0;  0 -1  0;  0  0 -1] * p.x),
]

# These relations specify which points are duplicated by the above transforms.
cubeSymmetries = Dict{(Int, Int), (Int, Int)}()
cubeSymmetries[(2, 2)] = (1, 1)
cubeSymmetries[(2, 3)] = (1, 4)
cubeSymmetries[(3, 1)] = (2, 1)
cubeSymmetries[(3, 3)] = (1, 2)
cubeSymmetries[(3, 4)] = (1, 1)
cubeSymmetries[(4, 1)] = (1, 2)
cubeSymmetries[(4, 2)] = (3, 2)
cubeSymmetries[(4, 4)] = (1, 3)
cubeSymmetries[(5, 1)] = (1, 4)
cubeSymmetries[(5, 2)] = (1, 3)
cubeSymmetries[(5, 3)] = (4, 3)
cubeSymmetries[(5, 4)] = (2, 4)
cubeSymmetries[(6, 1)] = (2, 4)
cubeSymmetries[(6, 2)] = (4, 3)
cubeSymmetries[(6, 3)] = (3, 2)
cubeSymmetries[(6, 4)] = (2, 1)

#-------------------------------------------------------------------------------
# Now we generate the OpenSCAD polyhedron command for the cube.
cube = generatePolyhedron(cubeBase, cubeTransforms, cubeSymmetries)
println(stringify(cube))

end

