using XPP
using PyPlot

include("00a_models.jl")
include("00b_styles.jl")
include("00c_helperfunctions.jl")

################################################################################
#                                                                              #
#       MODEL DEFINITION                                                       #
#                                                                              #
################################################################################

global total_time = 10000000
global inhib = 0.75

M = tev("stochastic")
M.spec["total"] = total_time


################################################################################
#                                                                              #
#       SIMULATIONS                                                            #
#                                                                              #
################################################################################

#run regular simulation to find the value for t corresponding to the desired value of "tr"
runSimulation!(M, "time")

t1 = find_t_for_tr(M, "time", 10)
t2 = total_time - t1

pars2 = deepcopy(M.pars)
pars2["RO"] = calculateInhibition(0.75)
continueSim!(M, t1, t2, "add RO after t1", pars2)

M.pars["RO"] = calculateInhibition(0.75)
runSimulation!(M, "RO from beginning")


################################################################################
#                                                                              #
#       PLOTTING                                                               #
#                                                                              #
################################################################################


figure()
simname = "RO from beginning"
plot(M.sims[simname].D["tr"], get_aKT(M, simname, "uKTtot"), color = "#601a5b", alpha = 1, linestyle = "-", linewidth = 2, label = "CDK-Inhibition (25%)")

# simname = "add RO after t1"
# plot(M.sims[simname].D["tr"], get_aKT(M, simname, "uKTtot"), color = "#431a60", alpha = 1, linestyle = "-", linewidth = 2, label = "CDK-Inhibition after 10 minutes")

simname = "add RO after t1_1"
plot(M.sims[simname].D["tr"], get_aKT(M, simname, "uKTtot"), color = "k", alpha = 0.5, linestyle = "-", linewidth = 2, label = "no CDK-Inhibition")

xlim(0,60)
title("Simulated Attachment Profiles in Cohesion-Depletion", fonts["subplt_title"])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,110)
yticks([0,20, 40, 60, 80, 100])
ylabel("attachment (%)", fonts["subplt_axis"])
legend(loc = 4)
savefig(pwd()*"/plots/inhibition_attachment.pdf")
