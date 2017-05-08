include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot

function runModelPlotPretty()
	close("all") #close already open windows
	#set start time, stop time and step sizes
	 tstart=0
	 tend=600
	 step=1.0
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict,1)
	colnum = 1
	numcols = 8
	upperlim =8*18
	offset = 8
	plotcounter = 1
	j = 1
	figure(figsize=(20,20), dpi = 80)
	#plt[:tight_layout]() 
	while(j<=upperlim)
		if(colnum >numcols)
			break
		end
		ax = gca()
		currx = [a[j] for a in x]
		plt[:subplot](18,8,plotcounter)
		plt[:tick_params](axis="both", which="major", labelsize=7)
		plt[:tick_params](axis="both", which="minor", labelsize=7)
		plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,currx ,linewidth=2.0,color = "k")
		@show plotcounter
		#remove axis numbering for columns other than first
		if(colnum !=1)
			ax[:set_yticklabels]([])
		end
		ax[:set_xticklabels]([])
		plotcounter = plotcounter+offset
		j=j+1

		if(plotcounter>=18*8+1)
			colnum = colnum+1
			plotcounter = colnum
		end
	end
	#make axis all the same
	for j in collect(1:8*18)
		plt[:subplot](18,8,j)
		ax = gca()
		if j in collect(1:8) #FII
			ax[:set_ylim]([0,1500])
		elseif j in collect(9:16) #FIIA
			ax[:set_ylim]([0,600]) 
		elseif j in collect(17:24) #PC
			ax[:set_ylim]([50,70])
		elseif j in collect(25:32)#APC
			ax[:set_ylim]([0,5]) 
		elseif j in collect(33:40)#ATIII
			ax[:set_ylim]([0,5000]) 
		elseif j in collect(41:48) #TM
			ax[:set_ylim]([00, 60])
		elseif j in collect(49:56) #Trigger
			ax[:set_ylim]([-.05,6])
		elseif j in collect(57:64) #Fibrin
			ax[:set_ylim]([0,50000])
		elseif j in collect(65:72) #Plasmin
			ax[:set_ylim]([1000,2100])
		elseif j in collect(73:80) #Fibrinogen
			ax[:set_ylim]([0,10000])
		elseif j in collect(81:88) #Plasminogen
			ax[:set_ylim]([0, 2500])
		elseif j in collect(89:96) #tPA
			ax[:set_ylim]([-1,10])
		elseif j in collect(97:104) #uPA
			ax[:set_ylim]([-.02, .05])
		elseif j in collect(105:112)#Fibrin monomer
			ax[:set_ylim]([0,100])
		elseif j in collect(113:120)#protofibril
			ax[:set_ylim]([0,300])
		elseif j in collect(121:128) #antiplasmin
			ax[:set_ylim]([0,2000])
		elseif j in collect(129:136)#PAI_1
			ax[:set_ylim]([-.1,.6])
		elseif j in collect(137:144)
			ax[:set_ylim]([0,4000])
		end
	end


	#label colums
	compartments = ["Veins", "Heart","Lungs", "Arteries", "Kidneys", "Liver","Bulk", "Wound"]
	for j in collect(1:8)
		plt[:subplot](18,8,j)
		title(compartments[j], fontsize=18)
	end

	#label rows
	speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Fibrin", "Plasmin", "Fibrinogen", "Plasminogen", "tPA", "uPA", "Fibrin monomer", "Protofibril monomer", "antiplasmin", "PAI_1", "Fiber","Volume"]
	counter = 1
	for j in collect(8:8:8*18)
		plt[:subplot](18,8,j)
		annotate(speciesnames[counter], xy = [1;1], xytext = [1.02,.8], xycoords = "axes fraction", textcoords = "axes fraction", rotation = "vertical", fontsize = 7)
		counter=counter+1
	end
	savefig(string("output/figs/PrettyLayoutFlowOnBestParamsPatchedProteinC",".pdf"),bbox_inches="tight")
end
