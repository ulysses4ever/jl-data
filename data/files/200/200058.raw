
function makeLtri(x)
    l = length(x)
    p = round(Int, (sqrt(1 + 8l) - 1) / 2)
    L = zeros(eltype(x), (p, p))
    k = 1
    for j in 1:p
        for i in j:p
            L[i, j] = x[k]
            k += 1
        end
    end
    L
end

function getLtri(L)
    p, q = size(L)
    x = zeros(eltype(L), (round(Int, p * (p + 1) / 2),))
    k = 1
    for j in 1:p
        for i in j:p
            x[k] = L[i, j]
            k += 1
        end
    end
    x
end
