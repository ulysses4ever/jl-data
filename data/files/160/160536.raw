function calc_wignerfunction_resonator(cutoffN,wignerSamples,coupling_freq,initialstate,time_vec,time_evo_array)
  # Solving for the Wigner Function from photon number distributions
  wigner=zeros(Float64,wignerSamples,wignerSamples)
  parityMatrix=ones(Float64,cutoffN,1);parityMatrix[2:2:cutoffN]=-1;
  #
  for realIndex=1:wignerSamples
    for imagIndex=1:wignerSamples
      displacement_operator = kron(eye(2),gen_displacementop((realIndex-wignerSamples/2)/10 + 1im*(imagIndex-wignerSamples/2)/10,cutoffN)) # generating the displacement operator for angle m
      # For each displaced state, we first find the photon number distribution
      excited_prob = calc_qubittimeevo(displacement_operator'*initialstate*displacement_operator,time_evo_array)
      photon_numbers = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq) # solving for the displaced state photon number distributions
      # We then fill the corresponding entry in the winger function array
      wigner[imagIndex,realIndex] = 2/pi * sum(parityMatrix .* photon_numbers);
    end
  end
  return wigner
end