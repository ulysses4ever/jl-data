require("harmonic.jl")


n0 = 10^8
if length(ARGS) > 0
    n0 = int(ARGS[1])
end

np = nprocs()-1
n = int(n0/np)*np

println("Computing harmonic sum to ", n)

println("In serial")
tic()
s = sharm(n)
toc()
println("result = ", s)

println("In parallel")
tic()
p = pharm(n)
toc()
println("result = ", p)
