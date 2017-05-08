module Utils

function sdiag(x::Vector)
    spdiagm((x,),0)
end

function ddx(n::Int64)
    return spdiagm((-1.0*ones(n), +1.0*ones(n)), (0,1), n, n+1)
end

function av(n::Int64)
    return spdiagm((+0.5*ones(n), +0.5*ones(n)), (0,1), n, n+1)
end

function avExtrap(n::Int64)
    """Define 1D averaging operator from cell-centers to nodes."""
    Av = spdiagm((+0.5*ones(n), +0.5*ones(n)), (-1, 0), n+1, n)
    Av[1,1] = 1
    Av[end,end] = 1
    return Av
end

function kron3(A, B, C)
    return kron( kron(A, B), C )
end

end
