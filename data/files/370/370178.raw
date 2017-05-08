#! /usr/bin/julia

# Rosetta Code, Compare a list of strings

function Base.isequal(a::AbstractArray)
    1 < length(a) || return true
    x = a[1]
    for y in a[2:end]
        x == y || return false
    end
    return true
end

function Base.isless(a::AbstractArray)
    1 < length(a) || return true
    for i in 2:length(a)
        a[i-1] < a[i] || return false
    end
    return true
end

tests = {["RC", "RC", "RC"],
         ["RC", "RC", "Rc"],
         ["RA", "RB", "RC"],
         ["RC"],
         ASCIIString[],
         ones(Int64, 4),
         1:4}

for a in tests
    println("\nTesting a = ", a)
    res = isequal(a) ? "are" : "are not"
    println(@sprintf "    The elements of a %s equal." res)
    res = isless(a) ? "are" : "are not"
    println(@sprintf "    The elements of a %s strictly increasing." res)
end
println()
