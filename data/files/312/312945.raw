#! /usr/bin/julia

# Rosetta Code, Find limit of recursion

function divedivedive()
    global depth
    depth += 1
    divedivedive()
end

function divedivedive(d::Int)
    try
        divedivedive(d+1)
    catch
        return d
    end
end

depth = divedivedive(0)
println("A clean dive reaches a depth of ", depth, ".")

depth = 0
try
    divedivedive()
end
println("A dirty dive reaches a depth of ", depth, ".")
        



