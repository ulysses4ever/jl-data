#----------------------------------------------------------------------
# Test name: IS11856_replace
#
# Issue/PR: https://github.com/JuliaLang/julia/issues/11856
#
# Description:
# replace was allocating excessive memory.
# Fixed in https://github.com/JuliaLang/julia/pull/11898
#
# Parameters:
# n         log10 size of the string to search through
#----------------------------------------------------------------------

using Benchmarks

function IS11856_replace(n)
    s = lowercase(randstring(10^n))
    r = @benchmark replace(s,"a","b")
end

r = IS11856_replace(8)
println(r)