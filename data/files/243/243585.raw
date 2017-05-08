export vectorCCx, vectorCCy, vectorCCz, vectorNx, vectorNy, vectorNz, getTensor, gridCC, gridN, gridFx, gridFy, gridFz, gridEx, gridEy, gridEz

function vectorCCx(M::AbstractTensorMesh)
    return [0, cumsum(M.hx[1:end-1])] + 0.5.*M.hx + M.x0[1]
end

function vectorCCy(M::AbstractTensorMesh)
    if M.cnt.dim < 2; return; end
    return [0, cumsum(M.hy[1:end-1])] + 0.5.*M.hy + M.x0[2]
end

function vectorCCz(M::AbstractTensorMesh)
    if M.cnt.dim < 3; return; end
    return [0, cumsum(M.hz[1:end-1])] + 0.5.*M.hz + M.x0[3]
end

function vectorNx(M::AbstractTensorMesh)
    return [0., cumsum(M.hx)] + M.x0[1]
end

function vectorNy(M::AbstractTensorMesh)
    if M.cnt.dim < 2; return; end
    return [0., cumsum(M.hy)] + M.x0[2]
end

function vectorNz(M::AbstractTensorMesh)
    if M.cnt.dim < 3; return; end
    return [0., cumsum(M.hz)] + M.x0[3]
end

function getTensor(M::AbstractTensorMesh, key::String="CC")
    """ Returns a tensor list.

    :param str key: What tensor (see below)
    :rtype: list
    :return: list of the tensors that make up the mesh.

    key can be::

        'CC'    -> scalar field defined on cell centers
        'N'     -> scalar field defined on nodes
        'Fx'    -> x-component of field defined on faces
        'Fy'    -> y-component of field defined on faces
        'Fz'    -> z-component of field defined on faces
        'Ex'    -> x-component of field defined on edges
        'Ey'    -> y-component of field defined on edges
        'Ez'    -> z-component of field defined on edges

    """

    @assert key in ["CC", "N", "Fx", "Fy", "Fz", "Ex", "Ey", "Ez"]

    if     key == "Fx"
        ten = (vectorNx(M) , vectorCCy(M), vectorCCz(M))
    elseif key == "Fy"
        ten = (vectorCCx(M), vectorNy(M) , vectorCCz(M))
    elseif key == "Fz"
        ten = (vectorCCx(M), vectorCCy(M), vectorNz(M) )
    elseif key == "Ex"
        ten = (vectorCCx(M), vectorNy(M) , vectorNz(M) )
    elseif key == "Ey"
        ten = (vectorNx(M) , vectorCCy(M), vectorNz(M) )
    elseif key == "Ez"
        ten = (vectorNx(M) , vectorNy(M) , vectorCCz(M))
    elseif key == "CC"
        ten = (vectorCCx(M), vectorCCy(M), vectorCCz(M))
    elseif key == "N"
        ten = (vectorNx(M) , vectorNy(M) , vectorNz(M) )
    end

    if M.cnt.dim == 1
        return (ten[1],)
    elseif M.cnt.dim == 2
        return (ten[1], ten[2])
    elseif M.cnt.dim == 3
        return ten
    end
end


function gridCC(M::AbstractTensorMesh; asVector=true)
    return ndgrid(getTensor(M, "CC")...; asVector=asVector)
end

function gridN(M::AbstractTensorMesh; asVector=true)
    return ndgrid(getTensor(M, "N")...; asVector=asVector)
end

function gridFx(M::AbstractTensorMesh; asVector=true)
    return ndgrid(getTensor(M, "Fx")...; asVector=asVector)
end

function gridFy(M::AbstractTensorMesh; asVector=true)
    if M.cnt.dim < 2; return; end
    return ndgrid(getTensor(M, "Fy")...; asVector=asVector)
end

function gridFz(M::AbstractTensorMesh; asVector=true)
    if M.cnt.dim < 3; return; end
    return ndgrid(getTensor(M, "Fz")...; asVector=asVector)
end

function gridEx(M::AbstractTensorMesh; asVector=true)
    return ndgrid(getTensor(M, "Ex")...; asVector=asVector)
end

function gridEy(M::AbstractTensorMesh; asVector=true)
    if M.cnt.dim < 2; return; end
    return ndgrid(getTensor(M, "Ey")...; asVector=asVector)
end

function gridEz(M::AbstractTensorMesh; asVector=true)
    if M.cnt.dim < 3; return; end
    return ndgrid(getTensor(M, "Ez")...; asVector=asVector)
end
