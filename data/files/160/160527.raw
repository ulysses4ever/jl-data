function calc_densitymatrix_resonator(cutoffN,coupling_freq,initialstate,time_vec,time_evo_array)
  # Solving for the density matrix from photon number distributions
  theta=0:pi/cutoffN:2*pi-pi/cutoffN # we need 2*cutoffN displacements to get enough linearly independent equations
  alpha=10*(cos(theta) + 1im*sin(theta)) # calculating the alpha values for 2*cutoffN displacements from a circle of unit radius

  photon_numbers=zeros(Float64,length(theta),cutoffN)

  M=zeros(Complex128,length(theta)*cutoffN,cutoffN^2)
  for m=1:length(theta)
    # For each angle/displaced state, we first find the photon number distribution
    # Generating the displacement operator for angle m
    displacement_operator = gen_displacementop(alpha[m],cutoffN) 
    sys_displacement = (kron(eye(2),displacement_operator))
    excited_prob = calc_qubittimeevo(sys_displacement'*initialstate*sys_displacement,time_evo_array)
    # Solving for the displaced state photon number distributions
    photon_numbers[m,:] = calc_photonnumbers(time_vec,real(excited_prob),cutoffN,coupling_freq) 
    # display(m/length(theta)) # very basic "progress bar"
    # We then calculate the displacement operator matrix elements
    for n=1:cutoffN
      for i=1:cutoffN
        for j=1:cutoffN
          # Generating the displacement operator matrix elements
          M[(m-1)*cutoffN+n,(i-1)*cutoffN+j] = convert(Complex128,(displacement_operator'[n,i] * displacement_operator[j,n]))
        end
      end
    end
  end
  # Reshaping the array in a form suitable to solving the system of equations
  photon_numbers=reshape(photon_numbers.',length(theta)*cutoffN,1)
  # Solving the system of equations (very slighly overdetermined, there will
  # be some least square fitting). The system to solve is:
  # photon_numbers = M * densityMatrixElements
  density_matrix = M\photon_numbers; # Vector form of the density matrix (ie the elements are 00, 01, 02, ..., cutoffNcutoffN-1, cutoffNcutoffN)
  density_matrix = reshape(density_matrix,cutoffN,cutoffN).'; # Reshaping the vector into an actual matrix
end