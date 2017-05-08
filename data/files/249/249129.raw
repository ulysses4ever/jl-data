module RandTNTest  # separate namespace

using Base.Test
using Distributions
using HypothesisTests

include("../src/randtn.jl")

function testrandtn(a::Real, b::Real, n::Int)
    println("* Sampling from range [", a, ", ", b, "], n=", n)
    d = TruncatedNormal(0, 1, a, b)
    x = Float64[randtn(d) for i = 1:n]
    r = ExactOneSampleKSTest(x, TruncatedNormal(0, 1, a, b))
    p = pvalue(r)
    println("  p = ", p, " (one-sample KS test)")
    if p < 0.05
        println(r)
    end
end

n = 10^7
testrandtn(tnzig_xmin - 1.0, tnzig_xmin - 0.1, n)
testrandtn(tnzig_xmin - 1.0, tnzig_xmin + 0.1, n)
testrandtn(tnzig_xmin - 1.0, tnzig_xmax - 0.1, n)
testrandtn(tnzig_xmin - 1.0, tnzig_xmax + 1.0, n)
testrandtn(tnzig_xmin - 1.0, Inf, n)
testrandtn(tnzig_xmin + 0.1, tnzig_xmax - 0.1, n)
testrandtn(tnzig_xmin + 0.1, tnzig_xmax + 1.0, n)
testrandtn(tnzig_xmin + 0.1, Inf, n)
testrandtn(tnzig_xmax - 0.1, tnzig_xmax + 1.0, n)
testrandtn(tnzig_xmax - 0.1, Inf, n)
testrandtn(tnzig_xmax + 0.1, tnzig_xmax + 1.0, n)
testrandtn(tnzig_xmax + 0.1, Inf, n)

end