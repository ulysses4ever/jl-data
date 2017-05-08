module Utils

export sdiag, ddx, av, avExtrap, kron3, sdInv, ndgrid

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

function sdInv(A)
    return sdiag(1.0./diag(A))
end

# https://github.com/JuliaLang/julia/blob/master/examples/ndgrid.jl

function ndgrid{T}(v1::AbstractVector{T}, v2::AbstractVector{T})
    m, n = length(v1), length(v2)
    v1 = reshape(v1, m, 1)
    v2 = reshape(v2, 1, n)
    (repmat(v1, 1, n), repmat(v2, m, 1))
end

function ndgrid_fill(a, v, s, snext)
    for j = 1:length(a)
        a[j] = v[div(rem(j-1, snext), s)+1]
    end
end

function ndgrid{T}(vs::AbstractVector{T}...;asVector=false)
    n = length(vs)
    sz = map(length, vs)
    out = ntuple(n, i->Array(T, sz))
    s = 1
    for i=1:n
        a = out[i]::Array
        v = vs[i]
        snext = s*size(a,i)
        ndgrid_fill(a, v, s, snext)
        s = snext
    end
    if asVector
        return cat(2,[v[:] for v in out]...)
    else
        return out
    end
end

end
