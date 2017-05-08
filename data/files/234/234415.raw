function evendiv(n::Int, d::Int)
    for i=1:d
        if n % i > 0
            return false
        end
    end
    return true
end


n = 20
d = 20
while true
    if evendiv(n, d)
        println(n)
        break
    end
    n += d
end
