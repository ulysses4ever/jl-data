function calc_photonnumbers(time_vec,excited_prob,cutoffN,coupling_freq)
  # Defining the function to fit (resonator state only)
  fun = "qubitModel(x, p) = 0.5*(1"
  for i=(1:cutoffN).-1
    fun = string(fun,"-p[$(i+1)]*cos($(sqrt(i)*(2*coupling_freq))*x)")
  end
  fun = string(fun,')')
  eval(parse(fun))

  fit = curve_fit(qubitModel, time_vec, excited_prob, ones(Float64,cutoffN)*0.1)
  return fit.param
end