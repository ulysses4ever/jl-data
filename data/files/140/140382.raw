#Push module load path to julia pathenv
#push!(LOAD_PATH, "C:/Users/theplankt/Desktop/LEVLAB summer14/Julia/Julia/")

using Types, Constants, Rect

include("Types.jl");
include("Constants.jl");
include("Rect.jl");

include("sub_functions.jl");
include("sub_init.jl");
include("sub_routines.jl");
include("Experiments.jl");

println("Libraries loaded: working:")

@time CPUE,Tau = sim_simple()
println(CPUE)
println(Tau)
