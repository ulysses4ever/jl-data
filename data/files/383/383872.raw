using PyPlot

function plotcomparison()
	close("all")
	#constP = readdlm("outputs/UsingConstP.csv")
	#varryingP = readdlm("outputs/s01004-2531-07-20-08-50n.csv")
	point5 = readdlm("output/constantvolumewound16mintrigerpoint5.csv")
	point05 = readdlm("output/constantvolumewound16mintrigerpoint05.csv")
	point005 = readdlm("output/constantvolumewound16mintrigerpoint005.csv")

	alldata = Array[]
	#push!(alldata, constP)
	#push!(alldata, varryingP)
	push!(alldata, point5)
	push!(alldata, point05)
	push!(alldata, point005)
	@show size(alldata)
	figure(figsize=(20,20))
	colorcounter = 1.0
	numDataSets = length(alldata)+0.0
	
	for x in alldata
		colorstr = string(1-colorcounter/(.001+numDataSets))
		@show colorstr
		t = x[:,1]
		x = x[:,2:end]
#		FIIa_vein = x[:, 3]
#		APC_heart = x[:, 12]
#		APC_liver = x[:, 40]
#		APC_bulk = x[:, 47]
#		APC_artery = x[:, 26]
#		TM_wound = x[:, 56]
#		TRIGGER_liver = x[:, 43]
#		FII_kidney = x[:, 30]
#		volume_heart = x[:, 59]
#		volume_lungs = x[:, 60]
#		FII_heart = x[:, 9]
#		volume_vein = x[:, 58]
#		TM_lungs = x[:, 21]
#		TRIGGER_heart = x[:, 15]
#		PC_kidney = x[:, 32]
#		ATIII_kidney = x[:, 34]
#		APC_lungs = x[:, 19]
#		PC_wound = x[:, 53]
#		ATIII_artery = x[:, 27]
#		TRIGGER_kidney = x[:, 36]
#		PC_lungs = x[:, 18]
#		volume_wound = x[:, 65]
#		TRIGGER_bulk = x[:, 50]
#		FIIa_bulk = x[:, 45]
#		APC_vein = x[:, 5]
#		FIIa_liver = x[:, 38]
#		PC_bulk = x[:, 46]
#		TM_heart = x[:, 14]
#		FIIa_kidney = x[:, 31]
#		FII_vein = x[:, 2]
#		ATIII_bulk = x[:, 48]
#		ATIII_wound = x[:, 55]
#		APC_kidney = x[:, 33]
#		FII_wound = x[:, 51]
#		ATIII_liver = x[:, 41]
#		TRIGGER_vein = x[:, 8]
#		FIIa_heart = x[:, 10]
#		FII_bulk = x[:, 44]
#		volume_artery = x[:, 61]
#		TM_kidney = x[:, 35]
#		PC_vein = x[:, 4]
#		volume_kidney = x[:, 62]
#		PC_liver = x[:, 39]
#		FII_liver = x[:, 37]
#		TM_bulk = x[:, 49]
#		ATIII_heart = x[:, 13]
#		FIIa_lungs = x[:, 17]
#		volume_liver = x[:, 63]
#		TRIGGER_lungs = x[:, 22]
#		PC_heart = x[:, 11]
#		ATIII_lungs = x[:, 20]
#		FIIa_wound = x[:, 52]
#		FII_artery = x[:, 23]
#		TM_vein = x[:, 7]
#		PC_artery = x[:, 25]
#		APC_wound = x[:, 54]
#		TRIGGER_artery = x[:, 29]
#		ATIII_vein = x[:, 6]
#		FIIa_artery = x[:, 24]
#		volume_bulk = x[:, 64]
#		TM_artery = x[:, 28]
#		TRIGGER_wound = x[:, 57]
#		TM_liver = x[:, 42]
#		FII_lungs = x[:, 16]
	
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
		plt[:tick_params](axis="both", which="major", labelsize=14)
		plt[:tick_params](axis="both", which="minor", labelsize=14)
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,x[:,j] ,linewidth=.8,color = colorstr)

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
		plt[:tick_params](axis="both", which="major", labelsize=14)
		plt[:tick_params](axis="both", which="minor", labelsize=14)
		#plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,x[:,k] ,linewidth=.8,color = colorstr)
		ax = gca()
		#ax[:set_xticklabels](collect(0:4:t[end]))

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
			ax[:set_ylim]([0,1400])
		elseif j in collect(9:16)
			ax[:set_ylim]([0,600])
		elseif j in collect(17:24)
			ax[:set_ylim]([20,60])
		elseif j in collect(25:32)
			ax[:set_ylim]([0,10])
		elseif j in collect(33:40)
			ax[:set_ylim]([2000,5000])
		elseif j in collect(41:48)
			ax[:set_ylim]([11, 13])
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
		title(compartments[j], fontsize=24)
	end

	#label rows
	speciesnames = ["FII", "FIIa", "Protein C", "APC", "ATIII", "TM", "Trigger", "Volume"]
	counter = 1
	for j in collect(8:8:64)
		plt[:subplot](8,8,j)
		annotate(speciesnames[counter], xy = [1;1], xytext = [1.02,.8], xycoords = "axes fraction", textcoords = "axes fraction", rotation = "vertical", fontsize = 22)
		counter=counter+1
	end

	for k in collect(1:64)
		plt[:subplot](8,8,k)
		PyPlot.locator_params(axis="y",nbins=4 ) #reduce number of ticks
		#PyPlot.locator_params(axis="x",nbins=5 ) #reduce number of ticks
	end

	savefig("ComparisonofTriggerValuesNewLayoutBetter.pdf",bbox_inches="tight")
end

plotcomparison()
