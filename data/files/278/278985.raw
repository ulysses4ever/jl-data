#==============================================================================#
# OpenSCADPolyhedron.jl
# December 2014
#==============================================================================#

# This module helps generate complex polyhedron commands for OpenSCAD.
# The key function is generatePolyhedron, which takes an initial set of points
# and faces, a set of transformations, and a dictionary of symmetries. All the
# transforms are applied to the initial base polyhedron, resulting in a new set
# of points and faces. The symmetry dictionary is used to eradicate duplicate
# points, so that the resulting polyhedron can be described as simply as
# possible.

# Background
# The polyhedron command in OpenSCAD looks like this:
# polyhedron(points = [[-1.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]],
#         faces = [[0, 1, 2], [0, 3, 1], [0, 2, 3], [1, 3, 2]])
# Note that the faces must be specified clocwise, when viewing the final shape from
# the outside.

#-------------------------------------------------------------------------------
module OpenSCADPolyhedron
import Base.append!

export Point3, Polyhedron, stringify, generatePolyhedron, expandSymmetries

#-------------------------------------------------------------------------------
type Point3{T<:Real}
  x::Array{T,1}
end

# This object can easily be turned into a polyhedron command in OpenSCAD.
type Polyhedron{T<:Real}
  points::Array{Point3{T},1}
  faces::Array{Array{Int,1},1}

  Polyhedron{T<:Real} (points::Array{Point3{T},1}) = new(points, Array{Int,1}[])
  Polyhedron{T<:Real} (points::Array{Point3{T},1}, faces::Array{Array{Int,1},1}) = new(points, faces)
end
append!{T} (poly::Polyhedron, point::Point3{T}) = append!(poly.points, Point3{T}[point])
append!{T} (poly::Polyhedron, points::Array{Point3{T},1}) = append!(poly.points, points)
append! (p::Polyhedron, face::Array{Int,1}) = append!(p.faces, Array{Int,1}[face])

# These methods are used to generate the OpenSCAD command strings.
stringify (p::Point3) = "[$(p.x[1]), $(p.x[2]), $(p.x[3])]"
stringify (x::Int) = string(x-1)
function stringify{T} (collection::Array{T})
  strings = [ stringify(x) for x in collection ]
  return "[$(join(strings, ", "))]"
end
stringify (poly::Polyhedron) = "polyhedron(points = $(stringify(poly.points)), faces = $(stringify(poly.faces)));"

#-------------------------------------------------------------------------------
# This object is a helper object used by generatePolyhedron.
# For each transformation i and point j, it stores the index of the resulting
# point in the points array of the polyhedron object being built.
# This allows duplicate points to not be recorded in the polyhedron object,
# since the same index can be recorded multiple times in this object.
type PointIndex
  npoints::Int
  pointids::Array{Int}

  PointIndex (npoints::Int, ntransforms::Int) = new(npoints, Array(Int, npoints*ntransforms))
end
packindex (p::PointIndex, i::Int, j::Int) = p.npoints*(i-1) + j
getindex (p::PointIndex, i::Int) = p.pointids[i]
getindex (p::PointIndex, i::Int, j::Int) = p[packindex(p, i, j)]
setindex! (p::PointIndex, x::Int, i::Int) = p.pointids[i] = x
setindex! (p::PointIndex, x::Int, i::Int, j::Int) = p[packindex(p, i, j)] = x

#-------------------------------------------------------------------------------
# This is the critical function. It generates a new polyhedron that is composed
# of one copy of the base polyhedron (p) for each transform. The symmetries
# dictionary is used to link these polyhedra together, so that their shared
# vertices (and hence edges) need not be recorded multiple times in the final
# command.
function generatePolyhedron{T} (p::Polyhedron{T}, transforms::Array{Function}, symmetries::Dict{(Int, Int), (Int, Int)})
  nt = length(transforms)
  np = length(p.points)
  nf = length(p.faces)
  pointids = PointIndex(np, nt)
  result = Polyhedron{T}(Point3{T}[])
  for i in 1:nt
    for j in 1:np
      if haskey(symmetries, (i, j))
        pointids[i, j] = pointids[symmetries[(i, j)]...]
      else
        append!(result, transforms[i](p.points[j]))
        pointids[i, j] = length(result.points)
      end
    end
    for k in 1:nf
      face::Array{Int,1} = p.faces[k]
      for j in 1:length(face)
      end
      append!(result, [ pointids[i, face[j]] for j in 1:length(face) ])
    end
  end
  return result
end

#-------------------------------------------------------------------------------
# This function allows more complicated shapes to be built up from simpler ones
function expandSymmetries (fundamentalSymmetries::Dict{(Int, Int), (Int, Int)}, fundamentalFace::Array{Int,1}, layers::Set{Array{Int,1}})
  symmetries = Dict{(Int, Int), (Int, Int)}()
  for layer in layers
    # build point lookup table
    lookup = Dict{Int, Int}()
    for i::Int in 1:length(fundamentalFace)
      lookup[fundamentalFace[i]] = layer[i]
    end

    # build new symmetries
    for ((t1, p1), (t2, p2)) in fundamentalSymmetries
      symmetries[(t1, lookup[p1])] = (t2, lookup[p2])
    end
  end

  return symmetries
end

end
