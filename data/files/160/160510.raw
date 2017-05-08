using Gadfly
import JaynesCummings

cutoffN = 12;  #cutoffN should be at least max(n)+1; where max(n) is the highest resonator initial state
qubit_freq = 2*pi*6.57E9;
resonator_freq = qubit_freq;
coupling_freq = 0.5*2*pi*19E6;
finalTime = 500E-9; # final evolution time in sec
samples = 300; # number of data points in time evolution
wignerSamples = 50; # number of points for the Wigner function 1D sampling (since the function is 2D, total number of points is wignerSamples^2)

initialstate = JaynesCummings.gen_initialstate(cutoffN,"|g,0>","0.707106781+0.907106781im|g,3>","1.6025403-0.5im|g,4>","1.6|g,6>") # Generate the initial state and the hamiltonian
hamiltonian = JaynesCummings.gen_hamiltonian(qubit_freq,resonator_freq,coupling_freq,cutoffN,0)

time_vec, excited_prob, time_evo_array = JaynesCummings.calc_qubittimeevo(initialstate,hamiltonian,finalTime,samples) # Calculate the excited probability of the qubit as a function of time
timeEvoPlot = plot(x=time_vec*10E9,y=real(excited_prob),Geom.line,Guide.xlabel("Time (ns)"),Guide.ylabel("Excited State Probability")) # Plot it

photons = JaynesCummings.calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq)
photonPlot = plot(x=0:(cutoffN-1),y=photons,Geom.bar,Guide.xlabel("Photon number"),Guide.ylabel("P<sub>n<\sub>"),Scale.x_discrete)

densityMatrix = @profile JaynesCummings.calc_densitymatrix_resonator(cutoffN,hamiltonian,coupling_freq,initialstate,time_vec,time_evo_array)
# Plotting the density matrix
JaynesCummings.plot_densitymatrix(densityMatrix)

test = @time JaynesCummings.calc_wignerfunction_resonator(cutoffN,wignerSamples,hamiltonian,coupling_freq,initialstate,time_vec,time_evo_array)