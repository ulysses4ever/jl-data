


module Mesh2d

export nverts, nedges

abstract Element
abstract Element2d <: Element

type Quad <: Element2d
    id::Int
    nv::Int
    ne::Int
    verts::Array{Float64,2}
    neigh::Array{Int,2}
    curve::Array{Int,1}
    curved::Bool
    hasbc::Bool
    orient::Array{Bool,1}
    Quad() = new(0, 4, 4, zeros(Float64,4,2), zeros(Int,4,2), zeros(Int,4),
                 false, false, [true, true, false, false])
end


type Tri <: Element2d
    id::Int
    nv::Int
    ne::Int
    verts::Array{Float64,2}
    neigh::Array{Int,2}
    curve::Array{Int,1}
    curved::Bool
    hasbc::Bool
    Tri() = new(0, 3, 3, zeros(Float64,3,2), zeros(Int,3,2), zeros(Int,3), false, false)
end

nverts(e::Quad) = 4
nedges(e::Quad) = 4
nverts(e::Tri) = 3
nedges(e::Tri) = 3

xverts(e::Element2d) = sub(e.verts, :, 1)
yverts(e::Element2d) = sub(e.verts, :, 2)


vertex_in_edge_quad = reshape([1,2,2,3,3,4,4,1], 2,4)
vertex_in_edge_tri = reshape([1,2,2,3,3,1], 2,3)
vinedge(el::Quad, edge) = sub(vertex_in_edge_quad, :, edge)
vinedge(edge) = sub(vertex_in_edge_quad, :, edge)

vinedge(el::Tri, edge) = sub(vertex_in_edge_tri, :, edge)

edge_in_vertex_quad = reshape([4,1,1,2,2,3,3,4], 2,4)
edge_in_vertex_tri = reshape([3,1,1,2,2,3], 2,3)
einvert(el::Quad, vert) = sub(edge_in_vertex_quad, :, vert)
einvert(vert) = sub(edge_in_vertex_quad, :, vert)

einvert(el::Tri, vert) = sub(edge_in_vertex_tri, :, vert)

abstract Bndry



abstract Curve
abstract Curve2d <: Curve

type Segment <: Curve2d
    seg::Int
    Segment() = new(0)
end

type Circle <: Curve2d
    xc::Float64
    yc::Float64
    rad::Float64
    inside::Bool
    Circle(x, y, r, s=false) = new(x, y, r, s)
end



type Mesh
    elems::Array{Element2d,1}
    curves::Array{Curve2d,1}
    bcs::Array{Bndry,1}
    other::Any
end



    
include("curve.jl")    

end


