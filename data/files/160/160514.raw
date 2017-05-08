module JaynesCummings
using LsqFit, PyPlot

global const h_bar = 1.05457173E-34 # in Joules*seconds

export gen_initialstate, gen_hamiltonian, gen_displacementop, gen_timeevoarray,
       calc_qubittimeevo, calc_photonnumbers,
       partialtrace, a, a_dagger, vonNeumann,
       calc_densitymatrix_resonator, plot_densitymatrix,
       calc_wignerfunction_resonator, plot_wignerfunction


include("gen_initialstate.jl")
include("gen_hamiltonian.jl")
include("gen_displacementop.jl")
include("gen_timeevoarray.jl")
include("calc_qubittimeevo.jl")
include("calc_photonnumbers.jl")
include("calc_densitymatrix_resonator.jl")
include("plot_densitymatrix.jl")
include("gen_hamiltonian.jl")
include("vonNeumann.jl")
include("partialtrace.jl")
include("calc_wignerfunction_resonator.jl")
include("plot_wignerfunction.jl")


function a(cutoffN) # Truncated matrix for the lowering operator
  out = zeros(Complex128,cutoffN,cutoffN);
  for i = 1:cutoffN-1
      out[i,i+1] = sqrt(i);
  end
  return out
end


function a_dagger(cutoffN) # Truncated matrix for the raising operator
  out = zeros(Complex128,cutoffN,cutoffN)
  for i = 1:cutoffN-1
    out[i+1,i] = sqrt(i);
  end
  return out
end

end
