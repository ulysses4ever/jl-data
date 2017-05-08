module LinearOperators

import Mesh

import Utils: ddx, sdiag, kron3

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


end
