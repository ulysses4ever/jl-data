function legendre{T<:Number}(::Type{T}, n::Integer, sym::Symbol=:x)
    if T <: Integer
        error("$T is an integer, but legendre polynomials have fractional coefficient.")
        return
    end
    p0,p1,p2 = zeros(T,n+1), zeros(T,n+1), zeros(T,n+1)
    p0[1] = one(T)
    if n==0
        return Poly(p0, sym)
    end
    p1[2] = one(T)

    for i = 2:n
        p2[1] = -(i-1)*p0[1]/i
        for j=2:i+1
            p2[j] = ((2i-1)*p1[j-1]-(i-1)*p0[j])/i
        end
        p0,p1,p2 = p1,p2,p0
    end

    Poly(p1, sym)
end

#legendre(n::Integer) = legendre(Float64,n)
#legendre(n::Integer, sym::Symbol) = legendre(Float64,n,sym)
@signatures legendre Float64
