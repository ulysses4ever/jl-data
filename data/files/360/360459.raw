#----------------------------------------------------------------------
# Test name: bench_det
#
# Determinants of LU factorizations (which is also where
# you end up if you take a determinant of a matrix)
# used some vectorized methods which was slow,
# especially for small matrices.
#
# PR: https://github.com/JuliaLang/julia/pull/12460
#
# Parameters:
# F - an LU factorization
#----------------------------------------------------------------------

using Benchmarks

function setup(n)
    A = rand(n,n)
    F = lufact(A)
    return F
end

function bench_det(F)
    det(F)
end

F = setup(4)
r = @benchmark bench_det(F)
println(r)

F = setup(100)
r = @benchmark bench_det(F)
println(r)
