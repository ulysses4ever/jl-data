#----------------------------------------------------------------------
# Test name: dense_sparse_mul
#
# Matrix multiplication between dense and sparse
# matrices was slow because it was not using inbounds
# and didn't hoist the loading of field access
#
# PR: https://github.com/JuliaLang/julia/pull/12689
#
# Parameters:
# A dense matrix
# B sparse matrix
#----------------------------------------------------------------------

using Benchmarks

function bench_dense_sparse_mul(A, B)
        A * B
end

A = rand(20, 300)
B = sprand(300, 10^4, 10/10^4);
r = @benchmark bench_dense_sparse_mul(A, B)
println(r)
