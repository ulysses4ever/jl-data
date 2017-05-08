using JaynesCummings
using Base.Test
const TOL = 5E-11
cutoffN = 12
qubit_freq = 2*pi*6.57E9
resonator_freq = qubit_freq
coupling_freq = 0.5*2*pi*19E6
finalTime = 500E-9
samples = 300

include("comparison.jl")

# Test state generation
initialstate = gen_initialstate(cutoffN,["|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","-1.6|g,6>"])
@test initialstate == good_initialstate

hamiltonian = gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN,0)
@test hamiltonian == good_hamiltonian

time_vec, time_evo_array = gen_timeevoarray(hamiltonian,finalTime,samples)
@test time_vec == good_time_vec
@test maximum(abs(time_evo_array[10] - good_time_evo_array_10)) < TOL

excited_prob = calc_qubittimeevo(initialstate,time_evo_array) # Calculate the excited probability of the qubit as a function of time
@test_approx_eq excited_prob[15] good_excited_prob_15

photons = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
@test maximum(abs(photons - good_photons)) < TOL

densitymatrix = calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
@test maximum(abs(densitymatrix - good_densitymatrix)) < TOL

println("Tests passed.")
#println("Now benchmarking...")
#include("perf/bench.jl")
