# Performance comparison of various methods to sample from a truncated normal

# plot performance for each upper bound b over lower bounds a < b
const plot_results = true

using Distributions
using DataFrames

if plot_results
    using Gadfly
end

include("../src/randtn.jl")
include("../src/randtn_other.jl")

function randtime(f::Function, d::Distribution, n::Int)
    f(d)
    gc_disable()
    t = @elapsed for i = 1:n
        f(d)
    end
    gc_enable()
    gc()
    t
end

# run tests for different upper bounds b for all lower bounds a < b
const anum = 100
const amin = -2.5
const amax = 4.0
const bs = [tnzig_xmin - 0.1, tnzig_xmin + 0.1, 
            tnzig_xmax - 0.1, tnzig_xmax + 0.1, Inf]
const nsamples = 10^6

const testfns = [randtn, randtn_robert, randtn_invcdf]
const testids = [:chopin, :robert, :invcdf]

for i = 1:length(bs)
    b = bs[i]
    println("upper bound b = ", b)
    as = linspace(amin, min(b - 0.01, amax), anum)
    df = DataFrame([Float64, Float64, Symbol], [:a, :t, :algo], anum * length(testfns))
    for j = 1:length(testfns)
        testfn = testfns[j]
        testid = testids[j]
        print("Testing ", string(testid))
        for k = 1:anum
            d = TruncatedNormal(0, 1, as[k], b)
            l = (j-1) * anum + k
            df[l, :a] = as[k]
            df[l, :t] = randtime(testfn, d, nsamples)
            df[l, :algo] = testid
        end
        println(", <t> = ", mean(df[((j-1)*anum+1):(j*anum), :t]))
    end
    if plot_results
        bfmt = @sprintf("b = %5.3f", b)
        p = plot(df, x="a", y="t", color="algo", Geom.line, Guide.title(bfmt))
        draw(PDF("randtn_perf_b$bfmt.pdf", 15cm, 10cm), p)
    end
end
