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

function kron3(A, B, C)
    return kron( kron(A, B), C )
end

end
