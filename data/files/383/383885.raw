using PyPlot

function plot3d()
	close("all")
	x = readdlm("output/HeartRateConst100.csv")
	PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]
	#compartments = ["Wound", "Vein", "Artery", "Heart", "Kidney", "Lungs", "Liver", "Bulk"]
	compartments = ["Vein", "Heart", "Lungs", "Artery","Kidney","Liver", "Bulk", "Wound" ]
	xcords = collect(1:7)
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

		startnum = 2
		numcompartments =7.0
		colorstr = 0.02
		incr = 1.0/numcompartments-.05
		for j in collect(1:numcompartments)
			scatter3D(t, fill(j, 1, size(t, 1),), x[:,startnum+j*numcompartments], color = string(colorstr), ".")
			colorstr = colorstr+incr

		end
		ax = gca()
		plt[:xlim](0,10)
		plt[:yticks](collect(1:numcompartments+1))
		ax[:set_yticklabels](compartments)
		savefig("outputJul06/CondensedFII.pdf")
		
		
end

function plot2D()
	close("all")
	x = readdlm("output/HeartRateConst100.csv")
	PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]
	#compartments = ["Wound", "Vein", "Artery", "Heart", "Kidney", "Lungs", "Liver", "Bulk"]
	compartments = ["Vein", "Heart", "Lungs", "Artery","Kidney","Liver", "Bulk", "Wound" ]
	xcords = collect(1:7)
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

		startnum = 3
		numcompartments =7.0
		colorstr = 0.02
		incr = 1.0/numcompartments-.05
		for j in collect(1:numcompartments)
			plot(t, x[:,startnum+j*numcompartments], color = string(colorstr), "-", linewidth = .3)
			colorstr = colorstr+incr

		end
		ax = gca()
		plt[:xlim](0,10)
		#plt[:yticks](collect(1:numcompartments+1))
		#ax[:set_yticklabels](compartments)
		savefig("outputJul06/CondensedFII2d.pdf")

end
