function factors(n)
    f = [one(n)]
    for (p,e) in factor(n)
        f = reduce(vcat, f, [f*p^j for j in 1:e])
    end
    return length(f) == 1 ? [one(n), n] : sort!(f)
end

function d(n ::Integer)
    vector = factors(n)
    pop!(vector)
    return sum(vector)
end

function amigable(x ::Integer, y::Integer)
    if ((d(x) == y) && (x != y) && (d(y) == x))
        return true
    else
        return false
    end
end

function sumaAmigable(limite ::Integer)
    listaAmigable = Integer[]
    for i=1:limite
        if ( amigable( i, d(i) ) )
            push!(listaAmigable, i)
        end
    end
    return sum(listaAmigable)
end
