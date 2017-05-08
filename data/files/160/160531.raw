function calc_qubittimeevo(initialstate,time_evo_array)
  excited_prob = zeros(Complex128,length(time_evo_array))

  # Time evolve the system density matrix and "measure" the qubit at each time sample taken. This is done by
  # tracing out the resonator and keeping the excited state entry of the density matrix (ie, entry 2,2 in the matrix)
  for i=1:length(time_evo_array)
    excited_prob[i] = partialtrace(time_evo_array[i] * initialstate * time_evo_array[i]',2)[2,2] 
  end

  return excited_prob
end
