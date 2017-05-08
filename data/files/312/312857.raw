#! /usr/bin/julia

# Rosetta Code, Carmichael 3 strong pseudoprimes

function carmichael{T<:Integer}(pmax::T)
    0 < pmax || throw(DomainError())
    car = T[]
    for p in primes(pmax)
        for h₃ in 2:(p-1)
            m = (p - 1)*(h₃ + p)
            pmh = mod(-p^2, h₃)
            for Δ in 1:(h₃+p-1)
                m%Δ==0 && Δ%h₃==pmh || continue
                q = div(m, Δ) + 1
                isprime(q) || continue
                r = div((p*q - 1), h₃) + 1
                isprime(r) && mod(q*r, (p-1))==1 || continue
                append!(car, [p, q, r])
            end
        end
    end
    reshape(car, 3, div(length(car), 3))
end

hi = 61
car = carmichael(hi)

curp = 0
tcnt = 0
print("Carmichael 3 (p\u00d7q\u00d7r) Pseudoprimes, up to p = ", hi, ":")
for j in sortperm(1:size(car)[2], by=x->(car[1,x], car[2,x], car[3,x]))
    p, q, r = car[:,j]
    c = prod(car[:,j])
    if p != curp
        curp = p
        print(@sprintf("\n\np = %d\n  ", p))
        tcnt = 0
    end
    if tcnt == 4
        print("\n  ")
        tcnt = 1
    else
        tcnt += 1
    end
    print(@sprintf("p\u00d7%d\u00d7%d = %d  ", q, r, c))
end
println("\n\n", size(car)[2], " results in total.")

    


    


