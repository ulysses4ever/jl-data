#! /usr/bin/julia

# Rosetta Code, Zig-zag matrix

immutable ZigZag
    m::Int
    n::Int
    diag::Array{Int,1}
    cmax::Int
    numd::Int
    lohi::(Int,Int)
end
    
function zigzag(m::Int, n::Int)
    0<m && 0<n || error("The matrix dimensions must be positive.")
    ZigZag(m, n, [-1,1], m*n, m+n-1, extrema([m,n]))
end
zigzag(n::Int) = zigzag(n, n)

type ZZState
    cnt::Int
    cell::Array{Int,1}
    dir::Int
    dnum::Int
    dlen::Int
    dcnt::Int
end

Base.length(zz::ZigZag) = zz.cmax
Base.start(zz::ZigZag) = ZZState(1, [1,1], 1, 1, 1, 1)
Base.done(zz::ZigZag, zzs::ZZState) = zzs.cnt > zz.cmax

function Base.next(zz::ZigZag, zzs::ZZState)
    s = sub2ind((zz.m, zz.n), zzs.cell[1], zzs.cell[2])
    if zzs.dcnt == zzs.dlen
        if isodd(zzs.dnum)
            if zzs.cell[2] < zz.n
                zzs.cell[2] += 1
            else
                zzs.cell[1] += 1
            end
        else
            if zzs.cell[1] < zz.m
                zzs.cell[1] += 1
            else
                zzs.cell[2] += 1
            end
        end
        zzs.dcnt = 1
        zzs.dnum += 1
        zzs.dir = -zzs.dir
        if zzs.dnum <= zz.lohi[1]
            zzs.dlen += 1
        elseif zz.lohi[2] < zzs.dnum
            zzs.dlen -= 1
        end
    else
        zzs.cell += zzs.dir*zz.diag
        zzs.dcnt += 1
    end
    zzs.cnt += 1
    return (s, zzs)
end

using Formatting

function width{T<:Integer}(n::T)
    w = ndigits(n)
    n < 0 || return w
    return w + 1
end

function pretty{T<:Integer}(a::Array{T,2}, indent::Int=4)
    lo, hi = extrema(a)
    w = max(width(lo), width(hi))
    id = " "^indent
    fe = FormatExpr(@sprintf(" {:%dd}", w))
    s = id
    nrow = size(a)[1]
    for i in 1:nrow
        for j in a[i,:]
            s *= format(fe, j)
        end
        i != nrow || continue
        s *= "\n"*id
    end
    return s
end

n = 5
println("The n = ", n, " zig-zag matrix:")
a = zeros(Int, (n, n))
for (i, s) in enumerate(zigzag(n))
    a[s] = i-1
end
println(pretty(a))

m = 3
println()
println("Generalize to a non-square matrix (", m, "x", n, "):")
a = zeros(Int, (m, n))
for (i, s) in enumerate(zigzag(m, n))
    a[s] = i-1
end
println(pretty(a))

p = primes(10^3)
n = 7
println()
println("An n = ", n, " prime spiral matrix:")
a = zeros(Int, (n, n))
for (i, s) in enumerate(zigzag(n))
    a[s] = p[i]
end
println(pretty(a))
