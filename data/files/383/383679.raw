# ----------------------------------------------------------------------------------- #
# Copyright (c) 2016 Varnerlab
# School of Chemical Engineering Purdue University
# W. Lafayette IN 46907 USA

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ----------------------------------------------------------------------------------- #
include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot
function runModel()
	 close("all") #close already open windows
	#set start time, stop time and step sizes
	 tstart=0
	 tend=15
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	Fibrin_monomer_artery = x[:, 68]
	volume_artery = x[:, 148]
	antiplasmin_bulk = x[:, 124]
	FIIa_vein = x[:, 2]
	PAI_1_kidney = x[:, 89]
	Plasminogen_vein = x[:, 11]
	PC_lungs = x[:, 39]
	Fibrinogen_lungs = x[:, 46]
	uPA_kidney = x[:, 85]
	Fibrin_wound = x[:, 134]
	Fibrinogen_wound = x[:, 136]
	TRIGGER_heart = x[:, 25]
	FII_artery = x[:, 55]
	TM_lungs = x[:, 42]
	Plasminogen_heart = x[:, 29]
	APC_artery = x[:, 58]
	tPA_artery = x[:, 66]
	ATIII_wound = x[:, 131]
	Fiber_wound = x[:, 144]
	ATIII_artery = x[:, 59]
	volume_bulk = x[:, 151]
	Fibrin_vein = x[:, 8]
	antiplasmin_wound = x[:, 142]
	volume_liver = x[:, 150]
	FIIa_kidney = x[:, 74]
	ATIII_liver = x[:, 95]
	uPA_wound = x[:, 139]
	PC_artery = x[:, 57]
	FIIa_heart = x[:, 20]
	Fiber_kidney = x[:, 90]
	PC_bulk = x[:, 111]
	Fibrin_monomer_vein = x[:, 14]
	uPA_heart = x[:, 31]
	TM_kidney = x[:, 78]
	APC_bulk = x[:, 112]
	antiplasmin_artery = x[:, 70]
	antiplasmin_liver = x[:, 106]
	Protofibril_heart = x[:, 33]
	Fiber_vein = x[:, 18]
	antiplasmin_lungs = x[:, 52]
	uPA_bulk = x[:, 121]
	Protofibril_artery = x[:, 69]
	TM_bulk = x[:, 114]
	FII_bulk = x[:, 109]
	TM_liver = x[:, 96]
	Fibrin_heart = x[:, 26]
	TRIGGER_wound = x[:, 133]
	PAI_1_heart = x[:, 35]
	Plasminogen_kidney = x[:, 83]
	PAI_1_bulk = x[:, 125]
	Plasmin_wound = x[:, 135]
	APC_wound = x[:, 130]
	volume_heart = x[:, 146]
	PAI_1_vein = x[:, 17]
	Fibrinogen_artery = x[:, 64]
	Plasminogen_artery = x[:, 65]
	uPA_lungs = x[:, 49]
	Fibrin_lungs = x[:, 44]
	tPA_kidney = x[:, 84]
	tPA_wound = x[:, 138]
	APC_vein = x[:, 4]
	FII_lungs = x[:, 37]
	volume_vein = x[:, 145]
	FIIa_bulk = x[:, 110]
	FII_wound = x[:, 127]
	Plasmin_lungs = x[:, 45]
	uPA_vein = x[:, 13]
	Fibrin_monomer_kidney = x[:, 86]
	uPA_artery = x[:, 67]
	Plasmin_liver = x[:, 99]
	PC_liver = x[:, 93]
	Plasmin_bulk = x[:, 117]
	Fiber_bulk = x[:, 126]
	APC_liver = x[:, 94]
	Plasminogen_wound = x[:, 137]
	Protofibril_wound = x[:, 141]
	Protofibril_liver = x[:, 105]
	tPA_heart = x[:, 30]
	FII_vein = x[:, 1]
	Plasminogen_lungs = x[:, 47]
	Fiber_lungs = x[:, 54]
	Fibrin_monomer_heart = x[:, 32]
	Fibrin_monomer_lungs = x[:, 50]
	ATIII_kidney = x[:, 77]
	APC_lungs = x[:, 40]
	Fibrin_kidney = x[:, 80]
	Plasminogen_liver = x[:, 101]
	TRIGGER_bulk = x[:, 115]
	Fibrinogen_kidney = x[:, 82]
	FII_liver = x[:, 91]
	TRIGGER_vein = x[:, 7]
	Plasmin_vein = x[:, 9]
	TRIGGER_lungs = x[:, 43]
	TM_artery = x[:, 60]
	antiplasmin_heart = x[:, 34]
	PC_kidney = x[:, 75]
	FIIa_wound = x[:, 128]
	Fibrin_monomer_liver = x[:, 104]
	TM_wound = x[:, 132]
	Protofibril_kidney = x[:, 87]
	volume_lungs = x[:, 147]
	uPA_liver = x[:, 103]
	PC_vein = x[:, 3]
	TRIGGER_artery = x[:, 61]
	TRIGGER_kidney = x[:, 79]
	FIIa_lungs = x[:, 38]
	Fibrinogen_bulk = x[:, 118]
	volume_wound = x[:, 152]
	PAI_1_artery = x[:, 71]
	tPA_bulk = x[:, 120]
	Fiber_heart = x[:, 36]
	tPA_lungs = x[:, 48]
	ATIII_bulk = x[:, 113]
	APC_kidney = x[:, 76]
	tPA_vein = x[:, 12]
	Fibrinogen_liver = x[:, 100]
	Plasmin_kidney = x[:, 81]
	Fibrin_liver = x[:, 98]
	Fibrin_monomer_bulk = x[:, 122]
	antiplasmin_vein = x[:, 16]
	Fibrin_artery = x[:, 62]
	PAI_1_liver = x[:, 107]
	Fibrin_monomer_wound = x[:, 140]
	PAI_1_wound = x[:, 143]
	PC_heart = x[:, 21]
	Fibrinogen_vein = x[:, 10]
	tPA_liver = x[:, 102]
	FII_heart = x[:, 19]
	Protofibril_lungs = x[:, 51]
	APC_heart = x[:, 22]
	TM_vein = x[:, 6]
	TM_heart = x[:, 24]
	FII_kidney = x[:, 73]
	antiplasmin_kidney = x[:, 88]
	FIIa_liver = x[:, 92]
	Plasminogen_bulk = x[:, 119]
	PC_wound = x[:, 129]
	PAI_1_lungs = x[:, 53]
	Fibrin_bulk = x[:, 116]
	Fiber_artery = x[:, 72]
	Fibrinogen_heart = x[:, 28]
	Protofibril_bulk = x[:, 123]
	volume_kidney = x[:, 149]
	ATIII_vein = x[:, 5]
	ATIII_heart = x[:, 23]
	Plasmin_artery = x[:, 63]
	Plasmin_heart = x[:, 27]
	FIIa_artery = x[:, 56]
	TRIGGER_liver = x[:, 97]
	Fiber_liver = x[:, 108]
	ATIII_lungs = x[:, 41]
	Protofibril_vein = x[:, 15]

#	 #code to plot, using subplots
#	 figure(figsize=(40,20))
#	 PyPlot.hold(true)
#	 plt[:tight_layout]() 	 #to prevent plots from overlapping
#	 plt[:subplot](1,18,1)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, FII_wound ,linewidth=2.0,"k")
#	 title("FII_wound")
#	 plt[:subplot](1,18,2)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, FIIa_wound ,linewidth=2.0,"k")
#	 title("FIIa_wound")
#	 plt[:subplot](1,18,3)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, PC_wound ,linewidth=2.0,"k")
#	 title("PC_wound")
#	 plt[:subplot](1,18,4)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, APC_wound ,linewidth=2.0,"k")
#	 title("APC_wound")
#	 plt[:subplot](1,18,5)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, ATIII_wound ,linewidth=2.0,"k")
#	 title("ATIII_wound")
#	 plt[:subplot](1,18,6)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, TM_wound ,linewidth=2.0,"k")
#	 title("TM_wound")
#	 plt[:subplot](1,18,7)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, TRIGGER_wound ,linewidth=2.0,"k")
#	 title("TRIGGER_wound")
#	 plt[:subplot](1,18,8)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Fibrin_wound ,linewidth=2.0,"k")
#	 title("Fibrin_wound")
#	 plt[:subplot](1,18,9)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Plasmin_wound ,linewidth=2.0,"k")
#	 title("Plasmin_wound")
#	 plt[:subplot](1,18,10)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Fibrinogen_wound ,linewidth=2.0,"k")
#	 title("Fibrinogen_wound")
#	 plt[:subplot](1,18,11)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Plasminogen_wound ,linewidth=2.0,"k")
#	 title("Plasminogen_wound")
#	 plt[:subplot](1,18,12)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, tPA_wound ,linewidth=2.0,"k")
#	 title("tPA_wound")
#	 plt[:subplot](1,18,13)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, uPA_wound ,linewidth=2.0,"k")
#	 title("uPA_wound")
#	 plt[:subplot](1,18,14)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Fibrin_monomer_wound ,linewidth=2.0,"k")
#	 title("Fibrin_monomer_wound")
#	 plt[:subplot](1,18,15)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Protofibril_wound ,linewidth=2.0,"k")
#	 title("Protofibril_wound")
#	 plt[:subplot](1,18,16)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, antiplasmin_wound ,linewidth=2.0,"k")
#	 title("antiplasmin_wound")
#	 plt[:subplot](1,18,17)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, PAI_1_wound ,linewidth=2.0,"k")
#	 title("PAI_1_wound")
#	 plt[:subplot](1,18,18)
#	 plt[:tick_params](axis="both", which="major", labelsize=7)
#	 plt[:tick_params](axis="both", which="minor", labelsize=7)
#	 plt[:ticklabel_format](axis="y", useOffset=false)
#	 plot(t, Fiber_wound ,linewidth=2.0,"k")
#	 title("Fiber_wound")
#	savefig("output/TestingTrigger5AllDone.pdf")

#	 #code to plot compartment volumes, using subplots
#	 figure(figsize=(20,20))
#	 PyPlot.hold(true)
#	 plt[:tight_layout]() 	 #to prevent plots from overlapping
#	 plt[:subplot](3.0,3.0,1)
#	 plot(t, volume_vein)
#	 title("volume_vein")
#	 plt[:subplot](3.0,3.0,2)
#	 plot(t, volume_heart)
#	 title("volume_heart")
#	 plt[:subplot](3.0,3.0,3)
#	 plot(t, volume_lungs)
#	 title("volume_lungs")
#	 plt[:subplot](3.0,3.0,4)
#	 plot(t, volume_artery)
#	 title("volume_artery")
#	 plt[:subplot](3.0,3.0,5)
#	 plot(t, volume_kidney)
#	 title("volume_kidney")
#	 plt[:subplot](3.0,3.0,6)
#	 plot(t, volume_liver)
#	 title("volume_liver")
#	 plt[:subplot](3.0,3.0,7)
#	 plot(t, volume_bulk)
#	 title("volume_bulk")
#	 plt[:subplot](3.0,3.0,8)
#	 plot(t, volume_wound)
#	 title("volume_wound")


	figure()
	plot(t, Fibrinogen_wound, "r")
	plot(t, Fibrin_monomer_wound, "o")
	plot(t, Protofibril_wound, "y")
	plot(t, Fiber_wound, "g")
	plot(t, Fibrin_wound, "b")

end
	
runModel()
