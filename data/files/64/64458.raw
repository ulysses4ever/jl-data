module FixedArrayBench
# TODO, make everything work automatically and save history!

using BenchmarkTools
import FixedSizeArrays
import SIMD
import StaticArrays

include("missing_ops.jl")
const suite = BenchmarkGroup()
include("matrix.jl")
include("vector.jl")
# Define a parent BenchmarkGroup to contain our suite

function run(tunecache=true)
    vector_bench()
    if tunecache && isfile("params.jld")
        loadparams!(suite, JLD.load("params.jld", "suite"), :evals, :samples)
    else
        println("tuning...")
        tune!(suite)
        println("done tuning")
    end
    result = BenchmarkTools.run(suite)
    #JLD.save("result$(Dates.format(now(), "yyudH")).jld", "suite", result)
    result
end


end # module
