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

global nsims = 10

# #Load models
# M = [
#     "Basic Model" => tev("stochastic_basic"),
#     "SAC-Feedback Model" => tev("stochastic_sac_only"),
#     "SAC-EC-Feedback Model"  => tev("stochastic")
#     ]
#
# #Define range of stretch values to simulate for
# stretch = [0:0.2:1]
#
# #Loop over models
# for model_instance in keys(M)
#     #Run simulations with varying stretch parameter
#     for s in stretch
#         for i in 1:nsims
#             println(model_instance, "\t", s, "\t", i)
#             M[model_instance].spec["seed"] = rand(1:20000000)
#             M[model_instance].spec["total"] = 2000000
#             M[model_instance].pars["Stretch"] = s
#             runSimulation!(M[model_instance], "stretch = $s\_$i")
#         end
#     end
# end

colors_cdk = ["#FBDE75","#ABBD69","#6B9763","#3D6F58","#234744","#142226"]
map_cdk = [s => colors_cdk[i] for (i, s) in enumerate(stretch)]
colors_apc = ["#FBDE75","#ABBD69","#6B9763","#3D6F58","#234744","#142226"]
map_apc = [s => colors_apc[i] for (i, s) in enumerate(stretch)]


#Custom plotting function, since XPPjl's standard plotting function, does not
#deal well with subplots
function plotSim(M, instance, var, stretch, c_map)
    for s in stretch
        for i in 1:nsims
            t = M[instance].sims["stretch = $s\_$i"].D["tr"]
            V = M[instance].sims["stretch = $s\_$i"].D[var]
            c = c_map[s]
            a = 1
            plot(t, V, color = c, alpha = a, linewidth = 2)
        end
    end
end

################################################################################
#                                                                              #
#       PLOTTING FUNCTIONS                                                     #
#                                                                              #
################################################################################

fig = figure(figsize = (20,12))

model_instance = "Basic Model"
ax1 = subplot2grid([2,3], [0,0], 1, 1)
title(model_instance, fonts["subplt_title"])
plotSim(M, model_instance, "CycB", stretch, map_cdk)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of CycB-Molecules", fonts["subplt_axis"])

ax2 = subplot2grid([2,3], [1,0], 1, 1)
plotSim(M, model_instance, "APC", stretch, map_apc)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of free APC-Molecules", fonts["subplt_axis"])

model_instance = "SAC-Feedback Model"
ax3 = subplot2grid([2,3], [0,1], 1, 1)
title(model_instance, fonts["subplt_title"])
plotSim(M, model_instance, "CycB", stretch,map_cdk)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of CycB-Molecules", fonts["subplt_axis"])

ax4 = subplot2grid([2,3], [1,1], 1, 1)
plotSim(M, model_instance, "APC", stretch, map_apc)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of free APC-Molecules", fonts["subplt_axis"])

model_instance = "SAC-EC-Feedback Model"
ax5 = subplot2grid([2,3], [0,2], 1, 1)
title(model_instance, fonts["subplt_title"])
plotSim(M, model_instance, "CycB", stretch, map_cdk)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of CycB-Molecules", fonts["subplt_axis"])

ax6 = subplot2grid([2,3], [1,2], 1, 1)
plotSim(M, model_instance, "APC", stretch, map_apc)
xlim(0,60)
xticks([0,10,20,30, 40])
xlabel("time (min)", fonts["subplt_axis"])
ylim(0,cyc_max)
yticks([0,2500,5000,7500,10000])
ylabel("Number of free APC-Molecules", fonts["subplt_axis"])

subplots_adjust(left = 0.06, right = 0.98, hspace = 0.33, wspace = 0.24, top = 0.90, bottom = 0.13)
savefig(pwd()*"/plots/stretch_sensitivity.pdf")
