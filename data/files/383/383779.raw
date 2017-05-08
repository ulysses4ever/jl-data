using PyPlot

function plotcomparison(savestr)
	close("all")
	constP = readdlm("output/HeartRateConst100.csv")
	varryingP = readdlm(string(savestr, ".csv"))

	alldata = Array[]
	push!(alldata, constP)
	push!(alldata, varryingP)
	colorcounter = 1.0
	numDataSets = length(alldata)+0.0
	figure(figsize=(30,20))
	PyPlot.hold(true)
	@show size(alldata)
	figure(figsize=(30,20))
	colorcounter = 1.0
	numDataSets = length(alldata)+0.0
	
		for x in alldata
		colorstr = string(1-colorcounter/(.001+numDataSets))
		@show colorstr
		t = x[:,1]
		x = x[:,2:end]
	
		 PyPlot.hold(true)
		 plt[:tight_layout]() 	 #to prevent plots from overlapping
		volumecounter = 1
		 volumeoffset = 56
		 plotcounter = 1
		 j=1
		 upperlim = 64
		offset = 8
			#plot so that factors are rows, organs are columns
	colnum = 1
	upperlim = 57
	while(j<=upperlim)
		if(colnum >8)
			break
		end

		ax = gca()
			@show plotcounter,colnum
		plt[:subplot](8,8,plotcounter)
		plt[:tick_params](axis="both", which="major", labelsize=12)
		plt[:tick_params](axis="both", which="minor", labelsize=12)
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,x[:,j] ,linewidth=2.0,color = colorstr)

		#remove axis numbering for columns other than first
		if(colnum !=1)
			ax[:set_yticklabels]([])
		end
		ax[:set_xticklabels]([])
		plotcounter = plotcounter+offset
		j=j+1
		if(plotcounter>=57)
			colnum = colnum+1
			plotcounter = colnum
		end
	end
	plt[:subplot](8,8,56)
	ax = gca()
	ax[:set_yticklabels]([])
	ax[:set_xticklabels]([])	

	plt[:subplot](8,8,49)
	ax = gca()
	ax[:set_yticklabels]([collect(-.05:.05:.2)])

	for k in collect(57:64)
		plt[:subplot](8,8,k)
		plt[:tick_params](axis="both", which="major", labelsize=12)
		plt[:tick_params](axis="both", which="minor", labelsize=12)
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,x[:,k] ,linewidth=2.0,color = colorstr)
		ax = gca()
		#ax[:set_xticklabels](collect(0:t[end]))

		if(k >57)
			ax[:set_yticklabels]([])
		end
	end
	plt[:subplot](8,8,64)
	ax = gca()
	ax[:set_xticklabels]([collect(0:2:16)])

	#make axis all the same
	for j in collect(1:64)
		plt[:subplot](8,8,j)
		ax = gca()
		if j in collect(1:8)
			ax[:set_ylim]([200,1500])
		elseif j in collect(9:16)
			ax[:set_ylim]([0,250])
		elseif j in collect(17:24)
			ax[:set_ylim]([40,60])
		elseif j in collect(25:32)
			ax[:set_ylim]([0,10])
		elseif j in collect(33:40)
			ax[:set_ylim]([3000,6000])
		elseif j in collect(41:48)
			ax[:set_ylim]([10, 20])
		elseif j in collect(49:56)
			ax[:set_ylim]([-.05,.2])
		elseif j in collect(57:64)
			ax[:set_ylim]([0,3])
		end
	end	
	colorcounter=colorcounter+1
	end
		
	#label colums
	compartments = ["Veins", "Heart","Lungs", "Arteries", "Kidneys", "Liver","Bulk", "Wound"]
	for j in collect(1:8)
		plt[:subplot](8,8,j)
		title(compartments[j], fontsize=18)
	end

	#label rows
	speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Volume"]
	counter = 1
	for j in collect(8:8:64)
		plt[:subplot](8,8,j)
		annotate(speciesnames[counter], xy = [1;1], xytext = [1.02,.8], xycoords = "axes fraction", textcoords = "axes fraction", rotation = "vertical", fontsize = 18)
		counter=counter+1
	end
	savefig(string(savestr,"ComparisonGreyConstHRBlackVarryingPPatient" ,".pdf"))
end

