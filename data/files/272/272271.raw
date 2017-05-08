function hermiteH(T::Type, n::Integer, sym::Symbol=:x)
    p0,p1 = zeros(T,n+1), zeros(T,n+1)
    p1[1] = one(T)

    for i = 1:n
        p0,p1 = p1,p0
        p1[1] = -p0[2]
        for j=2:i
            p1[j] = 2*p0[j-1] - j*p0[j+1]
        end
        p1[i+1] = 2*p0[i]
    end

    Poly(p1, sym)
end

#hermiteH(n::Integer) = hermite(Int, n)
#hermiteH(n::Integer, sym::Symbol) = hermite(Int, n, sym)
@signatures hermiteH Int


function hermiteHe(T::Type, n::Integer, sym::Symbol=:x)
    p0,p1 = zeros(T,n+1), zeros(T,n+1)
    p1[1] = one(T)

    for i = 1:n
        p0,p1 = p1,p0
        p1[1] = -p0[2]
        for j=2:i
            p1[j] = p0[j-1] - j*p0[j+1]
        end
        p1[i+1] = p0[i]
    end

    Poly(p1, sym)
end

@signatures hermiteHe Int
