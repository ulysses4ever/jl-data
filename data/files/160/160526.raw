function calc_densitymatrix_resonator(cutoffN,hamiltonian,coupling_freq,initialstate,time_vec,time_evo_array)
  # Solving for the density matrix from photon number distributions
  theta=0:pi/cutoffN:2*pi-pi/cutoffN # we need 2*cutoffN displacements to get enough linearly independent equations
  alpha=2*cos(theta) + 1im*2*sin(theta) # calculating the alpha values for 2*cutoffN displacements from a circle of unit radius

  photon_numbers=zeros(Float64,length(theta),cutoffN)

  M=zeros(Complex128,length(theta)*cutoffN,cutoffN^2)
  for m=1:length(theta)
  # For each angle/displaced state, we first find the photon number
  # distribution
    displacementoperator = gen_displacementop(alpha[m],cutoffN); # generating the displacement operator for angle m
    excited_prob = calc_qubittimeevo((kron(eye(2),displacementoperator))'*initialstate*kron(eye(2),displacementoperator),time_evo_array)
    photon_numbers[m,:] = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq) # solving for the displaced state photon number distributions
    # display(m/length(theta)) # very basic "progress bar"
    # We then calculate the displacement operator matrix elements
    for n=1:cutoffN
      for i=1:cutoffN
        for j=1:cutoffN
          nVector=zeros(Complex128,cutoffN,1);nVector[n]=1;
          iVector=zeros(Complex128,cutoffN,1);iVector[i]=1;
          jVector=zeros(Complex128,cutoffN,1);jVector[j]=1;
          M[(m-1)*cutoffN+n,(i-1)*cutoffN+j] = (nVector'*displacementoperator'*iVector * jVector'*displacementoperator*nVector)[1] # Generating the displacement operator matrix elements
        end
      end
    end
  end
  photon_numbers=reshape(photon_numbers.',length(theta)*cutoffN,1); # Reshaping the array in a form suitable to solving the system of equations

  # Solving the system of equations (very slighly overdetermined, there will
  # be some least square fitting). The system to solve is:
  # photon_numbers = M * densityMatrixElements
  density_matrix = M\photon_numbers; # Vector form of the density matrix (ie the elements are 00, 01, 02, ..., cutoffNcutoffN-1, cutoffNcutoffN)
  density_matrix = reshape(density_matrix,cutoffN,cutoffN).'; # Reshaping the vector into an actual matrix
end
