using XPP
using PyPlot

include("00a_models.jl")
include("00b_styles.jl")
include("00c_helperfunctions.jl")

global thres = 0.1

################################################################################
#                                                                              #
#       FUNCTION TO LOAD MODELS AND SIMUALTE                                   #
#                                                                              #
################################################################################

function cdki(M, activities, condition)
    model = M[condition]
    timing = []
    for p in activities
        simname = "CDK-Inhibition_$p\_actvity"
        println(condition * "_" * simname)
        println("-" ^30)
        restoreModel!(model)
        model.pars["RO"] = calculateInhibition(p)
        runSimulation!(model, simname)
        try
            timing = [[timing], [thresholdCrossing(model.sims[simname].D["t"], model.sims[simname].D["CycB"], "CycB", thres)]]
        end
        println("="^30)
    end
    return(timing)
end


M = Dict([
    "Control" => ctrl("deterministic"),
    "TEV" => tev("deterministic"),
    "Colchicine" => colchicine("deterministic")
])

#Make Checkpoints
for m in keys(M)
   checkpoint!(M[m])
end


#WT + CDK-Inhibition
activities = [0:0.1:1]

################################################################################
#                                                                              #
#       PLOTTING FUNCTIONS                                                     #
#                                                                              #
################################################################################

tev_timings = cdki(M, activities, "Control")
wt_timings = cdki(M, activities, "TEV")
colch_timings = cdki(M, activities, "Colchicine")

figure(figsize = (8,12))
ax1 = subplot2grid([2,1], [0,0], 1, 1)
title("Simulated Sensitivity of Timing towards CDK-Inhibition", fonts["subplt_title"])
xlabel("residual CDK-activity (%)", fonts["subplt_axis"])
ylabel("time (min)", fonts["subplt_axis"])
plot(activities*100, wt_timings, label = "Control", linewidth = 2)
plot(activities*100, tev_timings, label = "TEV", linewidth = 2)
plot(activities[1:length(colch_timings)]*100, colch_timings, label = "Colchicine", linewidth = 2)
ylim([0,330])
yticks([0, 50, 100, 150, 200, 250, 300])
legend(loc = 2)
# savefig(pwd()*"/plots/timing_10%_absolute.pdf")
# close()


#Normalise
tev_timings = (tev_timings - minimum(tev_timings))/(maximum(tev_timings) - minimum(tev_timings))
wt_timings = (wt_timings - minimum(wt_timings))/(maximum(wt_timings) - minimum(wt_timings))
colch_timings = (colch_timings - minimum(colch_timings))/(maximum(colch_timings) - minimum(colch_timings))

ax2 = subplot2grid([2,1], [1,0], 1, 1)
title("Simulated Sensitivity of Timing towards CDK-Inhibition", fonts["subplt_title"])
xlabel("residual CDK-activity (%)", fonts["subplt_axis"])
ylabel("timing relative (rescaled)", fonts["subplt_axis"])
plot(activities*100, wt_timings, label = "Control", linewidth = 2)
plot(activities*100, tev_timings, label = "TEV", linewidth = 2)
plot(activities[1:length(colch_timings)]*100, colch_timings, label = "Colchicine", linewidth = 2)
ylim([0,1.1])
yticks([0,0.25, 0.50, 0.75, 1.00])
legend(loc = 2)
subplots_adjust(left = 0.12, right = 0.93, hspace = 0.33, wspace = 0.10, top = 0.90, bottom = 0.10)
savefig(pwd()*"/plots/timing_10%.pdf")
close()
