function primefactors(n::Integer)
    f = factor(n)
    return sort(collect(keys(f)))
end

function factors(n)
    f = [one(n)]
    for (p,e) in factor(n)
        f = reduce(vcat, f, [f*p^j for j in 1:e])
    end
    return length(f) == 1 ? [one(n), n] : sort!(f)
end

function eulerphi(n::Integer)
    m = n
    for p in primefactors(n::Integer)  # Ciclo a traves de la factorizacion prima.
        m = m - div(m, p)
    end
    return int(round(m))
end

function A(n::Integer)                # Sucesion A usando la formula magica.
        suma = 0
        for j in factors(n)
                    suma += j*eulerphi(j)     
        end
return div(div((n*(1 + suma)),2),n)
end

function S(n::Integer)
        suma2 = 0
        for k=1:n
                suma2 += mod(A(k),999999017)
        end
        return suma2
end

