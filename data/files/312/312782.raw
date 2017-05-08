#! /usr/bin/julia

# Rosetta Code, Vampire number

function divisors{T<:Integer}(n::T)
    !isprime(n) || return [one(T), n]
    d = [one(T)]
    for (k, v) in factor(n)
        e = T[k^i for i in 1:v]
        append!(d, vec([i*j for i in d, j in e]))
    end
    sort(d)
end

function vampirefangs{T<:Integer}(n::T)
    fangs = T[]
    isvampire = false
    vdcnt = ndigits(n)
    fdcnt = vdcnt>>1
    iseven(vdcnt) || return (isvampire, fangs)
    !isprime(n) || return (isvampire, fangs)
    vdigs = sort(digits(n))
    d = divisors(n)
    len = length(d)
    len = iseven(len) ? len>>1 : len>>1 + 1
    for f in d[1:len]
        ndigits(f) == fdcnt || continue
        g = div(n, f)
        f%10!=0 || g%10!=0 || continue
        sort([digits(f), digits(g)]) == vdigs || continue
        isvampire = true
        append!(fangs, [f, g])
    end
    if isvampire
        fangs = reshape(fangs, (2,length(fangs)>>1))'
    end
    return (isvampire, fangs)
end

function showvampire{T<:Integer}(i::T, n::T, fangs::Array{T,2})
    s = @sprintf "%6d  %14d %s\n" i n join(fangs[1,:], "\u00d7")
    for i in 2:size(fangs)[1]
        s *= " "^23*join(fangs[i,:], "\u00d7")*"\n"
    end
    return s
end

vgoal = 25
vcnt = 0
dcnt = 0
println("Finding the first ", vgoal, " vampire numbers.")
println("     N         Vampire Fangs")
while vcnt < vgoal
    dcnt += 2
    for i in (10^(dcnt-1)):(10^dcnt-1)
        (isvampire, fangs) = vampirefangs(i)
        isvampire || continue
        vcnt += 1
        print(showvampire(vcnt, i, fangs))
        vcnt < vgoal || break
    end
end

test = [16758243290880, 24959017348650, 14593825548650]
println()
println("Checking a few numbers.")
println("     N         Vampire Fangs")
for (i, v) in enumerate(test)
    (isvampire, fangs) = vampirefangs(v)
    if isvampire
        print(showvampire(i, v, fangs))
    else
        println(@sprintf "%6d  %14d is not a vampire" i v)
    end
end


        
    
    
    
