tri(n::Int) = div(n * (n + 1), 2)

function nod(n::Int)
    d = 0
    top = int(√n)
    for i=1:top
        if n % i == 0
            d += 2
        end
    end
    top^2 == n ? d-1 : d
end

function main()
    i = 1
    while true
        nod(tri(i)) >= 500 && break
        i += 1
    end
    println(i)
end
