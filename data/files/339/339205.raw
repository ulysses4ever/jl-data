using OpenSCADPolyhedron
using OpenSCADIcosahedron

xscale = 1.15470053838
hscale = 1.51152262815
l1 = .3 # length toward center of triangle in plane from edge
l2 = .1 # overlap length of plexiglass over outer support (must be less than l1)
h = .3  # total height of inner rib
d = .15  # thickness of outer support (so depth of plexiglass traingles behind outer faces)
alpha = 1.2059325 # = half the dihedral angle of an icosahedron ~ 69 degrees


# FIGURE 1:
# Cross section parameters and points layout
#
#              l1
#    _____________________ 
# d |                    / |
#   |________           /  |
#      l2    |         /   | h
#            |________/    |

#=
icosahedronPoints = [
  Point3{Float64}([-1., -0.57735, 1.51152]),
  Point3{Float64}([ 0.,  1.1547,  1.51152]),
  Point3{Float64}([ 1., -0.57735, 1.51152]),
]
=#

# generates the points that define the triangle crosssection in the xz plane
# points are defined counter clockwise starting with top right point in Figure 1
xpoints = [
  Point3{Float64}([xscale,              0, hscale]),
  Point3{Float64}([xscale - 2l1,        0, hscale]),
  Point3{Float64}([xscale - 2l1,        0, hscale - d]),
  Point3{Float64}([xscale - 2(l1 - l2), 0, hscale - d]),
  Point3{Float64}([xscale - 2(l1 - l2), 0, hscale - h]),
  Point3{Float64}([xscale - 2*h/tan(alpha), 0, hscale - h]),
]
temppoly1 = Polyhedron{Float64}(xpoints)

strutTransforms = Function[
  p::Point3{Float64} -> p,
  p::Point3{Float64} -> Point3{Float64}([ -0.5 -0.866025403784 0.; 0.866025403784 -0.5 0.; 0. 0. 1.] * p.x),
]

triangleTransforms = Function[
  p::Point3{Float64} -> Point3{Float64}([ 0.866025403784  0.5  0.; -0.5  0.866025403784  0.; 0. 0. 1.] * p.x),
  p::Point3{Float64} -> Point3{Float64}([ 0.             -1.   0.;  1.   0.              0.; 0. 0. 1.] * p.x),
  p::Point3{Float64} -> Point3{Float64}([-0.866025403784  0.5  0.; -0.5 -0.866025403784  0.; 0. 0. 1.] * p.x),
]

temppoly2 = generatePolyhedron(temppoly1, strutTransforms, Dict{(Int, Int), (Int, Int)}())
append!(temppoly2, Int[1, 2, 8, 7])
append!(temppoly2, Int[2, 3, 9, 8])
append!(temppoly2, Int[3, 4, 10, 9])
append!(temppoly2, Int[4, 5, 11, 10])
append!(temppoly2, Int[5, 6, 12, 11])
#append!(temppoly2, Int[])
temppoly2symmetries = [
  (2,  1) => (1,  7),
  (2,  2) => (1,  8),
  (2,  3) => (1,  9),
  (2,  4) => (1, 10),
  (2,  5) => (1, 11),
  (2,  6) => (1, 12),
  (3,  7) => (1,  1),
  (3,  8) => (1,  2),
  (3,  9) => (1,  3),
  (3, 10) => (1,  4),
  (3, 11) => (1,  5),
  (3, 12) => (1,  6),
  (3,  1) => (2,  7),
  (3,  2) => (2,  8),
  (3,  3) => (2,  9),
  (3,  4) => (2, 10),
  (3,  5) => (2, 11),
  (3,  6) => (2, 12),
]

temppoly3 = generatePolyhedron(temppoly2, triangleTransforms, temppoly2symmetries)
#println(stringify(temppoly3))

layers = Set{Array{Int,1}}()
push!(layers, Int[13, 7, 1])
push!(layers, Int[18, 12, 6])

symmetries = expandSymmetries(icosahedronSymmetries, icosahedronFace, layers)
lampahedron = generatePolyhedron(temppoly3, icosahedronTransforms, symmetries) 

println(stringify(lampahedron))

