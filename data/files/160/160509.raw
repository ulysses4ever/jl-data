using JaynesCummings
using Base.Test

N = 12
ω_q = 2*pi*6.57E9
ω_r = ω_q
g = 0.5*2*pi*19E6
t_f = 500E-9
t_samples = 300
w_samples = 10

include("comparison.jl")

# Test state generation
# Simple case, |g,1>+1im|g,3>
state1 = gen_initialstate(N,["|g,1>","1im|g,3>"])
@test ishermitian(state1)
@test sum(diag(state1)) ≈ 1
@test state1[2,2] ≈ 0.5
@test state1[4,4] ≈ 0.5
@test state1[2,4] ≈ -0.5im
@test state1[4,2] ≈ 0.5im
# More complex case
state2 = gen_initialstate(N,["|g,0>","exp(π/3im)|g,3>","0.5im|g,4>","-3.25|g,7>"])
@test ishermitian(state2)
@test sum(diag(state2)) ≈ 1
ketmag = (1+1+0.5^2+3.25^2)
@test state2[1,1] ≈ 1/ketmag
@test state2[4,4] ≈ 1/ketmag
@test state2[5,5] ≈ 0.5^2/ketmag
@test state2[8,8] ≈ 3.25^2/ketmag
@test state2[1,4] ≈ exp(π/3im)'/ketmag
@test state2[1,5] ≈ -0.5im/ketmag
@test state2[1,8] ≈ -3.25/ketmag
@test state2[4,5] ≈ (exp(π/3im)*-0.5im)/ketmag
@test state2[5,4] ≈ (exp(π/3im)'*0.5im)/ketmag

# State for next tests
ρ = gen_initialstate(N,["|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","-1.6|g,6>"])
@test ρ ≈ good_initialstate

H = gen_hamiltonian(N,ω_q,ω_r,g)
@test H ≈ good_hamiltonian

times, U_array = gen_timeevoarray(H,t_f,t_samples)
@test times ≈ (0:t_samples-1)*t_f/t_samples
@test U_array[10] ≈ good_time_evo_array_10

e_prob = calc_qubittimeevo(ρ,U_array)
@test e_prob[15] ≈ good_excited_prob_15

photons = calc_photonnumbers(N,g,times,e_prob)
@test photons ≈ good_photons

ρ_resonator = calc_densitymatrix_resonator(ρ,g,times,U_array)
@test ρ_resonator ≈ partialtrace(ρ,[2,N],1)

W = calc_wignerfunction_resonator(ρ,g,times,U_array,w_samples)
@test W ≈ calc_wignerfunction_resonator(ρ_resonator,w_samples)

println("Tests passed.")
#println("Now benchmarking...")
#include("perf/bench.jl")
