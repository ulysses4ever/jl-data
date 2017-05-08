using PyPlot
using PyCall
@pyimport numpy as np

PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]

Rate_m = readdlm("Sens/Rate_m")
Rate_s = readdlm("Sens/Rate_s")/sqrt(180)
Rate_labels = readdlm("Rate_labels")
width = 1
a = [1:2:2*length(Rate_m);]
threshold = 0.05*ones(a)
PyPlot.matplotlib[:rc]("text",usetex=true)
fig,ax = plt[:subplots](figsize=(15,7))
b = ax[:bar](a,Rate_m,width,align="center",yerr=Rate_s,ecolor="black",color="black")
ax[:set_xticks]([])
ax[:set_xticklabels](Rate_labels)
plt[:margins](0.002)
plt[:ylim]([-0.3,0.8])
plt[:yticks]([-0.3:.1:0.8],fontsize=20)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")
#ax[:set_title]("Rate constants")
a1 = a[5:5:end]
a2 = 5:5:length(a)
plt[:xticks](a1,a2)

Sat_m = readdlm("Sens/Sat_m")
Sat_s = readdlm("Sens/Sat_s")/sqrt(180)
Sat_labels = readdlm("Sat_labels")
width = 1
a = [1:2:2*length(Sat_m);]
threshold = 0.05*ones(a)
PyPlot.matplotlib[:rc]("text",usetex=true)
fig,ax = plt[:subplots](figsize=(15,7))
b = ax[:bar](a,Sat_m,width,align="center",yerr=Sat_s,ecolor="black",color="black")
ax[:set_xticks]([])
ax[:set_xticklabels](Sat_labels)
plt[:margins](0.002)
plt[:ylim]([-0.4,0.1])
plt[:yticks]([-0.4:.1:0.1],fontsize=20)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")
#ax[:set_title]("Sat constants")
a1 = a[20:20:end]
a2 = 20:20:length(a)
plt[:xticks](a1,a2)

Cont_m = readdlm("Sens/Cont_m")
Cont_s = readdlm("Sens/Cont_s")/sqrt(180)
Cont_labels = readdlm("Cont_labels")
width = 1
a = [1:2:2*length(Cont_m);]
threshold = 0.05*ones(a)
PyPlot.matplotlib[:rc]("text",usetex=true)
fig,ax = plt[:subplots](figsize=(15,7))
b = ax[:bar](a,Cont_m,width,align="center",yerr=Cont_s,ecolor="black",color="black")
ax[:set_xticks]([])
#ax[:set_xticklabels](Cont_labels)
plt[:margins](0.002)
plt[:ylim]([-.02,.02])
plt[:yticks]([-.02:.01:.02],fontsize=20)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")
#ax[:set_title]("Control constants")
a1 = a[1:1:end]
a2 = 1:1:length(a)
plt[:xticks](a1,a2)






