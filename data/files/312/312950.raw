#! /usr/bin/julia

# Rosetta Code, Integer overflow

s = subtypes(Signed)
u = subtypes(Unsigned)

println("Integer Type Limits")
for i in 1:length(s)
    println(s[i], " [", typemin(s[i]), ", ", typemax(s[i]), "]")
    println(u[i], " [", typemin(u[i]), ", ", typemax(u[i]), "]")
end

println()
println("Add to typemax")
for t in s
    over = typemax(t) + 1
    println(t, " => ", over, " (", typeof(over), ")")
end
