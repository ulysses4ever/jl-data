abstract AbstractReferenceElement

abstract AbstractReferenceElement_1D <: AbstractReferenceElement
abstract AbstractReferenceElement_2D <: AbstractReferenceElement
abstract AbstractReferenceElement_3D <: AbstractReferenceElement

vertices(refele::AbstractReferenceElement) = refele.vertices
edges(refele::AbstractReferenceElement) = refele.edges
faces(refele::Union(AbstractReferenceElement_2D,
                    AbstractReferenceElement_3D)) = refele.faces

cell(refele::AbstractReferenceElement_3D) = refele.cell
facet(refele::AbstractReferenceElement_2D) = refele.edges
facet(refele::AbstractReferenceElement_3D) = refele.faces

dim(::AbstractReferenceElement_1D) = 1
dim(::AbstractReferenceElement_2D) = 2
dim(::AbstractReferenceElement_3D) = 3


# TODO this can fail for entity(refline, 3) for example
function entity(refele::AbstractReferenceElement, dim::Int)
    if dim == 1
        return refele.edges
    elseif dim == 2
        return refele.faces
    elseif dim == 3
        return refele.cell
    end
end


immutable ReferenceLine <: AbstractReferenceElement_1D
    vertices::Vector{Vector{Float64}}
    edges::Vector{Vector{Int}}
end

function ReferenceLine()
    vertices = Array(Vector{Float64}, 2)
    vertices[1] = [-1]
    vertices[2] = [1]
    edges = Array(Vector{Int}, 1)
    edges[1] = [1, 2]

    ReferenceLine(vertices, edges)
end
volume(::ReferenceLine) = 2.0


immutable ReferenceTriangle <: AbstractReferenceElement_2D
    vertices::Vector{Vector{Float64}}
    edges::Vector{Vector{Int}}
    faces::Vector{Vector{Int}}
end

function ReferenceTriangle()
    vertices = Array(Vector{Float64}, 3)
    vertices[1] = [0, 0]
    vertices[2] = [1, 0]
    vertices[3] = [0, 1]

    edges = Array(Vector{Int}, 3)
    edges[1] = [1, 2]
    edges[2] = [2, 3]
    edges[3] = [3, 1]

    faces = Array(Vector{Int}, 1)
    faces[1] = [1, 2, 3]

    ReferenceTriangle(vertices, edges, faces)
end
volume(::ReferenceTriangle) = 0.5


immutable ReferenceSquare <: AbstractReferenceElement_2D
    vertices::Vector{Vector{Float64}}
    edges::Vector{Vector{Int}}
    faces::Vector{Vector{Int}}
end

function ReferenceSquare()
    vertices = Array(Vector{Float64}, 4)
    vertices[1] = [-1, -1]
    vertices[2] = [ 1, -1]
    vertices[3] = [ 1,  1]
    vertices[4] = [-1,  1]

    edges = Array(Vector{Int}, 4)
    edges[1] = [1, 2]
    edges[2] = [2, 3]
    edges[3] = [3, 4]
    edges[4] = [4, 1]

    faces = Array(Vector{Int}, 1)
    faces[1] = [1, 2, 3, 4]

    ReferenceSquare(vertices, edges, faces)
end
volume(::ReferenceSquare) = 4.0

immutable ReferenceTetrahedron <: AbstractReferenceElement_3D
    vertices::Vector{Vector{Float64}}
    edges::Vector{Vector{Int}}
    faces::Vector{Vector{Int}}
    cell::Vector{Int}
end

function ReferenceTetrahedron()
    vertices = Array(Vector{Float64}, 4)
    vertices[1] = [0, 0 ,0]
    vertices[2] = [1, 0, 0]
    vertices[3] = [0, 1, 0]
    vertices[4] = [0, 0, 1]

    edges = Array(Vector{Int}, 6)
    edges[1] = [1, 2]
    edges[2] = [1, 3]
    edges[3] = [1, 4]
    edges[4] = [2, 3]
    edges[5] = [2, 4]
    edges[6] = [3, 4]

    faces = Array(Vector{Int}, 4)
    faces[1] = [1, 3, 2]
    faces[2] = [1, 2, 4]
    faces[3] = [1, 4, 3]
    faces[4] = [2, 3, 4]

    cell = [1, 2, 3, 4]

    ReferenceTetrahedron(vertices, edges, faces, cell)
end
volume(::ReferenceTetrahedron) = 1/6


immutable ReferenceCube <: AbstractReferenceElement_3D
    vertices::Vector{Vector{Float64}}
    edges::Vector{Vector{Int}}
    faces::Vector{Vector{Int}}
    cell::Vector{Int}
end

function ReferenceCube()
    vertices = Array(Vector{Float64}, 8)
    vertices[1] = [-1, -1, -1]
    vertices[2] = [ 1, -1, -1]
    vertices[3] = [ 1,  1, -1]
    vertices[4] = [-1,  1, -1]
    vertices[5] = [-1, -1,  1]
    vertices[6] = [ 1, -1,  1]
    vertices[7] = [ 1,  1,  1]
    vertices[8] = [-1,  1,  1]


    edges = Array(Vector{Int}, 12)
    edges[1] = [1, 2]
    edges[2] = [1, 3]
    edges[3] = [1, 5]
    edges[4] = [2, 4]
    edges[5] = [2, 6]
    edges[6] = [3, 4]
    edges[7] = [3, 7]
    edges[8] = [4, 8]
    edges[9] = [5, 6]
    edges[10] = [5, 7]
    edges[11] = [6, 8]
    edges[12] = [7, 8]

    faces = Array(Vector{Int}, 6)
    faces[1] = [1, 2, 6, 5]
    faces[2] = [1, 3, 4, 2]
    faces[3] = [1, 5, 7, 3]
    faces[4] = [2, 4, 8, 6]
    faces[5] = [3, 7, 8, 4]
    faces[6] = [5, 6, 8, 7]

    cell = [1, 2, 3, 4, 5, 6, 7, 8]

    ReferenceCube(vertices, edges, faces, cell)
end
volume(::ReferenceCube) = 8
