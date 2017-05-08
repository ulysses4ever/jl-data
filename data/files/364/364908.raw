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

global total_time = 2500000
global inhib = 0.75

M = tev("stochastic")
M.spec["total"] = total_time
M.spec["seed"] = rand(1:200000)


################################################################################
#                                                                              #
#       SIMULATIONS                                                            #
#                                                                              #
################################################################################

#run regular simulation to find the value for t corresponding to the desired value of "tr"
runSimulation!(M, "time")

M.pars["RO"] = calculateInhibition(0.65)
runSimulation!(M, "RO from beginning")


################################################################################
#                                                                              #
#       PLOTTING                                                               #
#                                                                              #
################################################################################


figure(figsize = [15,6])
ax1 = subplot2grid([2,1], [0,0], 1, 1)
title("Simulated Attachment Profiles and Rate of MCC-formation in Cohesion-Depletion", fonts["subplt_title"])
simname = "time"
plot(M.sims[simname].D["tr"], M.sims[simname].D["MCCformation "], color = "#288805", alpha = 1, linestyle = "-", linewidth = 2, label = "no CDK-Inhibition")
xlim(0,50)
xlabel("time (min)", fonts["subplt_axis"])

ylim(0,7000)
yticks([0,1200, 2400, 3600, 4800, 6000])
ylabel("MCC formation (min-1)", fonts["subplt_axis"])


ax1_2 = ax1[:twinx]()
plot(M.sims[simname].D["tr"], get_aKT(M, simname, "uKTtot"), color = "#601a5b", alpha = 1, linestyle = "-", linewidth = 2, label = "no CDK-Inhibition")
xlim(0,50)
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,110)
yticks([0,20, 40, 60, 80, 100])
ylabel("attachment (%)", fonts["subplt_axis"])


ax1 = subplot2grid([2,1], [1,0], 1, 1)
simname = "RO from beginning"

plot(M.sims[simname].D["tr"], M.sims[simname].D["MCCformation "], color = "#288805", alpha = 1, linestyle = "-", linewidth = 2, label = "CDK-Inhibition (25%)")
xlim(0,50)
xlabel("time (min)", fonts["subplt_axis"])

ylim(0,7000)
yticks([0,1200, 2400, 3600, 4800, 6000])
ylabel("MCC formation (min-1)", fonts["subplt_axis"])

ax1_2 = ax1[:twinx]()
plot(M.sims[simname].D["tr"], get_aKT(M, simname, "uKTtot"), color = "#601a5b", alpha = 1, linestyle = "-", linewidth = 2, label = "CDK-Inhibition (25%)")
xlim(0,50)
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,110)
yticks([0,20, 40, 60, 80, 100])
ylabel("attachment (%)", fonts["subplt_axis"])


subplots_adjust(left = 0.07, right = 0.93, hspace = 0.4, wspace = 0.10, top = 0.90, bottom = 0.15)
savefig(pwd()*"/plots/inhibition_attachment.pdf")
