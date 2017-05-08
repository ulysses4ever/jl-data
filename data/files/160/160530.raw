function calc_qubittimeevo(initialstate,time_evo_array)
  excited_prob = zeros(Complex128,length(time_evo_array))

  # Time evolve the system density matrix and "measure" the qubit at each time sample taken. This is done by
  # tracing out the resonator and keeping the excited state entry of the density matrix
  for i=1:length(time_evo_array)
    temp= partialtrace(time_evo_array[i] * initialstate * time_evo_array[i]',2) # trace out the resonator system from the density matrix
    excited_prob[i] = temp[2,2] # only keep the excited state probability (ie, entry 2,2 in the matrix)
  end

  return excited_prob
end
