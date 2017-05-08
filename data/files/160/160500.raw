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
@testset "State Generation" begin
    # Simple case, |g,1>+1im|g,3>
    state1 = gen_initialstate(cutoffN,["|g,1>","1im|g,3>"])
    @test ishermitian(state1)
    @test sum(diag(state1)) ≈ 1
    @test state1[2,2] ≈ 0.5
    @test state1[4,4] ≈ 0.5
    @test state1[2,4] ≈ -0.5im
    @test state1[4,2] ≈ 0.5im
    # More complex case
    state2 = gen_initialstate(cutoffN,["|g,0>","exp(π/3im)|g,3>","0.5im|g,4>","-1.6|g,6>"])
    @test ishermitian(state2)
    @test sum(diag(state2)) ≈ 1
    norm = (1+1+0.5^2+1.6^2)
    @test state2[1,1] ≈ 1/norm
    @test state2[4,4] ≈ 1/norm
    @test state2[5,5] ≈ 0.5^2/norm
    @test state2[7,7] ≈ 1.6^2/norm
    @test state2[1,4] ≈ exp(π/3im)'/norm
    @test state2[1,5] ≈ -0.5im/norm
    @test state2[1,7] ≈ -1.6/norm
    @test state2[4,5] ≈ (exp(π/3im)*-0.5im)/norm
    @test state2[5,4] ≈ (exp(π/3im)'*0.5im)/norm
end
initialstate = gen_initialstate(cutoffN,["|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","-1.6|g,6>"])

hamiltonian = gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN,0)
@test hamiltonian == good_hamiltonian

time_vec, time_evo_array = gen_timeevoarray(hamiltonian,finalTime,samples)
@test time_vec == good_time_vec
@test time_evo_array[10] ≈ good_time_evo_array_10

excited_prob = calc_qubittimeevo(initialstate,time_evo_array) # Calculate the excited probability of the qubit as a function of time
@test excited_prob[15] ≈ good_excited_prob_15

photons = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
@test maximum(abs(photons - good_photons)) < TOL

densitymatrix = calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
@test maximum(abs(densitymatrix - good_densitymatrix)) < TOL

println("Tests passed.")
#println("Now benchmarking...")
#include("perf/bench.jl")
