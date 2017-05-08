print("##############################################\n")
print("JaynesCummings.jl Benchmarks - Single Threaded\n")
print("Date: ", Libc.strftime(time()), "\n")
print("Revision:\n")
run(`git rev-parse HEAD`)
print("##############################################\n\n")

versioninfo()
print("\n\n")

# Including the module
using JaynesCummings

# This first run is just used to compile the functions with a basic case
cutoffN = 4
initket = ["|g,1>"]
qubit_freq = 2*pi*6.57E9
resonator_freq = qubit_freq
coupling_freq = 0.5*2*pi*19E6
finalTime = 500E-9
samples = 300
wigner_samples = 10

print("## Execution times for basic case, including build time.\nParameters:\ncutoffN = $cutoffN\nwigner_samples = $wigner_samples\ninitialstate = $initket\n\n")
print("gen_initialstate: ")
initialstate = @time gen_initialstate(cutoffN,initket)
print("gen_hamiltonian: ")
hamiltonian = @time gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN)
print("gen_timeevoarray: ")
time_vec, time_evo_array = @time gen_timeevoarray(hamiltonian,finalTime,samples)
print("calc_qubittimeevo: ")
excited_prob = @time calc_qubittimeevo(initialstate,time_evo_array)
print("calc_photonnumbers: ")
photons = @time calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
print("calc_densitymatrix_resonator: ")
densitymatrix = @time calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
print("calc_wignerfunction_resonator: ")
wignerfunction = @time calc_wignerfunction_resonator(cutoffN,wigner_samples,coupling_freq,initialstate,time_vec,time_evo_array)

# This second run is much more computationally intensive
cutoffN = 32
wigner_samples = 50
initket = ["|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","-1.6|g,6>"]
print("\n\n## Execution times for test case, does NOT include build time.\nParameters:\ncutoffN = $cutoffN\nwigner_samples = $wigner_samples\ninitialstate = $initket\n\n")
print("gen_initialstate: ")
initialstate = @time gen_initialstate(cutoffN,initket)
print("gen_hamiltonian: ")
hamiltonian = @time gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN)
print("gen_timeevoarray: ")
time_vec, time_evo_array = @time gen_timeevoarray(hamiltonian,finalTime,samples)
print("calc_qubittimeevo: ")
excited_prob = @time calc_qubittimeevo(initialstate,time_evo_array)
print("calc_photonnumbers: ")
photons = @time calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
print("calc_densitymatrix_resonator: ")
densitymatrix = @time calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
print("calc_wignerfunction_resonator: ")
wignerfunction = @time calc_wignerfunction_resonator(cutoffN,wigner_samples,coupling_freq,initialstate,time_vec,time_evo_array)
