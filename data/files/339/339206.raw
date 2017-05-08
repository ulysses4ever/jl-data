using OpenSCADPolyhedron
using OpenSCADCube

function generateBaseFace (d::Float64)
  return [
    # four base points
    Point3{Float64}([ 1.0,  1.0, -1.0]),
    Point3{Float64}([-1.0,  1.0, -1.0]),
    Point3{Float64}([-1.0, -1.0, -1.0]),
    Point3{Float64}([ 1.0, -1.0, -1.0]),
    # base points taken in by d
    Point3{Float64}([ 1.0 - d,  1.0 - d, -1.0]),
    Point3{Float64}([-1.0 + d,  1.0 - d, -1.0]),
    Point3{Float64}([-1.0 + d, -1.0 + d, -1.0]),
    Point3{Float64}([ 1.0 - d, -1.0 + d, -1.0]),
    # now taken up by d as well
    Point3{Float64}([ 1.0 - d,  1.0 - d, -1.0 + d]),
    Point3{Float64}([-1.0 + d,  1.0 - d, -1.0 + d]),
    Point3{Float64}([-1.0 + d, -1.0 + d, -1.0 + d]),
    Point3{Float64}([ 1.0 - d, -1.0 + d, -1.0 + d]),
  ]
end

cubeFrameBase = Polyhedron{Float64}(generateBaseFace(0.2))
# bottom faces
append!(cubeFrameBase, Int[1, 2, 6, 5])
append!(cubeFrameBase, Int[2, 3, 7, 6])
append!(cubeFrameBase, Int[3, 4, 8, 7])
append!(cubeFrameBase, Int[4, 1, 5, 8])
# inside faces
append!(cubeFrameBase, Int[10, 9, 5, 6])
append!(cubeFrameBase, Int[11, 10, 6, 7])
append!(cubeFrameBase, Int[12, 11, 7, 8])
append!(cubeFrameBase, Int[9, 12, 8, 5])

# These are the points that need symmetry relations.
# Note that they must be specified in the order that lines them up with cubeFace
cubeFrameLayers = Set{Array{Int,1}}()
push!(cubeFrameLayers, Int[1, 2, 3, 4])
push!(cubeFrameLayers, Int[9, 10, 11, 12])

# Here are our symmetries, generated from the basic cube symmetries
cubeFrameSymmetries = expandSymmetries(cubeSymmetries, cubeFace, cubeFrameLayers)

cube = generatePolyhedron(cubeFrameBase, cubeTransforms, cubeFrameSymmetries)
println(stringify(cube))

