function vonNeumann(Hamiltonian,initialMatrix,t)
  # The von Neumann equation describes the time evolution of a density
  # matrix. The von Neumann equation is:
  # i \hbar \frac{\partial \rho}{\partial t} = [H,\rho]
  # If the Hamiltonia is time indepedent, the solution is:
  # \rho(t) = e^{-i H t/\hbar} \rho(0) e^{i H t/\hbar}

  hBar = 1 #1.05457173E-34; # in Joules*seconds

  timeEvo = expm(-1im * Hamiltonian * t / hBar)

  return timeEvo * initialMatrix * timeEvo'
end
