module Mesh

abstract SimpegMesh
abstract SimpegMesh1D <: SimpegMesh
abstract SimpegMesh2D <: SimpegMesh
abstract SimpegMesh3D <: SimpegMesh

import MeshCount

type TensorMesh1D <: SimpegMesh2D
    hx::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh1DCounters
    TensorMesh1D(hx, x0) = new(hx, x0, MeshCount.countTensorMesh([length(hx)]))
end

type TensorMesh2D <: SimpegMesh2D
    hx::Vector{Float64}
    hy::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh2DCounters
    TensorMesh2D(hx, hy, x0) = new(hx, hy, x0, MeshCount.countTensorMesh([length(hx), length(hy)]))
end


type TensorMesh3D <: SimpegMesh3D
    hx::Vector{Float64}
    hy::Vector{Float64}
    hz::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh3DCounters
    TensorMesh3D(hx, hy, hz, x0) = new(hx, hy, hz, x0, MeshCount.countTensorMesh([length(hx), length(hy), length(hz)]))
end

function TensorMesh(hx::Vector{Float64}; x0=zeros(1))
    return TensorMesh1D(hx, x0)
end

function TensorMesh(hx::Vector{Float64},hy::Vector{Float64}; x0=zeros(2))
    return TensorMesh2D(hx, hy, x0)
end

function TensorMesh(hx::Vector{Float64},hy::Vector{Float64},hz::Vector{Float64}; x0=zeros(3))
    return TensorMesh3D(hx, hy, hz, x0)
end

hx = ones(5)
hy = ones(3)
hz = ones(4)

M = TensorMesh(hx, hy)
println(M)
println(M.cnt.nF)

end
