using Grisu

max_double = v = 1.7976931348623157e308
function perf(n,v=max_double)
    tic()
    for i = 1:n
        l,p,b,s = Grisu.grisu(v,Grisu.SHORTEST,0)
    end
    a = toq()
    tic()
    for i = 1:n
        l,b,s = Base.Grisu.grisu(v,Base.Grisu.SHORTEST,0)
    end
    b = toq()
    println("Shortest:\n  Native Julia: $a\n  Base.Grisu: $b")
end

perf(1000000,1.0)