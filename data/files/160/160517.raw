module JaynesCummings
using LsqFit, PlotlyJS

global const h_bar = 1.05457173E-34 # in Joules*seconds

export gen_initialstate, gen_hamiltonian, gen_displacementop, gen_timeevoarray,
calc_qubittimeevo, calc_photonnumbers,calc_densitymatrix_resonator,  calc_wignerfunction_resonator,
plot_qubittimeevo, plot_photonnumbers, plot_densitymatrix, plot_wignerfunction,
partialtrace, a, a_dagger

include("generation.jl")
include("calculation.jl")
include("plotting.jl")

function partialtrace(rho,dimOfSubsystemToKeep)
    # First check if the density matrix is Hermitian
    if maximum(abs(rho'-rho))>8E-15
        error("This density matrix is not Hermitian!")
    end

    dimOfSubsystemToTraceOut = div(size(rho)[1] , dimOfSubsystemToKeep)

    matrix = zeros(Complex128,dimOfSubsystemToKeep,dimOfSubsystemToKeep)

    for i=1:dimOfSubsystemToTraceOut
        vector = zeros(Complex128,dimOfSubsystemToTraceOut,1)
        vector[i] = 1
        fullVector = kron(eye(dimOfSubsystemToKeep),vector)
        matrix = matrix + fullVector' * rho * fullVector
    end

    return matrix
end


function a(cutoffN) # Truncated matrix for the lowering operator
    out = zeros(Complex128,cutoffN,cutoffN)
    for i = 1:cutoffN-1
        out[i,i+1] = sqrt(i)
    end
    return out
end


function a_dagger(cutoffN) # Truncated matrix for the raising operator
    out = zeros(Complex128,cutoffN,cutoffN)
    for i = 1:cutoffN-1
        out[i+1,i] = sqrt(i)
    end
    return out
end

end
