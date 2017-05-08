#! /usr/bin/julia

# Rosetta Code, AKS test for primes

function polycoefs(n::Int64)
    pc = typeof(n)[]
    if n < 0
        return pc
    end
    sgn = one(n)
    for k in n:-1:0
        push!(pc, sgn*binomial(n, k))
        sgn = -sgn
    end
    return pc
end

function stringpoly(n::Int64)
    if n < 0
        return ""
    end
    st = @sprintf "(x - 1)^{%d} & = & " n
    for (i, c) in enumerate(polycoefs(n))
        if i == 1
            op = ""
            ac = c
        elseif c < 0
            op = "-"
            ac = abs(c)
        else
            op = "+"
            ac = abs(c)
        end
        p = n + 1 - i
        if p == 0
            st *= @sprintf " %s %d\\\\" op ac
        elseif ac == 1
            st *= @sprintf " %s x^{%d}" op p
        else
            st *= @sprintf " %s %dx^{%d}" op ac p
        end
    end
    return st
end

function isaksprime(n::Int64)
    if n < 2
        return false
    end
    for c in polycoefs(n)[2:(end-1)]
        if c%n != 0
            return false
        end
    end
    return true
end

println("<math>")
println("\\begin{array}{lcl}")
for i in 0:10
    println(stringpoly(i))
end
println("\\end{array}")
println("</math>\n")

L = 50
print("AKS primes less than ", L, ":  ")
sep = ""
for i in 1:L  
    if isaksprime(i)
        print(sep, i)
        sep = ", "
    end
end
println()
