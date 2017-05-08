module JaynesCummings
using LsqFit, PlotlyJS

import Base.product

export gen_initialstate, gen_hamiltonian, gen_displacementop, gen_timeevoarray,
calc_qubittimeevo, calc_photonnumbers,calc_densitymatrix_resonator,  calc_wignerfunction_resonator,
plot_qubittimeevo, plot_photonnumbers, plot_densitymatrix, plot_wignerfunction,
partialtrace, a, a_dagger, σ_minus, σ_plus, σ_z, qeye, ⊗

include("constants.jl")
include("generation.jl")
include("calculation.jl")
include("plotting.jl")


runtests() = include(joinpath(dirname(dirname(@__FILE__)),"test","runtests.jl"))

end
