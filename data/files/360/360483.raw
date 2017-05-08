#----------------------------------------------------------------------
# Test name: split
#
# split/search was doing excessive allocation
# Issue: https://github.com/JuliaLang/julia/issues/12520
#
# Parameters:
# n         log10 size of the string to split through
#----------------------------------------------------------------------

using Benchmarks

function bench_split(n)
    s = string(rand(1:10000, 1, 10^n))
    r = @benchmark split(s)
end

r = bench_split(8)
println(r)