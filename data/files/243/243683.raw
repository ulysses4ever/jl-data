module MeshCount


abstract MeshCounters
abstract MeshCounters1D <: MeshCounters
abstract MeshCounters2D <: MeshCounters
abstract MeshCounters3D <: MeshCounters


type TensorMesh1DCounters <: MeshCounters1D
    dim::Int64
    nC::Int64
    nN::Int64
    nF::Int64
    nE::Int64
    vnC::Array{Int64}
    vnN::Array{Int64}
    vnF::Array{Int64}
    vnE::Array{Int64}
    nCx::Int64
    nNx::Int64
    nFx::Int64
    nEx::Int64
    vnFx::Array{Int64}
    vnEx::Array{Int64}
end

type TensorMesh2DCounters <: MeshCounters2D
    dim::Int64
    nC::Int64
    nN::Int64
    nF::Int64
    nE::Int64
    vnC::Array{Int64}
    vnN::Array{Int64}
    vnF::Array{Int64}
    vnE::Array{Int64}
    nCx::Int64
    nCy::Int64
    nNx::Int64
    nNy::Int64
    nFx::Int64
    nFy::Int64
    nEx::Int64
    nEy::Int64
    vnFx::Array{Int64}
    vnFy::Array{Int64}
    vnEx::Array{Int64}
    vnEy::Array{Int64}
end

type TensorMesh3DCounters <: MeshCounters3D
    dim::Int64
    nC::Int64
    nN::Int64
    nF::Int64
    nE::Int64
    vnC::Array{Int64}
    vnN::Array{Int64}
    vnF::Array{Int64}
    vnE::Array{Int64}
    nCx::Int64
    nCy::Int64
    nCz::Int64
    nNx::Int64
    nNy::Int64
    nNz::Int64
    nFx::Int64
    nFy::Int64
    nFz::Int64
    nEx::Int64
    nEy::Int64
    nEz::Int64
    vnFx::Array{Int64}
    vnFy::Array{Int64}
    vnFz::Array{Int64}
    vnEx::Array{Int64}
    vnEy::Array{Int64}
    vnEz::Array{Int64}
end

function countTensorMesh(n::Vector{Int64})

    if length(n) == 1

        vnC  = n
        vnN  = n + 1

        vnFx = n + 1
        vnF  = [prod(vnFx)]

        vnEx = n
        vnE  = [prod(vnEx)]

        return TensorMesh1DCounters(
                1,
                prod(vnC), prod(vnN), sum(vnF), sum(vnE),
                vnC, vnN, vnF, vnE,
                vnC[1],
                vnN[1],
                vnF[1],
                vnE[1],
                vnFx,
                vnEx
            )

    elseif length(n) == 2

        vnC  = n
        vnN  = n + [1, 1]

        vnFx = n + [1, 0]
        vnFy = n + [0, 1]
        vnF  = [prod(vnFx), prod(vnFy)]

        vnEx = n + [0, 1]
        vnEy = n + [1, 0]
        vnE  = [prod(vnEx), prod(vnEy)]

        return TensorMesh2DCounters(
                2,
                prod(vnC), prod(vnN), sum(vnF), sum(vnE),
                vnC, vnN, vnF, vnE,
                vnC[1], vnC[2],
                vnN[1], vnN[2],
                vnF[1], vnF[2],
                vnE[1], vnE[2],
                vnFx, vnFy,
                vnEx, vnEy
            )

    elseif length(n) == 3

        vnC  = n
        vnN  = n + [1, 1, 1]

        vnFx = n + [1, 0, 0]
        vnFy = n + [0, 1, 0]
        vnFz = n + [0, 0, 1]
        vnF  = [prod(vnFx), prod(vnFy), prod(vnFz)]

        vnEx = n + [0, 1, 1]
        vnEy = n + [1, 0, 1]
        vnEz = n + [1, 1, 0]
        vnE  = [prod(vnEx), prod(vnEy), prod(vnEz)]

        return TensorMesh3DCounters(
                3,
                prod(vnC), prod(vnN), sum(vnF), sum(vnE),
                vnC, vnN, vnF, vnE,
                vnC[1], vnC[2], vnC[3],
                vnN[1], vnN[2], vnN[3],
                vnF[1], vnF[2], vnF[3],
                vnE[1], vnE[2], vnE[3],
                vnFx, vnFy, vnFz,
                vnEx, vnEy, vnEz
            )
    end

end


end
