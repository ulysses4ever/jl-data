import JaynesCummings
const jc = JaynesCummings

cutoffN = 18  #cutoffN should be at least max(n)+1; where max(n) is the highest resonator initial state
qubit_freq = 2*pi*6.57E9
resonator_freq = qubit_freq
coupling_freq = 0.5*2*pi*19E6
finalTime = 500E-9 # final evolution time in sec
samples = 300 # number of data points in time evolution
wigner_samples = 50 # number of points for the Wigner function 1D sampling (since the function is 2D, total number of points is wigner_samples^2)
ket = ("|g,0>","0.70710678+0.90710678im|g,3>","1.60254-0.5im|g,4>","-1.6|g,6>")


# Generate the initial state and the hamiltonian
initialstate = jc.gen_initialstate(cutoffN,ket...)
hamiltonian = jc.gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN,0)
time_vec, time_evo_array = jc.gen_timeevoarray(hamiltonian,finalTime,samples)

# Calculate the excited probability of the qubit as a function of time
excited_prob = jc.calc_qubittimeevo(initialstate,time_evo_array)
p1 = jc.plot_qubittimeevo(time_vec,real(excited_prob))
display(p1)

# Calculate the photon numbers in the resonator
photons = jc.calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
p2 = jc.plot_photonnumbers(photons)
display(p2)

# Calculate the density matrix by repeating the above while displacing the resonator
densitymatrix =  jc.calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
p3 = jc.plot_densitymatrix(densitymatrix)
display(p3)

# Calculate the Wigner function
wignerfunction = jc.calc_wignerfunction_resonator(cutoffN,wigner_samples,coupling_freq,initialstate,time_vec,time_evo_array)
p4 = jc.plot_wignerfunction(wignerfunction)
display(p4)
