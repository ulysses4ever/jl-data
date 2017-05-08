#! /usr/bin/julia

# Rosetta Code, N'th

function sprintfordinal{T<:Integer}(n::T)
    const sfixes = ["st", "nd", "rd"]
    0 <= n || throw(ArgumentError("number to be formatted must be ≥ 0, got $n"))
    u = n%10
    t = div(n, 10)%10
    if 3 < u || u == 0 || t == 1
        sf = "th"
    else
        sf = sfixes[u]
    end
    @sprintf "%d%s" n sf
end

println("Tests of ordinal formatting of integers.")
for (i, n) in enumerate(0:25)
    if (i-1)%10 == 0
        print("\n   ")
    end
    print(@sprintf("%7s", sprintfordinal(n)))
end
println()

for (i, n) in enumerate(250:265)
    if (i-1)%10 == 0
        print("\n   ")
    end
    print(@sprintf("%7s", sprintfordinal(n)))
end
println()

for (i, n) in enumerate(1000:1025)
    if (i-1)%10 == 0
        print("\n   ")
    end
    print(@sprintf("%7s", sprintfordinal(n)))
end
println()
