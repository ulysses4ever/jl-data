function d(n ::Integer)
    function factors(n)
        f = [one(n)]
        for (p,e) in factor(n)
            f = reduce(vcat, f, [f*p^j for j in 1:e])
        end
        return length(f) == 1 ? [one(n), n] : sort!(f)
    end
    vector = factors(n)
    pop!(vector)
    return sum(vector)
end

function esPerfecto(n::Integer)
    if (d(n) == n)
        return true
    else
        return false
    end
end

function esDeficiente(n::Integer)
    if (d(n) < n)
        return true
    else
        return false
    end
end

function esAbundante(n::Integer)
    if (d(n) > n)
        return true
    else
        return false
    end
end

function ListaAbundante(Limite::Integer)
    lista = Integer[]
    for i=1:Limite
        if (esAbundante(i))
            push!(lista,i)
        end
    end
    return lista
end

function sumaPerfecta(Limite::Integer)
    lista = Integer[]
    for i=1:Limite
        if(esPerfecto(i))
            push!(lista,i)
        end
    end
    return sum(lista)
end

function sumaDeficiente(Limite::Integer)
    lista = Integer[]
    for i=1:Limite
        if (esDeficiente(i))
            push!(lista,i)
        end
    end
    return sum(lista)
end
