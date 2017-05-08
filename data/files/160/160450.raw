using BenchmarkTools, JaynesCummings
cd(Base.source_path()[1:end-11])
include("benchmarkreport.jl")

# Define a parent BenchmarkGroup to contain our suite
const suite = BenchmarkGroup()

# Add some child groups to our benchmark suite.
suite["generation"] = BenchmarkGroup(["hamiltonian,state"])
suite["calculation"] = BenchmarkGroup(["densitymatrix,wignerfunction"])

# Parameters
N = 14
ω_q = 2*pi*6.57E9
ω_r = ω_q
g = 0.5*2*pi*19E6
t_f = 200E-9
t_samples = 200
w_samples = 6
ket = ["|g,0>","0.707106781+0.907106781im|g,1>","1.6025403-0.5im|g,3>"]

# State generation benchmark
suite["generation"]["initialstate"] = @benchmarkable gen_initialstate($N,$ket)

# We actually need the state
ρ = gen_initialstate(N,ket)

# Hamiltonian generation benchmark
suite["generation"]["hamiltonian"] = @benchmarkable gen_hamiltonian($N,$ω_q,$ω_r,$g)

# We actually need the hamiltonian
H = gen_hamiltonian(N,ω_q,ω_r,g)

# Time evolution operator benchmark
suite["generation"]["timeevo"] = @benchmarkable gen_timeevoarray($H,$t_f,$t_samples)

# We actually need the operator
times, U_array = gen_timeevoarray(H,t_f,t_samples)

# Qubit time evolution calculation
suite["calculation"]["qubitetimeevo"] = @benchmarkable calc_qubittimeevo($ρ,$U_array)

# We need the excited state probability
e_prob = calc_qubittimeevo(ρ,U_array)

# Photon number calculation benchmark
suite["calculation"]["photonnum"] = @benchmarkable calc_photonnumbers($N,$g,$times,$e_prob)

# Density matrix calculation benchmark
suite["calculation"]["densitymatrix"] = @benchmarkable calc_densitymatrix_resonator($ρ,$g,$times,$U_array)

# Wigner function calculation benchmark
suite["calculation"]["wignerfunc"] = @benchmarkable calc_wignerfunction_resonator($ρ,$g,$times,$U_array,$w_samples)

tune!(suite)
results = run(suite)
reportstr = sprint(io -> printreport(io, results))

f = open("results//bench-$(Libc.strftime("%Y%m%d_%H%M%S",time())).md","w")
write(f,reportstr)
close(f)
