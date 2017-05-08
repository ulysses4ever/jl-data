
function loweringoperator(s::Real)
    sizem = int(2*s)+1
    ssq = s*(s+1)

    result = zeros(sizem,sizem)

    for i = 1:sizem-1
        m = s - i
        result[i+1,i] = (ssq-m*(m+1))^0.5
    end

    return result
end

function raisingoperator(s::Real)
    sizem = int(2*s)+1
    ssq = s*(s+1)

    result = zeros(sizem,sizem)

    for i = 1:sizem-1
        m = s - i
        result[i,i+1] = (ssq-m*(m+1))^0.5
    end

    return result
end

Jz(s) = diagm([s:-1:-s])
Jx(s) = 1/2*(raisingoperator(s) + loweringoperator(s))
Jy(s) = 1im/2*(loweringoperator(s) - raisingoperator(s))

function AnisoTensor(D::Real, E::Real)
    dz = 2.0/3.0*D
    dx = E - 0.5*dz
    dy = -2.0*E + dx
    mat = diagm([dx dy dz])
    return mat
end

