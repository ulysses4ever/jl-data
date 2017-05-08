#! /usr/bin/julia

# Rosetta Code, Set consolidation

function consolidate{T}(a::Array{Set{T},1})
    1 < length(a) || return a
    b = copy(a)
    c = Set{T}[]
    while 1 < length(b)
        x = shift!(b)
        cme = true
        for (i, y) in enumerate(b)
            !isempty(intersect(x, y)) || continue
            cme = false
            b[i] = union(x, y)
            break
        end
        !cme || push!(c, x)
    end
    push!(c, b[1])
    return c
end

p = Set(["A", "B"])
q = Set(["C", "D"])
r = Set(["B", "D"])
s = Set(["H", "I", "K"])
t = Set(["F", "G", "H"])

println("p = ", p)
println("q = ", q)
println("r = ", r)
println("s = ", s)
println("t = ", t)

println("consolidate([p, q]) =\n    ", consolidate([p, q]))
println("consolidate([p, r]) =\n    ", consolidate([p, r]))
println("consolidate([p, q, r]) =\n    ", consolidate([p, q, r]))
println("consolidate([p, q, r, s, t]) =\n    ",
        consolidate([p, q, r, s, t]))

        
        
