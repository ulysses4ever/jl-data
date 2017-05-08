function vonNeumann(Hamiltonian,initialMatrix,t)
  # The von Neumann equation describes the time evolution of a density
  # matrix. The von Neumann equation is:
  # i \h_bar \frac{\partial \rho}{\partial t} = [H,\rho]
  # If the Hamiltonia is time indepedent, the solution is:
  # \rho(t) = e^{-i H t/\h_bar} \rho(0) e^{i H t/\h_bar}

  global h_bar

  timeEvo = expm(-1im * Hamiltonian * t / h_bar)

  return timeEvo * initialMatrix * timeEvo'
end
