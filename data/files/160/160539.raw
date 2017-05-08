function gen_displacementop(alpha,cutoffN)
  # Generates the displacement operator for a qubit and resonator system
  # (only displaces the resonator, the identity is tensored in for the
  # qubit).
  expm( alpha .* a_dagger(cutoffN) - alpha' .* a(cutoffN) )
end
