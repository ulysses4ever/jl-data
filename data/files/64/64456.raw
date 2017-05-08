__precompile(false)
module FixedArrayBench
# TODO, make everything work automatically and save history!

using BenchmarkTools
import FixedSizeArrays
import SIMD

include("missing_ops.jl")
include("matrix.jl")
include("vector.jl")
# Define a parent BenchmarkGroup to contain our suite
const suite = BenchmarkGroup()

function run(tunecache=true)
  if tunecache
    loadparams!(suite, JLD.load("params.jld", "suite"), :evals, :samples);
  else
    tune!(suite)
  end
  result = run(suite)
  JLD.save("result$(Dates.format(now(), "yyudH")).jld", "suite", result);
end

end # module
