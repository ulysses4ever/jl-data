module DoublelengthFloat

import Base: +, -, ⋅, *, /, √, convert
export Doublelength

immutable Doublelength{T<:FloatingPoint} <: FloatingPoint
    head :: T
    tail :: T
end
Doublelength(x::FloatingPoint) = Doublelength(x, zero(x))
convert{T<:FloatingPoint}(::Type{Doublelength{T}}, x::T) = Doublelength(x)

#The following precision computation is based on the maximal error constant of 12.1 in (7.10),
#which is slightly less than 4 bits' worth of error.
precision(a::Doublelength) = precision(a.head) + precision(a.head) - 4

#add2
function +{T<:FloatingPoint}(a::Doublelength{T}, b::Doublelength{T})
    x, xx = a.head, a.tail
    y, yy = b.head, b.tail
    r = x + y
    s = abs(x) > abs(y) ? x - r + y + xx + xx :
                          y - r + x + xx + yy
    z = r + s
    zz = r - z + s
    Doublelength(z, zz)
end

#sub2
function -{T<:FloatingPoint}(a::Doublelength{T}, b::Doublelength{T})
    x, xx = a.head, a.tail
    y, yy = b.head, b.tail
    r = x - y
    s = abs(x) > abs(y) ? x - r - y - yy + xx :
                         -y - r + x + xx - yy
    z = r + s
    zz = r - z + s
    Doublelength(z, zz)
end

#mul12
function ⋅{T<:FloatingPoint}(x::T, y::T)
    const t = precision(one(T))
    const constant = 2^(t-t÷2)+1
    p = x * constant
    hx = x - p + p
    tx = x - hx
    p = y * constant
    hy = y - p + p
    ty = y - hy
    p = hx * hy
    q = hx * ty + tx * hy
    z = p + q
    zz = p - z + q + tx * ty
    Doublelength(z, zz)
end

#mul2
function *{T<:FloatingPoint}(a::Doublelength{T}, b::Doublelength{T})
    x, xx = a.head, a.tail
    y, yy = b.head, b.tail
    C = x ⋅ y #mul12
    c, cc = C.head, C.tail
    cc = x*yy + xx*y + cc
    z = c + cc
    zz = c - z + cc
    Doublelength(z, zz)
end

#div2
function /{T<:FloatingPoint}(a::Doublelength{T}, b::Doublelength{T})
    x, xx = a.head, a.tail
    y, yy = b.head, b.tail
    c = x / y
    U = c ⋅ y
    u, uu = U.head, U.tail
    cc = (x - u - uu + xx - c * yy)/y
    z = c + cc
    zz = c - z + cc
    Doublelength(z, zz)
end

#sqrt2
function √{T<:FloatingPoint}(a::Doublelength{T})
    x, xx = a.head, a.tail
    x ≥ 0 || throw(DomainError())
    c = √x
    U = c ⋅ c
    u, uu = U.head, U.tail
    cc = (x - u - uu + xx) * 0.5/c
    y = c + cc
    yy = c - y + cc
    Doublelength(y, yy)
end

end # module