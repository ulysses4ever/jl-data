using Base.Test
using ClusterAnalysis

lbls = vec([1 1 1 2 2 2])
expected = vec([2 2 2 3 3 3])

@test 1.0 == ClusterAnalysis.adjusted_rand_index(lbls, expected)

lbls = vec([1 1 1 2 2 2])
expected = vec([1 2 1 1 2 1])

@test_approx_eq_eps -0.2162 ClusterAnalysis.adjusted_rand_index(lbls, expected) e-2

