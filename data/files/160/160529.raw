function calc_qubittimeevo(initialstate,hamiltonian,finalTime,samples)
  # Generate the time evolution vector
  time_vec=((1:samples)-1)*finalTime/samples
  excited_prob = zeros(Complex128,length(time_vec))
  temp = zeros(Complex128,2,2);
  time_evo_array = Array(typeof(hamiltonian),samples)

  hBar = 1 #1.05457173E-34; # in Joules*seconds

  # We can now "measure" our qubit at each time sample taken. This is done by
  # tracing out the resonator and keeping the excited state entry of the
  # density matrix
  for i=1:samples
    timeEvo = expm(-1im .* hamiltonian .* time_vec[i] ./ hBar)
    temp = partialtrace(timeEvo * initialstate * timeEvo',2) # trace out the resonator system from the density matrix
    excited_prob[i] = temp[2,2] # only keep the excited state probability (ie, entry 2,2 in the matrix)
    time_evo_array[i] = timeEvo
  end

  return time_vec, excited_prob, time_evo_array
end

function calc_qubittimeevo(initialstate,time_evo_array)
  excited_prob = zeros(Complex128,length(time_evo_array))
  temp = zeros(Complex128,2,2);

  for i=1:length(time_evo_array)
    temp= partialtrace(time_evo_array[i] * initialstate * time_evo_array[i]',2) # trace out the resonator system from the density matrix
    excited_prob[i] = temp[2,2] # only keep the excited state probability (ie, entry 2,2 in the matrix)
  end

  return excited_prob
end
