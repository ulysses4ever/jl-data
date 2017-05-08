module LinearOperators

import Mesh

import Utils

function faceDiv(M::Mesh.AbstractTensorMesh)

    if isdefined(M.ops, :faceDiv)
        return M.ops.faceDiv
    end

    # The number of cell centers in each direction
    n = M.cnt.vnC
    # Compute faceDivergence operator on faces
    if M.cnt.dim == 1
        D = Utils.ddx(n[1])
    elseif M.cnt.dim == 2
        D1 = kron(speye(n[2]), Utils.ddx(n[1]))
        D2 = kron(Utils.ddx(n[2]), speye(n[1]))
        D = [D1 D2]
    elseif M.cnt.dim == 3
        D1 = Utils.kron3(speye(n[3]), speye(n[2]), Utils.ddx(n[1]))
        D2 = Utils.kron3(speye(n[3]), Utils.ddx(n[2]), speye(n[1]))
        D3 = Utils.kron3(Utils.ddx(n[3]), speye(n[2]), speye(n[1]))
        D = [D1 D2 D3]
    end
    # Compute areas of cell faces & volumes
    S = M.area
    V = M.vol
    M.ops.faceDiv = Utils.sdiag(1.0./V)*D*Utils.sdiag(S)
    return M.ops.faceDiv

end

end
