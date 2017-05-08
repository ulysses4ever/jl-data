module LinearOperators

import Mesh

import Utils: ddx, sdiag, kron3, av, avExtrap, sdInv

export faceDiv, nodalGrad, edgeCurl, aveF2CC, aveF2CCV, aveCC2F, aveE2CC, aveE2CCV, aveN2CC, aveN2E, aveN2F, getFaceInnerProduct, getEdgeInnerProduct

function faceDiv(M::Mesh.AbstractTensorMesh)

    if isdefined(M.ops, :faceDiv)
        return M.ops.faceDiv
    end

    # The number of cell centers in each direction
    n = M.cnt.vnC
    # Compute faceDivergence operator on faces
    if M.cnt.dim == 1
        D = ddx(n[1])
    elseif M.cnt.dim == 2
        D1 = kron(speye(n[2]), ddx(n[1]))
        D2 = kron(ddx(n[2]), speye(n[1]))
        D = [D1 D2]
    elseif M.cnt.dim == 3
        D1 = kron3(speye(n[3]), speye(n[2]), ddx(n[1]))
        D2 = kron3(speye(n[3]), ddx(n[2]), speye(n[1]))
        D3 = kron3(ddx(n[3]), speye(n[2]), speye(n[1]))
        D = [D1 D2 D3]
    end

    # Compute areas of cell faces & volumes
    S = M.area
    V = M.vol
    M.ops.faceDiv = sdiag(1.0./V)*D*sdiag(S)
    return M.ops.faceDiv

end

function nodalGrad(M::Mesh.AbstractTensorMesh)

    if isdefined(M.ops, :nodalGrad)
        return M.ops.nodalGrad
    end

    # The number of cell centers in each direction
    n = M.cnt.vnC
    # Compute divergence operator on faces
    if M.cnt.dim == 1
        G = ddx(n[1])
    elseif M.cnt.dim == 2
        D1 = kron(speye(n[2]+1), ddx(n[1]))
        D2 = kron(ddx(n[2]), speye(n[1]+1))
        G = [D1, D2]
    elseif M.cnt.dim == 3
        D1 = kron3(speye(n[3]+1), speye(n[2]+1), ddx(n[1]))
        D2 = kron3(speye(n[3]+1), ddx(n[2]), speye(n[1]+1))
        D3 = kron3(ddx(n[3]), speye(n[2]+1), speye(n[1]+1))
        G = [D1, D2, D3]
    end
    # Compute lengths of cell edges
    L = M.edge
    M.ops.nodalGrad = sdiag(1.0./L)*G
    return M.ops.nodalGrad

end

function edgeCurl(M::Mesh.AbstractTensorMesh)

    if isdefined(M.ops, :edgeCurl)
        return M.ops.edgeCurl
    end

    n = M.cnt.vnC

    # Compute lengths of cell edges
    L = M.edge

    # Compute areas of cell faces
    S = M.area

    # Compute divergence operator on faces
    if M.cnt.dim == 2

        D21 = kron(ddx(n[2]), speye(n[1]))
        D12 = kron(speye(n[2]), ddx(n[1]))
        C = [-D21 D12]
        M.ops.edgeCurl = C*sdiag(1.0./S)
        return M.ops.edgeCurl

    elseif M.cnt.dim == 3

        D32 = kron3(ddx(n[3]), speye(n[2]), speye(n[1]+1))
        D23 = kron3(speye(n[3]), ddx(n[2]), speye(n[1]+1))
        D31 = kron3(ddx(n[3]), speye(n[2]+1), speye(n[1]))
        D13 = kron3(speye(n[3]), speye(n[2]+1), ddx(n[1]))
        D21 = kron3(speye(n[3]+1), ddx(n[2]), speye(n[1]))
        D12 = kron3(speye(n[3]+1), speye(n[2]), ddx(n[1]))

        O1 = spzeros(size(D32)[1], size(D31)[2])
        O2 = spzeros(size(D31)[1], size(D32)[2])
        O3 = spzeros(size(D21)[1], size(D13)[2])

        C = [[  O1  -D32   D23],
             [ D31    O2  -D13],
             [-D21   D12    O3]]

        M.ops.edgeCurl = sdiag(1.0./S)*(C*sdiag(L))
        return M.ops.edgeCurl

    end

end


# --------------- Averaging ---------------------

function aveF2CC(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell faces to cell centers."""
    if isdefined(M.ops, :aveF2CC)
        return M.ops.aveF2CC
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveF2CC = av(n[1])
    elseif M.cnt.dim == 2
        f2ccx = kron(speye(n[2]), av(n[1]))
        f2ccy = kron(av(n[2]), speye(n[1]))
        M.ops.aveF2CC = (0.5).*[ f2ccx f2ccy ]
    elseif M.cnt.dim == 3
        f2ccx = kron3(speye(n[3]), speye(n[2]), av(n[1]))
        f2ccy = kron3(speye(n[3]), av(n[2]), speye(n[1]))
        f2ccz = kron3(av(n[3]), speye(n[2]), speye(n[1]))
        M.ops.aveF2CC = (1./3.).*[ f2ccx f2ccy f2ccz ]
    end
    return M.ops.aveF2CC
end



function aveF2CCV(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell faces to cell centers."""
    if isdefined(M.ops, :aveF2CCV)
        return M.ops.aveF2CCV
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveF2CCV = av(n[1])
    elseif M.cnt.dim == 2
        M.ops.aveF2CCV = blkdiag(kron(speye(n[2]), av(n[1])), kron(av(n[2]), speye(n[1])))
    elseif M.cnt.dim == 3
        M.ops.aveF2CCV = blkdiag(kron3(speye(n[3]), speye(n[2]), av(n[1])),
                                 kron3(speye(n[3]), av(n[2]), speye(n[1])),
                                 kron3(av(n[3]), speye(n[2]), speye(n[1])))
    end
    return M.ops.aveF2CCV
end


function aveCC2F(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell cell centers to faces."""
    if isdefined(M.ops, :aveCC2F)
        return M.ops.aveCC2F
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveCC2F = avExtrap(n[1])
    elseif M.cnt.dim == 2
        M.ops.aveCC2F = [kron(speye(n[2]), avExtrap(n[1])),
                         kron(avExtrap(n[2]), speye(n[1]))]
    elseif M.cnt.dim == 3
        M.ops.aveCC2F = [kron3(speye(n[3]), speye(n[2]), avExtrap(n[1])),
                         kron3(speye(n[3]), avExtrap(n[2]), speye(n[1])),
                         kron3(avExtrap(n[3]), speye(n[2]), speye(n[1]))]
    end
    return M.ops.aveCC2F
end


function aveE2CC(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell edges to cell centers."""
    if isdefined(M.ops, :aveE2CC)
        return M.ops.aveE2CC
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveE2CC = speye(n[1])
    elseif M.cnt.dim == 2
        e2ccx = kron(av(n[2]), speye(n[1]))
        e2ccy = kron(speye(n[2]), av(n[1]))
        M.ops.aveE2CC = 0.5.*[ e2ccx e2ccy ]
    elseif M.cnt.dim == 3
        e2ccx = kron3(av(n[3]), av(n[2]), speye(n[1]))
        e2ccy = kron3(av(n[3]), speye(n[2]), av(n[1]))
        e2ccz = kron3(speye(n[3]), av(n[2]), av(n[1]))
        M.ops.aveE2CC = (1./3).*[ e2ccx e2ccy e2ccz ]
    end
    return M.ops.aveE2CC
end


function aveE2CCV(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell edges to cell centers."""
    if isdefined(M.ops, :aveE2CCV)
        return M.ops.aveE2CCV
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        error("Edge Averaging does not make sense in 1D: Use Identity?")
    elseif M.cnt.dim == 2
        M.ops.aveE2CCV = blkdiag(kron(av(n[2]), speye(n[1])), kron(speye(n[2]), av(n[1])))
    elseif M.cnt.dim == 3
        M.ops.aveE2CCV = blkdiag(kron3(av(n[3]), av(n[2]), speye(n[1])),
                                 kron3(av(n[3]), speye(n[2]), av(n[1])),
                                 kron3(speye(n[3]), av(n[2]), av(n[1])))
    end
    return M.ops.aveE2CCV
end


function aveN2CC(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell nodes to cell centers."""
    if isdefined(M.ops, :aveN2CC)
        return M.ops.aveN2CC
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveN2CC = av(n[1])
    elseif M.cnt.dim == 2
        M.ops.aveN2CC = kron(av(n[2]), av(n[1]))
    elseif M.cnt.dim == 3
        M.ops.aveN2CC = kron3(av(n[3]), av(n[2]), av(n[1]))
    end
    return M.ops.aveN2CC
end


function aveN2E(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell nodes to cell edges, keeping each dimension separate."""

    if isdefined(M.ops, :aveN2E)
        return M.ops.aveN2E
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveN2E = av(n[1])
    elseif M.cnt.dim == 2
        M.ops.aveN2E = [kron(speye(n[2]+1), av(n[1])),
                        kron(av(n[2]), speye(n[1]+1))]
    elseif M.cnt.dim == 3
        M.ops.aveN2E = [kron3(speye(n[3]+1), speye(n[2]+1), av(n[1])),
                        kron3(speye(n[3]+1), av(n[2]), speye(n[1]+1)),
                        kron3(av(n[3]), speye(n[2]+1), speye(n[1]+1))]
    end
    return M.ops.aveN2E
end


function aveN2F(M::Mesh.AbstractTensorMesh)
    """Construct the averaging operator on cell nodes to cell faces, keeping each dimension separate."""
    if isdefined(M.ops, :aveN2F)
        return M.ops.aveN2F
    end
    n = M.cnt.vnC
    if M.cnt.dim == 1
        M.ops.aveN2F = av(n[1])
    elseif M.cnt.dim == 2
        M.ops.aveN2F = [kron(av(n[2]), speye(n[1]+1)),
                        kron(speye(n[2]+1), av(n[1]))]
    elseif M.cnt.dim == 3
        M.ops.aveN2F = [kron3(av(n[3]), av(n[2]), speye(n[1]+1)),
                        kron3(av(n[3]), speye(n[2]+1), av(n[1])),
                        kron3(speye(n[3]+1), av(n[2]), av(n[1]))]
    end
    return M.ops.aveN2F
end

function getTensorInnerProduct(projType::String, M::Mesh.AbstractTensorMesh, prop=ones(M.cnt.nC); invProp::Bool=false, invMat::Bool=false)

    @assert projType in ["E", "F"]

    if invProp
        prop = 1.0./prop
    end

    if typeof(prop) <: Number
        prop = prop.*ones(M.cnt.nC)
    end

    if length(prop) == M.cnt.nC
        Av = (projType == "E")? aveE2CC(M) : aveF2CC(M)
        Vprop = M.vol .* prop[:]
        M = M.cnt.dim * sdiag(Av' * Vprop)
    elseif length(prop) == M.cnt.nC*M.cnt.dim
        Av = (projType == "E")? aveE2CCV(M) : aveF2CCV(M)
        V = kron(speye(M.cnt.dim), sdiag(M.vol))
        M = sdiag(Av' * V * prop[:])
    else
        return
    end

    if invMat
        return sdInv(M)
    else
        return M
    end

end

function getFaceInnerProduct(M::Mesh.AbstractTensorMesh, prop=ones(M.cnt.nC); invProp::Bool=false, invMat::Bool=false)
    return getTensorInnerProduct("F", M, prop; invProp=invProp, invMat=invMat)
end
function getEdgeInnerProduct(M::Mesh.AbstractTensorMesh, prop=ones(M.cnt.nC); invProp::Bool=false, invMat::Bool=false)
    return getTensorInnerProduct("E", M, prop; invProp=invProp, invMat=invMat)
end

end
