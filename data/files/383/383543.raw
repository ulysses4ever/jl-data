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
	figure(figsize=(20,20))
	colorcounter = 1.0
	numDataSets = length(alldata)+0.0
	
	for x in alldata
		colorstr = string(1-colorcounter/(.001+numDataSets))
		@show colorstr
		t = x[:,1]
		FIIa_vein = x[:, 3]
		APC_heart = x[:, 12]
		APC_liver = x[:, 40]
		APC_bulk = x[:, 47]
		APC_artery = x[:, 26]
		TM_wound = x[:, 56]
		TRIGGER_liver = x[:, 43]
		FII_kidney = x[:, 30]
		volume_heart = x[:, 59]
		volume_lungs = x[:, 60]
		FII_heart = x[:, 9]
		volume_vein = x[:, 58]
		TM_lungs = x[:, 21]
		TRIGGER_heart = x[:, 15]
		PC_kidney = x[:, 32]
		ATIII_kidney = x[:, 34]
		APC_lungs = x[:, 19]
		PC_wound = x[:, 53]
		ATIII_artery = x[:, 27]
		TRIGGER_kidney = x[:, 36]
		PC_lungs = x[:, 18]
		volume_wound = x[:, 65]
		TRIGGER_bulk = x[:, 50]
		FIIa_bulk = x[:, 45]
		APC_vein = x[:, 5]
		FIIa_liver = x[:, 38]
		PC_bulk = x[:, 46]
		TM_heart = x[:, 14]
		FIIa_kidney = x[:, 31]
		FII_vein = x[:, 2]
		ATIII_bulk = x[:, 48]
		ATIII_wound = x[:, 55]
		APC_kidney = x[:, 33]
		FII_wound = x[:, 51]
		ATIII_liver = x[:, 41]
		TRIGGER_vein = x[:, 8]
		FIIa_heart = x[:, 10]
		FII_bulk = x[:, 44]
		volume_artery = x[:, 61]
		TM_kidney = x[:, 35]
		PC_vein = x[:, 4]
		volume_kidney = x[:, 62]
		PC_liver = x[:, 39]
		FII_liver = x[:, 37]
		TM_bulk = x[:, 49]
		ATIII_heart = x[:, 13]
		FIIa_lungs = x[:, 17]
		volume_liver = x[:, 63]
		TRIGGER_lungs = x[:, 22]
		PC_heart = x[:, 11]
		ATIII_lungs = x[:, 20]
		FIIa_wound = x[:, 52]
		FII_artery = x[:, 23]
		TM_vein = x[:, 7]
		PC_artery = x[:, 25]
		APC_wound = x[:, 54]
		TRIGGER_artery = x[:, 29]
		ATIII_vein = x[:, 6]
		FIIa_artery = x[:, 24]
		volume_bulk = x[:, 64]
		TM_artery = x[:, 28]
		TRIGGER_wound = x[:, 57]
		TM_liver = x[:, 42]
		FII_lungs = x[:, 16]
	
		 PyPlot.hold(true)
		 plt[:tight_layout]() 	 #to prevent plots from overlapping
		 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](8,8,1)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_wound,linewidth=2.0,color = colorstr)
	
	 #title("FII_wound")
	 plt[:subplot](8,8,2)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_wound ,linewidth=2.0,color = colorstr)
	 #title("FIIa_wound")
	 plt[:subplot](8,8,3)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_wound ,linewidth=2.0,color = colorstr)
	 #title("PC_wound")
	 plt[:subplot](8,8,4)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_wound ,linewidth=2.0,color = colorstr)
	 #title("APC_wound")
	 plt[:subplot](8,8,5)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_wound ,linewidth=2.0,color = colorstr)
	 #title("ATIII_wound")
	 plt[:subplot](8,8,6)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_wound ,linewidth=2.0,color = colorstr)
	 #title("TM_wound")
	 plt[:subplot](8,8,7)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_wound ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_wound")

	 plt[:subplot](8,8,8)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_wound ,linewidth=2.0,color = colorstr)

	 plt[:subplot](8,8,9)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_vein ,linewidth=2.0,color = colorstr)
	 #title("FII_vein")
	 plt[:subplot](8,8,10)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_vein ,linewidth=2.0,color = colorstr)
	 #title("FIIa_vein")
	 plt[:subplot](8,8,11)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_vein ,linewidth=2.0,color = colorstr)
	 #title("PC_vein")
	 plt[:subplot](8,8,12)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_vein ,linewidth=2.0,color = colorstr)
	 #title("APC_vein")
	 plt[:subplot](8,8,13)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_vein ,linewidth=2.0,color = colorstr)
	 #title("ATIII_vein")
	 plt[:subplot](8,8,14)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_vein ,linewidth=2.0,color = colorstr)
	 #title("TM_vein")
	 plt[:subplot](8,8,15)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_vein ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_vein")
	 plt[:subplot](8,8,16)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_vein ,linewidth=2.0,color = colorstr)


	 plt[:subplot](8,8,17)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_artery ,linewidth=2.0,color = colorstr)
	 #title("FII_artery")
	 plt[:subplot](8,8,18)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_artery ,linewidth=2.0,color = colorstr)
	 #title("FIIa_artery")
	 plt[:subplot](8,8,19)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_artery ,linewidth=2.0,color = colorstr)
	 #title("PC_artery")
	 plt[:subplot](8,8,20)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_artery ,linewidth=2.0,color = colorstr)
	 #title("APC_artery")
	 plt[:subplot](8,8,21)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_artery ,linewidth=2.0,color = colorstr)
	 #title("ATIII_artery")
	 plt[:subplot](8,8,22)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_artery ,linewidth=2.0,color = colorstr)
	 #title("TM_artery")
	 plt[:subplot](8,8,23)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_artery ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_artery")
	 plt[:subplot](8,8,24)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_artery ,linewidth=2.0,color = colorstr)

	 plt[:subplot](8,8,25)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_heart ,linewidth=2.0,color = colorstr)
	 #title("FII_heart")
	 plt[:subplot](8,8,26)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_heart ,linewidth=2.0,color = colorstr)
	 #title("FIIa_heart")
	 plt[:subplot](8,8,27)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_heart ,linewidth=2.0,color = colorstr)
	 #title("PC_heart")
	 plt[:subplot](8,8,28)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_heart ,linewidth=2.0,color = colorstr)
	 #title("APC_heart")
	 plt[:subplot](8,8,29)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_heart ,linewidth=2.0,color = colorstr)
	 #title("ATIII_heart")
	 plt[:subplot](8,8,30)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_heart ,linewidth=2.0,color = colorstr)
	 #title("TM_heart")
	 plt[:subplot](8,8,31)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_heart ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_heart")

	 plt[:subplot](8,8,32)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_heart ,linewidth=2.0,color = colorstr)

	 plt[:subplot](8,8,33)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_kidney ,linewidth=2.0,color = colorstr)
	 #title("FII_kidney")
	 plt[:subplot](8,8,34)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_kidney ,linewidth=2.0,color = colorstr)
	 #title("FIIa_kidney")
	 plt[:subplot](8,8,35)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_kidney ,linewidth=2.0,color = colorstr)
	 #title("PC_kidney")
	 plt[:subplot](8,8,36)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_kidney ,linewidth=2.0,color = colorstr)
	 #title("APC_kidney")
	 plt[:subplot](8,8,37)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_kidney ,linewidth=2.0,color = colorstr)
	 #title("ATIII_kidney")
	 plt[:subplot](8,8,38)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_kidney ,linewidth=2.0,color = colorstr)
	 #title("TM_kidney")
	 plt[:subplot](8,8,39)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_kidney ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_kidney")

	 plt[:subplot](8,8,40)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_kidney ,linewidth=2.0,color = colorstr)
	
	 plt[:subplot](8,8,41)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_lungs ,linewidth=2.0,color = colorstr)
	 #title("FII_lungs")
	 plt[:subplot](8,8,42)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_lungs ,linewidth=2.0,color = colorstr)
	 #title("FIIa_lungs")
	 plt[:subplot](8,8,43)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_lungs ,linewidth=2.0,color = colorstr)
	 #title("PC_lungs")
	 plt[:subplot](8,8,44)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_lungs ,linewidth=2.0,color = colorstr)
	 #title("APC_lungs")
	 plt[:subplot](8,8,45)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_lungs ,linewidth=2.0,color = colorstr)
	 #title("ATIII_lungs")
	 plt[:subplot](8,8,46)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_lungs ,linewidth=2.0,color = colorstr)
	 #title("TM_lungs")
	 plt[:subplot](8,8,47)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_lungs ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_lungs")

	 plt[:subplot](8,8,48)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_lungs ,linewidth=2.0,color = colorstr)

	 plt[:subplot](8,8,49)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_liver ,linewidth=2.0,color = colorstr)
	 #title("FII_liver")
	 plt[:subplot](8,8,50)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_liver ,linewidth=2.0,color = colorstr)
	 #title("FIIa_liver")
	 plt[:subplot](8,8,51)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_liver ,linewidth=2.0,color = colorstr)
	 #title("PC_liver")
	 plt[:subplot](8,8,52)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_liver ,linewidth=2.0,color = colorstr)
	 #title("APC_liver")
	 plt[:subplot](8,8,53)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_liver ,linewidth=2.0,color = colorstr)
	 #title("ATIII_liver")
	 plt[:subplot](8,8,54)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_liver ,linewidth=2.0,color = colorstr)
	 #title("TM_liver")
	 plt[:subplot](8,8,55)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_liver ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_liver")

	 plt[:subplot](8,8,56)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_liver ,linewidth=2.0,color = colorstr)

	 plt[:subplot](8,8,57)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_bulk ,linewidth=2.0,color = colorstr)
	 #title("FII_bulk")
	 plt[:subplot](8,8,58)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_bulk ,linewidth=2.0,color = colorstr)
	 #title("FIIa_bulk")
	 plt[:subplot](8,8,59)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_bulk ,linewidth=2.0,color = colorstr)
	 #title("PC_bulk")
	 plt[:subplot](8,8,60)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_bulk ,linewidth=2.0,color = colorstr)
	 #title("APC_bulk")
	 plt[:subplot](8,8,61)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_bulk ,linewidth=2.0,color = colorstr)
	 #title("ATIII_bulk")
	 plt[:subplot](8,8,62)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_bulk ,linewidth=2.0,color = colorstr)
	 #title("TM_bulk")
	 plt[:subplot](8,8,63)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_bulk ,linewidth=2.0,color = colorstr)
	 #title("TRIGGER_bulk")

	 plt[:subplot](8,8,64)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, volume_bulk ,linewidth=2.0,color = colorstr)
		colorcounter = 1.0+colorcounter;

	end
	#remove axis numbers
	for j in collect(1:64)
		plt[:subplot](8,8,j)
		#plt[:ylim](0, 5000)
		ax = gca()
		ax[:set_xticklabels]([])
		ax[:set_yticklabels]([])
	end

	savefig(string(savestr,"ComparisonGreyConstHRBlackVarryingPPatient" ,".pdf"))
end

