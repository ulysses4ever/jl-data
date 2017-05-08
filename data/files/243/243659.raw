module Mesh

abstract AbstractSimpegMesh
abstract AbstractTensorMesh <: AbstractSimpegMesh

import MeshCount
import MeshOperators

type TensorMesh1D <: AbstractTensorMesh
    hx::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh1DCounters
    ops::MeshOperators.DifferentialOperators
    TensorMesh1D(hx, x0) = new(hx, x0, MeshCount.countTensorMesh([length(hx)]), MeshOperators.DifferentialOperators())
    vol::Vector{Float64}
    area::Vector{Float64}
    edge::Vector{Float64}
end

type TensorMesh2D <: AbstractTensorMesh
    hx::Vector{Float64}
    hy::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh2DCounters
    ops::MeshOperators.DifferentialOperators
    TensorMesh2D(hx, hy, x0) = new(hx, hy, x0, MeshCount.countTensorMesh([length(hx), length(hy)]), MeshOperators.DifferentialOperators())
    vol::Vector{Float64}
    area::Vector{Float64}
    edge::Vector{Float64}
end

type TensorMesh3D <: AbstractTensorMesh
    hx::Vector{Float64}
    hy::Vector{Float64}
    hz::Vector{Float64}
    x0::Vector{Float64}
    cnt::MeshCount.TensorMesh3DCounters
    ops::MeshOperators.DifferentialOperators
    TensorMesh3D(hx, hy, hz, x0) = new(hx, hy, hz, x0, MeshCount.countTensorMesh([length(hx), length(hy), length(hz)]), MeshOperators.DifferentialOperators())
    vol::Vector{Float64}
    area::Vector{Float64}
    edge::Vector{Float64}
end

function TensorMesh(hx::Vector{Float64}; x0=zeros(1))
    M = TensorMesh1D(hx, x0)
    M.vol = hx
    M.area = ones(M.cnt.nN)
    M.edge = hx
    return M
end

function TensorMesh(hx::Vector{Float64}, hy::Vector{Float64}; x0=zeros(2))
    M = TensorMesh2D(hx, hy, x0)
    M.vol  = (hx * hy')[:]
    M.area = [
                (ones(M.cnt.nNx) * hy')[:],
                (hx * ones(M.cnt.nNy)')[:]
             ]
    M.edge = [
                (hx * ones(M.cnt.nNy)')[:],
                (ones(M.cnt.nNx) * hy')[:]
             ]
    return M
end

function TensorMesh(hx::Vector{Float64}, hy::Vector{Float64}, hz::Vector{Float64}; x0=zeros(3))
    M = TensorMesh3D(hx, hy, hz, x0)
    M.vol = ((hx * hy')[:] * hz')[:]
    M.area = [
                ( ones(M.cnt.nNx) * ( hy * hz' )[:]' )[:],
                ( hx * ( ones(M.cnt.nNy) * hz' )[:]' )[:],
                ( hx * ( hy * ones(M.cnt.nNz)' )[:]' )[:]
             ]
    M.edge = [
                ( hx * ( ones(M.cnt.nNy) * ones(M.cnt.nNz)' )[:]' )[:],
                ( ones(M.cnt.nNx) * ( hy * ones(M.cnt.nNz)' )[:]' )[:],
                ( ones(M.cnt.nNx) * ( ones(M.cnt.nNy) * hz' )[:]' )[:]
             ]
    return M
end

end
