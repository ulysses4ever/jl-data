cd(Base.source_path()[1:end-11])
using JaynesCummings, BenchmarkTools
include("benchmarkreport.jl")
const jc = JaynesCummings

# Define a parent BenchmarkGroup to contain our suite
const suite = BenchmarkGroup()

# Add some child groups to our benchmark suite.
suite["generation"] = BenchmarkGroup(["hamiltonian,state"])
suite["calculation"] = BenchmarkGroup(["densitymatrix,wignerfunction"])

# Parameters
cutoffN = 6
qubit_freq = 2*pi*6.57E9
resonator_freq = qubit_freq
coupling_freq = 0.5*2*pi*19E6
finalTime = 500E-9
samples = 300
wigner_samples = 5
initket = ["|g,0>","0.707106781+0.907106781im|g,1>","1.6025403-0.5im|g,3>"]

# State generation benchmark
suite["generation"]["initialstate"] = @benchmarkable jc.gen_initialstate($cutoffN,$initket)

# We actually need the state
initialstate = jc.gen_initialstate(cutoffN,initket)

# Hamiltonian generation benchmark
suite["generation"]["hamiltonian"] = @benchmarkable jc.gen_hamiltonian($qubit_freq,$resonator_freq,$coupling_freq,$cutoffN,$0)

# We actually need the hamiltonian
hamiltonian = jc.gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN,0)

# Time evolution operator benchmark
suite["generation"]["timeevo"] = @benchmarkable jc.gen_timeevoarray($hamiltonian,$finalTime,$samples)

# We actually need the operator
time_vec, time_evo_array = jc.gen_timeevoarray(hamiltonian,finalTime,samples)

# Qubit time evolution calculation
suite["calculation"]["qubitetimeevo"] = @benchmarkable jc.calc_qubittimeevo($initialstate,$time_evo_array)

# We need the excited state probability
excited_prob = jc.calc_qubittimeevo(initialstate,time_evo_array)

# Photon number calculation benchmark
suite["calculation"]["photonnum"] = @benchmarkable jc.calc_photonnumbers($time_vec,$real(excited_prob),$cutoffN,$coupling_freq)

# Density matrix calculation benchmark
suite["calculation"]["densitymatrix"] = @benchmarkable jc.calc_densitymatrix_resonator($cutoffN,$coupling_freq,$initialstate,$time_vec,$time_evo_array)

# Wigner function calculation benchmark
suite["calculation"]["wignerfunc"] = @benchmarkable jc.calc_wignerfunction_resonator($cutoffN,$wigner_samples,$coupling_freq,$initialstate,$time_vec,$time_evo_array)

tune!(suite)
results = run(suite)
reportstr = sprint(io -> printreport(io, results))

f = open("results//bench-$(Libc.strftime("%Y%m%d_%H%M%S",time())).md","w")
write(f,reportstr)
close(f)
