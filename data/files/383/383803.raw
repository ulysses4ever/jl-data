function perturbInitialConditions(x, percentageperturb)
  selectedindexes = collect(1:56)
  for j in selectedindexes
    p = 2*(.5-rand())*x[j]*percentageperturb
    x[j]=x[j]+p
    @show x[j]
  end
  return x
end
