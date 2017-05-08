function gen_hamiltonian(omegaQ,omegaR,g,cutoffN,noiseAdded)
  # This function generates a times invariant matrix for the Jaynes-Cummings
  # Hamiltonian. The parameters omegaR, omegaQ and g should be given in
  # rad/s. The cutoffN parameter is the highest energy level of the harmonic
  # oscillator that is considered. Higher levels are truncated.

  # Some constant parameters for the Jaynes-Cummings
  identity = [1 0 ; 0 1]; sigmaZ = [1 0 ; 0 -1];
  sigmaMinus = [0 1 ; 0 0]; sigmaPlus = [0 0 ; 1 0];
  hBar = 1; # 1.05457173E-34; # in Joules*seconds

  # The Jaynes-Cummings Hamiltonian is written with the following
  # conventions: omegaR is the resonator frequency, omegaQ is the qubit
  # frequency and g is the coupling. The resonator Hilbert space is truncated
  # to n = cutoffN, and the ground state of the qubit is given by the vector
  # [1;0] (hence the minus sign before sigmaZ).
  jaynesCummings = zeros(Complex128,2*cutoffN,2*cutoffN)
  jaynesCummings = jaynesCummings +
    hBar * omegaR .* kron(identity,a_dagger(cutoffN)) * kron(identity,a(cutoffN)) -  # harmonic oscillator term
    0.5 .* hBar .* omegaQ .* kron(sigmaZ,eye(cutoffN)) +  # qubit term
    hBar .* g .* ( kron(sigmaPlus,a(cutoffN)) + kron(sigmaMinus,a_dagger(cutoffN)) ); # interaction term

  if noiseAdded==1
    randM = rand(2*cutoffN);
    randomness = 0.005*hBar*g*(randM+randM');
    jaynesCummings = jaynesCummings + randomness;
  end
  return jaynesCummings
end