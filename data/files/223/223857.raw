function primesieve(n::Integer)
    if n <= 1
        return Integer[]
    end

    p = [1:2:n]
    q = length(p)
    p[1] = 2
    if n >= 9
        for k = 3:2:isqrt(n)
            if p[(k+1)/2] != 0
                p[(k*k+1)/2:k:q] = 0
            end
        end
    end

    return p[p .> 0]
end

function multiploComun(n::Integer)
    p = primesieve(1000)
    K = 1
    i = 1
    check = true
    limite = sqrt(n)
    a = Integer[1:200]
    while p[i] <= n 
        a[i] = 1
        if check 
            if p[i] <= limite
                a[i] = floor( log(n) / log(p[i]) )
                    
            else 
                check = false 
            end
        end
        K = K * p[i]^ a[i]
        i = i + 1
    end
    return K 
end

println(multiploComun(20))
