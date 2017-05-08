using DataFrames

require("toric.jl")

if length(ARGS) > 0
    const L = int(ARGS[1])
else
    const L = 10
end
if length(ARGS) > 1
    const tries = int(ARGS[2])
else
    const tries = 1000
end
filename = "data_L$L.csv"

code = ToricCode(L)
initialize_code!(code)

results = {}

stepsize = iceil(0.005*2*L*L)
τ = 2*L*L

T_max = min(30, iceil(0.15/(stepsize/τ)))

for T = 0:T_max
    push!(results, run_simulation!(code, T*stepsize, tries))
end

println(0:stepsize/τ:T_max*stepsize/τ)
println(results)

df = DataFrame(time=0:stepsize/τ:T_max*stepsize/τ,
                probability=results, L=L)

writetable(filename, df)
