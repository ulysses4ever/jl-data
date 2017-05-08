



function getFrac()
    frac = map(parseint, split(readline(), '/'))
    (frac[1], frac[2])
end


function oldest(frac)
    P, Q = frac
    ratio = P // Q
    p = num(ratio)
    q = den(ratio)
    qfactors = factor(q)
    if !haskey(qfactors, 2) || length(qfactors) > 1
        return -1
    end
    while p > 1
        p = div(p, 2)
        q = div(q, 2)
    end
    factor(q)[2]
end



function solve()
    T = parseint(readline())
    for t in 1:T
        frac = getFrac()
        old = oldest(frac)
        print("Case #$t: ")
        if old != -1
            println(old)
        else
            println("impossible")
        end 
    end
end 


solve()
