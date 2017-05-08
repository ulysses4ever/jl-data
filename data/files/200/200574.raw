# XBraid.jl: Wrapper around the XBraid library (https://computation.llnl.gov/project/parallel-time-integration/software.php)
module XBraid
if isfile(joinpath(dirname(dirname(@__FILE__)), "deps", "deps.jl"))
    include(joinpath(dirname(dirname(@__FILE__)), "deps", "deps.jl"))
else
    error("XBraid not properly installed. Please run Pkg.build(\"XBraid\")")
end

end # module
