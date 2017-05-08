#==============================================================================#
# OpenSCADIcosahedron
# December 2014
#==============================================================================#

# This module uses OpenSCADPolyhedron to build an icosahedron.
# All points, transforms, and symmetries were derived in Mathematica.

#-------------------------------------------------------------------------------
module OpenSCADIcosahedron
using lampahedron
export icosahedronPoints, icosahedronBase, icosahedronTransforms, icosahedronSymmetries

#-------------------------------------------------------------------------------
# We start with the top face (our icosahedron will have its top and bottom faces
# parallel to the ground, to facilitate 3D printing).
icosahedronPoints = [
  Point3{Float64}([-1., -0.57735, 1.51152]),
  Point3{Float64}([ 0.,  1.1547,  1.51152]),
  Point3{Float64}([ 1., -0.57735, 1.51152]),
]
icosahedronBase = Polyhedron{Float64}(icosahedronPoints)
append!(icosahedronBase, Int[1, 2, 3])

icosahedronTransforms = Function[
  #Group 1 ("top 5")
  p::Point3{Float64} -> Point3{Float64}([ 1.        0.        0.;        0.        1.        0.;        0.        0.        1.      ] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.5      -0.645497 -0.57735;   0.866025  0.372678  0.333333;  0.       -0.666667  0.745356] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.309017 -0.178411 -0.934172;  0.755761 -0.64235  -0.127322; -0.57735  -0.745356  0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.309017  0.755761 -0.57735;  -0.178411 -0.64235  -0.745356; -0.934172 -0.127322  0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.5       0.866025  0.;       -0.645497  0.372678 -0.666667; -0.57735   0.333333  0.745356] * p.x),
  #Group 2 ("bottom 5")
  p::Point3{Float64} -> Point3{Float64}([ 1.        0.        0.;        0.       -1.        0.;        0.        0.       -1.      ] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.5       0.645497  0.57735;   0.866025 -0.372678 -0.333333;  0.        0.666667 -0.745356] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.309017  0.178411  0.934172;  0.755761  0.64235   0.127322; -0.57735   0.745356 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.309017 -0.755761  0.57735;  -0.178411  0.64235   0.745356; -0.934172  0.127322 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.5      -0.866025  0.;       -0.645497 -0.372678  0.666667; -0.57735  -0.333333 -0.745356] * p.x),
  #Group 4 ("downward pointing faces")
  p::Point3{Float64} -> Point3{Float64}([ 0.309017 -0.755761  0.57735;   0.755761  0.563661  0.333333; -0.57735   0.333333  0.745356] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.       -0.934172 -0.356822;  0.356822 -0.333333  0.872678; -0.934172 -0.127322  0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.309017 -0.178411 -0.934172; -0.178411 -0.975684  0.127322; -0.934172  0.127322 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.809017  0.467086 -0.356822; -0.110264 -0.475684 -0.872678; -0.57735   0.745356 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.809017  0.110264  0.57735;   0.467086  0.475684 -0.745356; -0.356822  0.872678  0.333333] * p.x),
  #Group 4 ("upward pointing faces")
  p::Point3{Float64} -> Point3{Float64}([-0.809017 -0.467086  0.356822;  0.467086 -0.14235   0.872678; -0.356822  0.872678  0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.5      -0.645497 -0.57735;  -0.645497 -0.166667  0.745356; -0.57735   0.745356 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.5      -0.645497 -0.57735;  -0.866025 -0.372678 -0.333333;  0.        0.666667 -0.745356] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.809017 -0.467086  0.356822;  0.110264 -0.475684 -0.872678;  0.57735   0.745356 -0.333333] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.       -0.356822  0.934172;  0.934172 -0.333333 -0.127322;  0.356822  0.872678  0.333333] * p.x),
]

icosahedronSymmetries = [
  (2,  1) => (1, 1),
  (2,  3) => (1, 2),
  (3,  1) => (1, 1),
  (3,  3) => (2, 2),
  (4,  1) => (1, 1),
  (4,  3) => (3, 2),
  (5,  1) => (1, 1),
  (5,  3) => (4, 2),
  (5,  2) => (1, 3),
  (7,  1) => (6, 2),
  (7,  3) => (6, 3),
  (8,  1) => (7, 2),
  (8,  3) => (6, 3),
  (9,  1) => (8, 2),
  (9,  3) => (6, 3),
  (10, 1) => (9, 2),
  (10, 3) => (6, 3),
  (10, 2) => (6, 1),
  (11, 1) => (8, 2),
  (11, 2) => (1, 2),
  (11, 3) => (9, 2),
  (12, 1) => (9, 2),
  (12, 2) => (2, 2),
  (12, 3) => (6, 1),
  (13, 1) => (6, 1),
  (13, 2) => (3, 2),
  (13, 3) => (6, 2),
  (14, 1) => (6, 2),
  (14, 2) => (4, 2),
  (14, 3) => (7, 2),
  (15, 1) => (7, 2),
  (15, 2) => (1, 3),
  (15, 3) => (8, 2),
  (16, 1) => (1, 3),
  (16, 2) => (1, 2),
  (16, 3) => (8, 2),
  (17, 1) => (1, 2),
  (17, 2) => (2, 2),
  (17, 3) => (9, 2),
  (18, 1) => (2, 2),
  (18, 2) => (3, 2),
  (18, 3) => (6, 1),
  (19, 1) => (3, 2),
  (19, 2) => (4, 2),
  (19, 3) => (6, 2),
  (20, 1) => (4, 2),
  (20, 2) => (1, 3),
  (20, 3) => (7, 2)
]

#-------------------------------------------------------------------------------
# Build the icosahedron polygon.
icosahedron = generatePolyhedron(icosahedronBase, icosahedronTransforms, icosahedronSymmetries)
println(stringify(icosahedron))


#-------------------------------------------------------------------------------
# Bonus: this base polyhedron and set of transforms can be used to generate an icosahedron
# of a different orientation. The transforms are slightly cleaner, but the resulting model
# only has one edge that touches the ground so cannot stand on its own without support.

icosahedronPoints2 = [
  Point3{Float64}([-1., 0.,      1.61803]),
  Point3{Float64}([ 0., 1.61803, 1.     ]),
  Point3{Float64}([ 1., 0.,      1.61803])
]
icosahedronBase2 = Polyhedron{Float64}(icosahedronPoints)
append!(icosahedronBase2, Int[1, 2, 3])

v1 = 0.309017
v2 = 0.809017
icosahedronTransforms2 = Function[
  # Group 1
  p::Point3{Float64} -> p,
  p::Point3{Float64} -> Point3{Float64}([ .5 -v2 -v1;  v2  v1  .5; -v1 -.5  v2] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-v1 -.5 -v2;  .5 -v2  v1; -v2 -v1  .5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-v1 0.5 -v2; -.5 -v2 -v1; -v2  v1  .5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ .5  v2 -v1; -v2  v1 -.5; -v1  .5  v2] * p.x),
  # Group 2
  p::Point3{Float64} -> Point3{Float64}([ 1.  0.  0.;  0. -1.  0.;  0.  0. -1.] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ .5  v2  v1;  v2 -v1 -.5; -v1  .5 -v2] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-v1  .5  v2;  .5  v2 -v1; -v2  v1 -.5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-v1 -.5  v2; -.5  v2  v1; -v2 -v1 -.5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ .5 -v2  v1; -v2 -v1  .5; -v1 -.5 -v2] * p.x),
  # Group 3
  p::Point3{Float64} -> Point3{Float64}([ v1 -.5  v2;  .5  v2  v1; -v2  v1  .5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0. -1.  0.;  0.  0.  1.; -1.  0.  0.] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ v1 -.5 -v2; -.5 -v2  v1; -v2  v1 -.5] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ v2  v1 -.5; -v1 -.5 -v2; -.5  v2 -v1] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ v2  v1  .5;  v1  .5 -v2; -.5  v2  v1] * p.x),
  # Group 4
  p::Point3{Float64} -> Point3{Float64}([-v2 -v1  .5;  v1  .5  v2; -.5  v2 -v1] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-.5 -v2 -v1; -v2  v1  .5; -v1  .5 -v2] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ .5 -v2 -v1; -v2 -v1 -.5;  v1  .5 -v2] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ v2 -v1  .5;  v1 -.5 -v2;  .5  v2 -v1] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.  0.  1.;  1.  0.  0.;  0.  1.  0.] * p.x)
]

end

