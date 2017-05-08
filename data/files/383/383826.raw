using PyPlot

function plotcomparison()
	close("all")
	constP = readdlm("outputs/UsingConstP.csv")
	varryingP = readdlm("outputs/s01004-2531-07-20-08-50n.csv")

	alldata = Array[]
	push!(alldata, constP)
	push!(alldata, varryingP)
	@show size(alldata)
	figure(figsize=(20,20))
	colorcounter = 1.0
	numDataSets = length(alldata)+0.0
	
	for x in alldata
		colorstr = string(1-colorcounter/(.001+numDataSets))
		@show colorstr
		t = x[:,1]
		FIIa_vein = x[:, 3]
		APC_lungs = x[:, 12]
		APC_wound = x[:, 40]
		volume_heart = x[:, 47]
		APC_heart = x[:, 26]
		TRIGGER_wound = x[:, 43]
		FII_kidney = x[:, 30]
		FII_lungs = x[:, 9]
		TM_artery = x[:, 21]
		TRIGGER_lungs = x[:, 15]
		PC_kidney = x[:, 32]
		ATIII_kidney = x[:, 34]
		APC_artery = x[:, 19]
		ATIII_heart = x[:, 27]
		TRIGGER_kidney = x[:, 36]
		PC_artery = x[:, 18]
		volume_lungs = x[:, 45]
		APC_vein = x[:, 5]
		FIIa_wound = x[:, 38]
		volume_artery = x[:, 46]
		TM_lungs = x[:, 14]
		FIIa_kidney = x[:, 31]
		FII_vein = x[:, 2]
		volume_kidney = x[:, 48]
		APC_kidney = x[:, 33]
		ATIII_wound = x[:, 41]
		TRIGGER_vein = x[:, 8]
		FIIa_lungs = x[:, 10]
		volume_vein = x[:, 44]
		TM_kidney = x[:, 35]
		PC_vein = x[:, 4]
		PC_wound = x[:, 39]
		FII_wound = x[:, 37]
		volume_wound = x[:, 49]
		ATIII_lungs = x[:, 13]
		FIIa_artery = x[:, 17]
		TRIGGER_artery = x[:, 22]
		PC_lungs = x[:, 11]
		ATIII_artery = x[:, 20]
		FII_heart = x[:, 23]
		TM_vein = x[:, 7]
		PC_heart = x[:, 25]
		TRIGGER_heart = x[:, 29]
		ATIII_vein = x[:, 6]
		FIIa_heart = x[:, 24]
		TM_heart = x[:, 28]
		TM_wound = x[:, 42]
		FII_artery = x[:, 16]
	
		 PyPlot.hold(true)
		 plt[:tight_layout]() 	 #to prevent plots from overlapping
		 plt[:subplot](6,7,1)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_wound ,linewidth=.7,color = colorstr)
		 title("FII_wound")
		 plt[:subplot](6,7,2)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_wound ,linewidth=.7,color = colorstr)
		 title("FIIa_wound")
		 plt[:subplot](6,7,3)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_wound ,linewidth=.7,color = colorstr)
		 title("PC_wound")
		 plt[:subplot](6,7,4)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_wound ,linewidth=.7,color = colorstr)
		 title("APC_wound")
		 plt[:subplot](6,7,5)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_wound ,linewidth=.7,color = colorstr)
		 title("ATIII_wound")
		 plt[:subplot](6,7,6)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_wound ,linewidth=.7,color = colorstr)
		 title("TM_wound")
		 plt[:subplot](6,7,7)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_wound ,linewidth=.7,color = colorstr)
		 title("TRIGGER_wound")
		 plt[:subplot](6,7,8)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_vein ,linewidth=.7,color = colorstr)
		 title("FII_vein")
		 plt[:subplot](6,7,9)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_vein ,linewidth=.7,color = colorstr)
		 title("FIIa_vein")
		 plt[:subplot](6,7,10)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_vein ,linewidth=.7,color = colorstr)
		 title("PC_vein")
		 plt[:subplot](6,7,11)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_vein ,linewidth=.7,color = colorstr)
		 title("APC_vein")
		 plt[:subplot](6,7,12)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_vein ,linewidth=.7,color = colorstr)
		 title("ATIII_vein")
		 plt[:subplot](6,7,13)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_vein ,linewidth=.7,color = colorstr)
		 title("TM_vein")
		 plt[:subplot](6,7,14)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_vein ,linewidth=.7,color = colorstr)
		 title("TRIGGER_vein")
		 plt[:subplot](6,7,15)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_artery ,linewidth=.7,color = colorstr)
		 title("FII_artery")
		 plt[:subplot](6,7,16)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_artery ,linewidth=.7,color = colorstr)
		 title("FIIa_artery")
		 plt[:subplot](6,7,17)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_artery ,linewidth=.7,color = colorstr)
		 title("PC_artery")
		 plt[:subplot](6,7,18)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_artery ,linewidth=.7,color = colorstr)
		 title("APC_artery")
		 plt[:subplot](6,7,19)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_artery ,linewidth=.7,color = colorstr)
		 title("ATIII_artery")
		 plt[:subplot](6,7,20)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_artery ,linewidth=.7,color = colorstr)
		 title("TM_artery")
		 plt[:subplot](6,7,21)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_artery ,linewidth=.7,color = colorstr)
		 title("TRIGGER_artery")
		 plt[:subplot](6,7,22)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_heart ,linewidth=.7,color = colorstr)
		 title("FII_heart")
		 plt[:subplot](6,7,23)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_heart ,linewidth=.7,color = colorstr)
		 title("FIIa_heart")
		 plt[:subplot](6,7,24)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_heart ,linewidth=.7,color = colorstr)
		 title("PC_heart")
		 plt[:subplot](6,7,25)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_heart ,linewidth=.7,color = colorstr)
		 title("APC_heart")
		 plt[:subplot](6,7,26)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_heart ,linewidth=.7,color = colorstr)
		 title("ATIII_heart")
		 plt[:subplot](6,7,27)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_heart ,linewidth=.7,color = colorstr)
		 title("TM_heart")
		 plt[:subplot](6,7,28)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_heart ,linewidth=.7,color = colorstr)
		 title("TRIGGER_heart")
		 plt[:subplot](6,7,29)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_kidney ,linewidth=.7,color = colorstr)
		 title("FII_kidney")
		 plt[:subplot](6,7,30)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_kidney ,linewidth=.7,color = colorstr)
		 title("FIIa_kidney")
		 plt[:subplot](6,7,31)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_kidney ,linewidth=.7,color = colorstr)
		 title("PC_kidney")
		 plt[:subplot](6,7,32)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_kidney ,linewidth=.7,color = colorstr)
		 title("APC_kidney")
		 plt[:subplot](6,7,33)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_kidney ,linewidth=.7,color = colorstr)
		 title("ATIII_kidney")
		 plt[:subplot](6,7,34)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_kidney ,linewidth=.7,color = colorstr)
		 title("TM_kidney")
		 plt[:subplot](6,7,35)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_kidney ,linewidth=.7,color = colorstr)
		 title("TRIGGER_kidney")
		 plt[:subplot](6,7,36)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FII_lungs ,linewidth=.7,color = colorstr)
		 title("FII_lungs")
		 plt[:subplot](6,7,37)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, FIIa_lungs ,linewidth=.7,color = colorstr)
		 title("FIIa_lungs")
		 plt[:subplot](6,7,38)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, PC_lungs ,linewidth=.7,color = colorstr)
		 title("PC_lungs")
		 plt[:subplot](6,7,39)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, APC_lungs ,linewidth=.7,color = colorstr)
		 title("APC_lungs")
		 plt[:subplot](6,7,40)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, ATIII_lungs ,linewidth=.7,color = colorstr)
		 title("ATIII_lungs")
		 plt[:subplot](6,7,41)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TM_lungs ,linewidth=.7,color = colorstr)
		 title("TM_lungs")
		 plt[:subplot](6,7,42)
		 plt[:tick_params](axis="both", which="major", labelsize=7)
		 plt[:tick_params](axis="both", which="minor", labelsize=7)
		 plt[:ticklabel_format](axis="y", useOffset=false)
		 plot(t, TRIGGER_lungs ,linewidth=.7,color = colorstr)
		 title("TRIGGER_lungs")

		colorcounter = 1.0+colorcounter;

	end
	savefig("ComparisonGreyConstPBlackVarryingPPatients01004-2531-07-20-08-50n.png")
end

plotcomparison()
