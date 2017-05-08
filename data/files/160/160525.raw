module JaynesCummings
using Compat

if VERSION < v"0.5.0"
    product(x,y) = reshape(collect(Compat.Iterators.product(x,y)),length(x),length(y))
else
    import Base.product
end

export
gen_initialstate, gen_hamiltonian, gen_displacementop, gen_timeevoarray,
gen_drive_hamiltonian,
calc_qubittimeevo, calc_qubittimeevo_rel, calc_photonnumbers,
calc_densitymatrix_resonator, calc_wignerfunction_resonator,
plot_qubittimeevo, plot_photonnumbers, plot_densitymatrix, plot_wignerfunction,
plot_wignerfunction3d,
partialtrace,
ħ, a, a_dagger, σ_minus, σ_plus, σ_z, qeye, ⊗

include("constants.jl")
include("generation.jl")
include("calculation.jl")


load_plotfuns() = include(joinpath(dirname(@__FILE__),"plotting.jl"))
runtests() = include(joinpath(dirname(dirname(@__FILE__)),"test","runtests.jl"))
runperf() = include(joinpath(dirname(dirname(@__FILE__)),"test","perf","runperf.jl"))

end
