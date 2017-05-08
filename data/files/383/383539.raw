include("SolveBalances.jl")
include("DataFile.jl")
include("runPatient.jl")
using PyPlot

@everywhere function generateData(num_param_sets, patientID,t_trigger)
	close("all") #close already open windows
	#set start time, stop time and step sizes
	 tstart=0
	 tend=40.0
	 step=1.0
	t = Float64[]
	x = Float64[]
	@parallel (+) for j in collect(1:num_param_sets)
		tic()
		println(string("On set ", j," out of ",num_param_sets))
		t,x = runPatient(patientID,j,tend,t_trigger)
		@show size(x)
		strx = string(x)
	
		#cleanedstrx =replace(replace(strx, "[", ""), "]", "")
		outputfilename = string("outputOct12/60s/","for_patient", patientID,"set",j, ".txt")
		writedlm(outputfilename, x)
		toc()
		j
	end
	#return t,x
end

@everywhere function readAndPlotData(filename,num_param_sets)
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

@everywhere function readandPlotDataWoundOnly(filename,num_param_sets)
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
		x = readdlm(string(filename, k, "for_patient", patientID, ".txt"),',')
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
	savefig(string("output/PrettyLayoutFlowOn100WoundOnlyBestParams",".pdf"),bbox_inches="tight")
end

@everywhere function ReadAndPlotWoundAvg(dir, num_param_sets, patientID)
	close("all")
	tstart=0
	 tend=100
	 step=1.0

	t = collect(tstart:step:tend)
	numcols = 8
	upperlim =8*18
	offset = 8

	alldata = Array[]
	allfiles = readdir(dir)
	for file in allfiles
		if(contains(file, "Cleaned"))
			data = readdlm(string(dir,file), ',')
			push!(alldata, data)
		end
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
		speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Fibrin", "Plasmin", "Fibrinogen", "Plasminogen", "tPA", "uPA", "Fibrin monomer", "Protofibril monomer", "Antiplasmin", "PAI_1", "Fiber","Volume"]
	figure(figsize=(30,10), dpi = 80)
	#PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]
	plotcounter = 1
	for j in collect(128:145)
		postive95conf = means[j]+1.96.*stdevs[j]
		negative95conf = means[j]-1.96.*stdevs[j]
		#remove data less than zero, unphysical
		idx = find(x->(x<0),negative95conf);
		negative95conf[idx] = 0.0;
		
		idx = find(x->(x<0),means[j]);
		means[j][idx] = 0.0;
		ax = gca()
		plt[:subplot](3,6,plotcounter)
		plt[:tick_params](axis="both", which="major", labelsize=14)
		plt[:tick_params](axis="both", which="minor", labelsize=14)
		ax[:set_xticklabels]([]) #remove xaxis numbering
		plt[:tight_layout]() 
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,means[j] ,linewidth=2.0,color = ".03")
		fill_between((t), squeeze(negative95conf,2), squeeze(postive95conf,2), color = ".75")
		title(speciesnames[plotcounter], fontsize = 14)
		plotcounter = plotcounter+1
	end
	ax = gca()
	plt[:tight_layout]() 
	ax[:set_xticklabels]([]) #remove xaxis numbering
	savefig(string("outputOct6/patient", patientID, ".pdf"))
	#return forsummary
end

@everywhere function plotMeanAllCompartments(dir, num_param_sets, patientID)
	close("all")
	tstart=0
	 tend=60
	 step=1.0

	t = collect(tstart:step:tend)
	numcols = 8
	upperlim =8*18
	offset = 8

	alldata = Array[]
	allfiles = readdir(dir)
	for file in allfiles
		if(contains(file, "Cleaned"))
			data = readdlm(string(dir,file), ',')
			push!(alldata, data)
		end
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
		speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Fibrin", "Plasmin", "Fibrinogen", "Plasminogen", "tPA", "uPA", "Fibrin monomer", "Protofibril monomer", "Antiplasmin", "PAI_1", "Fiber","Volume"]

		plotcounter = 1
		othercounter = 1
	figure(figsize=(15,20), dpi = 80)
	timesthrough =1
	for j in collect(2:145) #do plotting
		#@show othercounter
		postive95conf = means[j]+1.96.*stdevs[j]
		negative95conf = means[j]-1.96.*stdevs[j]
		#remove data less than zero, unphysical
		idx = find(x->(x<0),negative95conf);
		negative95conf[idx] = 0.0;
		
		idx = find(x->(x<0),means[j]);
		means[j][idx] = 0.0;
		ax = gca()
		plt[:subplot](18,8,othercounter)
		plt[:tick_params](axis="both", which="major", labelsize=7)
		plt[:tick_params](axis="both", which="minor", labelsize=7)
		ax[:set_xticklabels]([]) #remove xaxis numbering
		#plt[:tight_layout]() 
		plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,means[j] ,linewidth=2.0,color = ".03")
		fill_between((t), squeeze(negative95conf,2), squeeze(postive95conf,2), color = ".75")
		#title(speciesnames[plotcounter], fontsize = 7)
		plotcounter = plotcounter+1
		othercounter = othercounter+numcols
		if(plotcounter>length(speciesnames))
			plotcounter = 1
		end
		
		if(othercounter>upperlim)
			timesthrough = timesthrough+1
			othercounter = timesthrough
		end

	end
	#make all axis the same
	for j in collect(1:8*18)
		plt[:subplot](18,8,j)
		ax = gca()
		if j in collect(1:8) #FII
			ax[:set_ylim]([950,1500])
		elseif j in collect(9:16) #FIIA
			ax[:set_ylim]([0,250]) 
		elseif j in collect(17:24) #PC
			ax[:set_ylim]([50,70])
		elseif j in collect(25:32)#APC
			ax[:set_ylim]([0,5]) 
		elseif j in collect(33:40)#ATIII
			ax[:set_ylim]([3000,4000]) 
		elseif j in collect(41:48) #TM
			ax[:set_ylim]([00, 5])
		elseif j in collect(49:56) #Trigger
			ax[:set_ylim]([-.05,6])
		elseif j in collect(57:64) #Fibrin
			ax[:set_ylim]([0,10000])
		elseif j in collect(65:72) #Plasmin
			ax[:set_ylim]([0000,2100])
		elseif j in collect(73:80) #Fibrinogen
			ax[:set_ylim]([0,10000])
		elseif j in collect(81:88) #Plasminogen
			ax[:set_ylim]([1500, 2500])
		elseif j in collect(89:96) #tPA
			ax[:set_ylim]([-1,10])
		elseif j in collect(97:104) #uPA
			ax[:set_ylim]([-.02, .05])
		elseif j in collect(105:112)#Fibrin monomer
			ax[:set_ylim]([0,50])
		elseif j in collect(113:120)#protofibril
			ax[:set_ylim]([0,600])
		elseif j in collect(121:128) #antiplasmin
			ax[:set_ylim]([1000,1200])
		elseif j in collect(129:136)#PAI_1
			ax[:set_ylim]([-.1,.6])
		elseif j in collect(137:144)
			ax[:set_ylim]([-100,3000])
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
		annotate(speciesnames[counter], xy = [1;1], xytext = [1.05,.50], xycoords = "axes fraction", textcoords = "axes fraction", rotation = "horizontal", fontsize = 18)
		counter=counter+1
	end
	#remove ylables from other than 1st colums
	for j in collect(0:143)
		plotcounter = j+1
		if(mod(j,8)!=0)
			plt[:subplot](18,8,plotcounter)
			ax = gca()
			ax[:set_yticklabels]([]) #remove yaxis numbering
		end
	end
	#remove one remaining xtricks
	plt[:subplot](18,8,18*8)
	ax = gca()
	ax[:set_xticklabels]([])



	savefig(string("outputOct10/600sParallel/patient", patientID, "AllCompartments.pdf"),bbox_inches="tight")
end
