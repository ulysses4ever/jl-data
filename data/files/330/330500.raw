#Generate Summary Plots
using Mamba, Gadfly

function summaryPlots(sim::Mamba.Chains)

  proteinIntensityVariables = filter(s->contains(s,"logProteinIntensity"),sim.names)

  plots = Array{Gadfly.Plot}()

  for v in proteinIntensityVariables
    p = Mamba.plot(x=sim[:,v,:],)
    push!(plots,p)
