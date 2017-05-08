using PyPlot

coeff = readdlm("coeff")

Sensitivity = coeff[:,2:end]

Sens = zeros(0,20)
for i in 1:size(Sensitivity,1)
    tmp = Sensitivity[i,2:end]/Sensitivity[i,1]
    Sens = [Sens;tmp]
end

Sensitivity = Sens'

# Plot the bar graph with fixed width of the bar
width = 1
a = [1:4:4*length(Sensitivity[:,1]);]
threshold = 0.05*ones(a)
PyPlot.matplotlib[:rc]("text",usetex=true)
fig,ax = plt[:subplots](figsize=(15,7))

# Set up the format for presenting each dataset
b_CAT = ax[:bar](a-1,Sensitivity[:,1],width,align="center",color="black",ecolor="black")
b_deGFP = ax[:bar](a-1+width,Sensitivity[:,2],width,align="center",color="#858585",ecolor="black")
b_BMP10 = ax[:bar](a-1+2*width,Sensitivity[:,3],width,align="center",color="lightgrey",ecolor="black")

#b_woAA = ax[:bar](a-1+width,Sensitivity[:,2],yerr=Error[:,2],width,align="center",color="#858585",ecolor="black")
#b_woSyn = ax[:bar](a-1+2*width,Sensitivity[:,3],yerr=Error[:,3],width,align="center",color="lightgrey",ecolor="black")

# Set up the characteristic of the figure
ax[:set_xticks]([])
plt[:margins](0.002)
plt[:ylim]([0,.08])
plt[:yticks]([0:.02:.08],fontsize=20)
plt[:ylabel]("CAT Sensitivity Index",fontsize=20)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")

#plt[:xlabel]("GTP ALA ARG ASN ASP CYS GLU GLN GLY HIS ILE LEU LYS MET PHE PRO SER THR TRP TYR VAL",fontsize=14.5)

x = vec(["ALA" "ARG" "ASN" "ASP" "CYS" "GLU" "GLN" "GLY" "HIS" "ILE" "LEU" "LYS" "MET" "PHE" "PRO" "SER" "THR" "TRP" "TYR" "VAL"]')

a = [1:4:4*length(x);]
ax[:set_xticks](a)
plt[:tick_params](axis="x",which="both",bottom="off",top="off")

ax[:set_xticklabels](x,rotation=70)

