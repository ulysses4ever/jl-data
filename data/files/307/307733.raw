################################################################################
#                                                                              #
#       SCRIPT TO PRODUCE THE PANEL B OF THE SUPPLEMENTARY MODELLING FIGURE    #
#                               MIRKOVIC ET. AL                                #
#                                                                              #
################################################################################

#Load dependencies
using XPP
using PyPlot
include("00a_models.jl")
include("00b_styles.jl")
include("00c_helperfunctions.jl")

#Load data
measured_rates = parseData("rates_clustered.dat")

function plot_exp_rates(measured_rates)
    # scatter(measured_rates["CycB"], measured_rates["rate"])
    errorbar(measured_rates["CycB"],measured_rates["rate"], yerr=measured_rates["SD"], fmt="o", color = "#630505", label = "measured")
end

function run_and_plot_simulation_rates(typ)
    var = "CycB"
    M = tev(typ)
    runSimulation!(M, "Normal")
    R = rates(M, "Normal", var)
    plot(R[var], R["rate"], linewidth = 2, color = styles[var], label = "simulated")
end


fig = figure(figsize = (20,6))


ax1 = subplot2grid([1,3], [0,0], 1, 1)
title("Basic Model", fonts["subplt_title"])
run_and_plot_simulation_rates("stochastic_basic")
plot_exp_rates(measured_rates)
xlabel("CycB", fonts["subplt_axis"])
ylabel("Rate of CycB-degradation", fonts["subplt_axis"])
legend()

ax2 = subplot2grid([1,3], [0,1], 1, 1)
title("SAC-Feedback Model", fonts["subplt_title"])
run_and_plot_simulation_rates("stochastic_sac_only")
plot_exp_rates(measured_rates)
xlabel("CycB", fonts["subplt_axis"])
ylabel("Rate of CycB-degradation)", fonts["subplt_axis"])
legend()

ax3 = subplot2grid([1,3], [0,2], 1, 1)
title("SAC-EC-Feedback Model", fonts["subplt_title"])
run_and_plot_simulation_rates("stochastic")
plot_exp_rates(measured_rates)
xlabel("CycB", fonts["subplt_axis"])
ylabel("Rate of CycB-degradation", fonts["subplt_axis"])
legend()

subplots_adjust(left = 0.06, right = 0.98, hspace = 0.33, wspace = 0.24, top = 0.90, bottom = 0.13)
savefig(pwd() * "/plots/rate_comparison.pdf")
close()
