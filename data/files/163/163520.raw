using PyPlot

y = readdlm("Yield_best")
mean_best = mean(y)
std_best = std(y)

y = readdlm("Yield_KO_cyd")
mean_KO_cyd = mean(y)
std_KO_cyd = std(y)

y = readdlm("Yield_KO_nuo")
mean_KO_nuo = mean(y)
std_KO_nuo = std(y)

y = readdlm("Yield_KO_app")
mean_KO_app = mean(y)
std_KO_app = std(y)

y = readdlm("Yield_KO_all")
mean_KO_all = mean(y)
std_KO_all = std(y)

means = [mean_best mean_KO_app mean_KO_nuo mean_KO_cyd mean_KO_all]'
stds = [std_best std_KO_app std_KO_nuo std_KO_cyd std_KO_all]'

color_array = ["black";"#555555";"#AFAFAF";"#DDDDDD";"white"]

width = 1.8
a = [1:2:2*length(means);]
threshold = 0.05*ones(a)
#PyPlot.matplotlib[:rc]("text",usetex=true)
fig,ax = plt[:subplots](figsize=(4,3))
b = ax[:bar](a,means,width,align="center",yerr=stds,ecolor="black",color=color_array)
ax[:set_xticks]([])
plt[:margins](0.02)
plt[:ylim]([0,.15])
plt[:yticks]([0:.05:.15],fontsize=10)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")



