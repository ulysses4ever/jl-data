include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot

function generateData(num_param_sets)
	close("all") #close already open windows
	#set start time, stop time and step sizes
	 tstart=0
	 tend=600
	 step=1.0
	for j in collect(1:num_param_sets)
		println(string("On set ", j," out of ",num_param_sets))
		 data_dict = DataFile(tstart, tend, step)
		 t, x = SolveBalances(tstart, tend, step, data_dict,j)
		@show size(x)
		outputfilename = string("output/ResPatchedSetSeedParamSet", j, ".txt")
		writedlm(outputfilename, x)
	end
end

function readAndPlotData(filename,num_param_sets)
	close("all")
	tstart=0
	 tend=600
	 step=1.0

	t = collect(tstart:step:tend)
	numcols = 8
	upperlim =8*18
	offset = 8
	figure(figsize=(20,20), dpi = 80)
	#plt[:tight_layout]() 
	for k in collect(1:num_param_sets)
		color = 1-k/num_param_sets
		colorstr = string(color)
		println(string("on data set ", k, " of ", num_param_sets))
		x = readdlm(string(filename,k,".txt"),',')
		@show size(x)
		j = 1 #plot all the data
		plotcounter = 1
		colnum = 1
		while(j<=upperlim)
			if(colnum >numcols)
				break
			end
			ax = gca()
			currx = x[:,j]
			plt[:subplot](18,8,plotcounter)
			plt[:tick_params](axis="both", which="major", labelsize=7)
			plt[:tick_params](axis="both", which="minor", labelsize=7)
			#plt[:ticklabel_format](axis="y", useOffset=false)
			plot(t,currx ,linewidth=2.0,color = colorstr)
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
			ax[:set_ylim]([0,600])
		elseif j in collect(121:128) #antiplasmin
			ax[:set_ylim]([0,2000])
		elseif j in collect(129:136)#PAI_1
			ax[:set_ylim]([-.1,.6])
		elseif j in collect(137:144)
			ax[:set_ylim]([0,6000])
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
	savefig(string("output/PrettyLayoutFlowOn10BestParams",".pdf"),bbox_inches="tight")
end

function readandPlotDataWoundOnly(filename,num_param_sets)
	close("all")
	tstart=0
	 tend=600
	 step=1.0

	t = collect(tstart:step:tend)
	numcols = 8
	upperlim =8*18
	offset = 8
	figure(figsize=(20,20), dpi = 80)
	speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Fibrin", "Plasmin", "Fibrinogen", "Plasminogen", "tPA", "uPA", "Fibrin monomer", "Protofibril monomer", "antiplasmin", "PAI_1", "Fiber","Volume"]
	for k in collect(1:num_param_sets)
		color = 1-k/num_param_sets
		colorstr = string(color)
		println(string("on data set ", k, " of ", num_param_sets))
		x = readdlm(string(filename,k,".txt"),',')
		@show size(x)
		j = 1 #plot all the data
		plotcounter = 1
		colnum = 1

		for j in collect(127:144)
			ax = gca()
			currx = x[:,j]
			plt[:subplot](4,5,plotcounter)
			plt[:tick_params](axis="both", which="major", labelsize=14)
			plt[:tick_params](axis="both", which="minor", labelsize=14)
			#plt[:ticklabel_format](axis="y", useOffset=false)
			plot(t,currx ,linewidth=2.0,color = colorstr)
			title(speciesnames[plotcounter])
			plotcounter = plotcounter+1
		end

	end
	savefig(string("output/PrettyLayoutFlowOn10WoundOnlyBestParams",".pdf"),bbox_inches="tight")
end

function ReadAndPlotWoundAvg(filename, num_param_sets)
	close("all")
	tstart=0
	 tend=600
	 step=1.0

	t = collect(tstart:step:tend)
	numcols = 8
	upperlim =8*18
	offset = 8

	alldata = Array[]
	for j in collect(1:num_param_sets)
		data = readdlm(string(filename,j,".txt"),',')
		push!(alldata,data)
	end

	#arrange data into a form that I can use
	k = 0
	numthings = 19*8
	forsummary = Array[]
	for x in alldata
		for j in collect(1:size(x,2))
	    		  push!(forsummary,x[:,j])
	   	 end
	end
	means = Array[]
	stdevs = Array[]
	while (k<=numthings)
		usefulindexes = Int[]
		for j in collect(1:size(forsummary,1))
			if(mod(j,numthings)==k)
				push!(usefulindexes,j)
			end
	       end
		#@show usefulindexes
	      # currstuff = Array{Array}(size(forsummary[1],1))
		currstuff = fill(1.0, size(forsummary[1],1),1)
		for idx in usefulindexes
			currstuff=hcat(currstuff,forsummary[idx])
		end
		#@show currstuff
		currmean = mean(currstuff[:,2:end],2)
		currstd = std(currstuff[:,2:end],2)
		push!(means,currmean)
		push!(stdevs, currstd)
		k = k+1
	end
		speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Fibrin", "Plasmin", "Fibrinogen", "Plasminogen", "tPA", "uPA", "Fibrin monomer", "Protofibril monomer", "antiplasmin", "PAI_1", "Fiber","Volume"]
	figure(figsize=(20,20), dpi = 80)
	plotcounter = 1
	for j in collect(128:145)
		postive95conf = means[j]+1.96.*stdevs[j]
		negative95conf = means[j]-1.96.*stdevs[j]
		ax = gca()
		plt[:subplot](4,5,plotcounter)
		plt[:tick_params](axis="both", which="major", labelsize=12)
		plt[:tick_params](axis="both", which="minor", labelsize=12)
		plt[:tight_layout]() 
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,means[j] ,linewidth=2.0,color = ".03")
		fill_between((t), squeeze(negative95conf,2), squeeze(postive95conf,2), color = ".75")
		title(speciesnames[plotcounter], fontsize = 14)
		plotcounter = plotcounter+1
		end
	savefig("output/PrettyUsing10BestParamSetsInWoundPatchedSetSeed.pdf")
	#return forsummary
end
