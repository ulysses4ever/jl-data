using JaynesCummings
using Base.Test

cutoffN = 12
qubit_freq = 2*pi*6.57E9
resonator_freq = qubit_freq
coupling_freq = 0.5*2*pi*19E6
finalTime = 500E-9
samples = 300

include("comparison.jl")

# Test state generation
# Simple case, |g,1>+1im|g,3>
state1 = gen_initialstate(cutoffN,["|g,1>","1im|g,3>"])
@test ishermitian(state1)
@test sum(diag(state1)) ≈ 1
@test state1[2,2] ≈ 0.5
@test state1[4,4] ≈ 0.5
@test state1[2,4] ≈ -0.5im
@test state1[4,2] ≈ 0.5im
# More complex case
state2 = gen_initialstate(cutoffN,["|g,0>","exp(π/3im)|g,3>","0.5im|g,4>","-3.25|g,7>"])
@test ishermitian(state2)
@test sum(diag(state2)) ≈ 1
norm = (1+1+0.5^2+3.25^2)
@test state2[1,1] ≈ 1/norm
@test state2[4,4] ≈ 1/norm
@test state2[5,5] ≈ 0.5^2/norm
@test state2[8,8] ≈ 3.25^2/norm
@test state2[1,4] ≈ exp(π/3im)'/norm
@test state2[1,5] ≈ -0.5im/norm
@test state2[1,8] ≈ -3.25/norm
@test state2[4,5] ≈ (exp(π/3im)*-0.5im)/norm
@test state2[5,4] ≈ (exp(π/3im)'*0.5im)/norm

# State for next tests
initialstate = gen_initialstate(cutoffN,["|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","-1.6|g,6>"])
@test initialstate ≈ good_initialstate

hamiltonian = gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN)
@test hamiltonian ≈ good_hamiltonian

time_vec, time_evo_array = gen_timeevoarray(hamiltonian,finalTime,samples)
@test time_vec ≈ good_time_vec
@test time_evo_array[10] ≈ good_time_evo_array_10

excited_prob = calc_qubittimeevo(initialstate,time_evo_array) # Calculate the excited probability of the qubit as a function of time
@test excited_prob[15] ≈ good_excited_prob_15

photons = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
@test photons ≈ good_photons

densitymatrix = calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
@test densitymatrix ≈ good_densitymatrix

println("Tests passed.")
#println("Now benchmarking...")
#include("perf/bench.jl")
