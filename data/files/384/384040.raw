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
	 tend=10
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	Fibrin_heart = x[:, 68]
	volume_heart = x[:, 124]
	FIIa_vein = x[:, 2]
	Plasmin_kidney = x[:, 89]
	Plasminogen_vein = x[:, 11]
	TAT_lungs = x[:, 39]
	TM_artery = x[:, 46]
	ATIII_kidney = x[:, 85]
	ATIII_lungs = x[:, 25]
	Protofibril_artery = x[:, 55]
	FIIa_artery = x[:, 42]
	Plasmin_lungs = x[:, 29]
	Fiber_artery = x[:, 58]
	TM_heart = x[:, 66]
	TAT_artery = x[:, 59]
	Fibrin_vein = x[:, 8]
	Fibrin_monomer_heart = x[:, 74]
	Protofibril_kidney = x[:, 95]
	PAI_1_artery = x[:, 57]
	PAP_vein = x[:, 20]
	Fibrinogen_kidney = x[:, 90]
	Plasminogen_wound = x[:, 111]
	Fibrin_monomer_vein = x[:, 14]
	Plasminogen_lungs = x[:, 31]
	Fiber_heart = x[:, 78]
	tPA_wound = x[:, 112]
	Fibrinogen_heart = x[:, 70]
	TM_wound = x[:, 106]
	uPA_lungs = x[:, 33]
	Fiber_vein = x[:, 18]
	tPA_artery = x[:, 52]
	volume_vein = x[:, 121]
	Plasmin_heart = x[:, 69]
	Fibrin_monomer_wound = x[:, 114]
	Plasmin_wound = x[:, 109]
	antiplasmin_kidney = x[:, 96]
	TM_lungs = x[:, 26]
	Protofibril_lungs = x[:, 35]
	PC_kidney = x[:, 83]
	volume_kidney = x[:, 125]
	PAI_1_vein = x[:, 17]
	APC_heart = x[:, 64]
	ATIII_heart = x[:, 65]
	Plasmin_artery = x[:, 49]
	APC_artery = x[:, 44]
	APC_kidney = x[:, 84]
	APC_vein = x[:, 4]
	PAI_1_lungs = x[:, 37]
	Fibrinogen_wound = x[:, 110]
	ATIII_artery = x[:, 45]
	uPA_vein = x[:, 13]
	TM_kidney = x[:, 86]
	TRIGGER_heart = x[:, 67]
	TAT_kidney = x[:, 99]
	uPA_kidney = x[:, 93]
	PAI_1_wound = x[:, 117]
	volume_wound = x[:, 126]
	Fibrin_monomer_kidney = x[:, 94]
	ATIII_wound = x[:, 105]
	Fibrinogen_lungs = x[:, 30]
	FII_vein = x[:, 1]
	TRIGGER_artery = x[:, 47]
	Fibrin_monomer_artery = x[:, 54]
	tPA_lungs = x[:, 32]
	Fibrinogen_artery = x[:, 50]
	PAI_1_heart = x[:, 77]
	PAP_lungs = x[:, 40]
	PAP_heart = x[:, 80]
	FII_wound = x[:, 101]
	Protofibril_wound = x[:, 115]
	FIIa_kidney = x[:, 82]
	Plasminogen_kidney = x[:, 91]
	TRIGGER_vein = x[:, 7]
	Plasmin_vein = x[:, 9]
	PC_artery = x[:, 43]
	PAP_artery = x[:, 60]
	Fibrin_monomer_lungs = x[:, 34]
	Protofibril_heart = x[:, 75]
	APC_wound = x[:, 104]
	TRIGGER_kidney = x[:, 87]
	PC_wound = x[:, 103]
	PC_vein = x[:, 3]
	FII_heart = x[:, 61]
	TAT_heart = x[:, 79]
	Fiber_lungs = x[:, 38]
	Fiber_wound = x[:, 118]
	Plasminogen_heart = x[:, 71]
	PAP_wound = x[:, 120]
	antiplasmin_lungs = x[:, 36]
	Fibrin_artery = x[:, 48]
	uPA_wound = x[:, 113]
	antiplasmin_heart = x[:, 76]
	tPA_vein = x[:, 12]
	PAP_kidney = x[:, 100]
	FII_kidney = x[:, 81]
	Fiber_kidney = x[:, 98]
	volume_lungs = x[:, 122]
	antiplasmin_vein = x[:, 16]
	FIIa_heart = x[:, 62]
	TRIGGER_wound = x[:, 107]
	FII_lungs = x[:, 21]
	Fibrinogen_vein = x[:, 10]
	FIIa_wound = x[:, 102]
	TAT_vein = x[:, 19]
	Plasminogen_artery = x[:, 51]
	FIIa_lungs = x[:, 22]
	TM_vein = x[:, 6]
	APC_lungs = x[:, 24]
	uPA_heart = x[:, 73]
	Fibrin_kidney = x[:, 88]
	tPA_kidney = x[:, 92]
	TAT_wound = x[:, 119]
	uPA_artery = x[:, 53]
	antiplasmin_wound = x[:, 116]
	tPA_heart = x[:, 72]
	Fibrin_lungs = x[:, 28]
	volume_artery = x[:, 123]
	ATIII_vein = x[:, 5]
	PC_lungs = x[:, 23]
	PC_heart = x[:, 63]
	TRIGGER_lungs = x[:, 27]
	antiplasmin_artery = x[:, 56]
	PAI_1_kidney = x[:, 97]
	Fibrin_wound = x[:, 108]
	FII_artery = x[:, 41]
	Protofibril_vein = x[:, 15]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](4,5,1)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_wound ,linewidth=2.0,"k")
	 title("FII_wound")
	 plt[:subplot](4,5,2)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_wound ,linewidth=2.0,"k")
	 title("FIIa_wound")
	 plt[:subplot](4,5,3)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_wound ,linewidth=2.0,"k")
	 title("PC_wound")
	 plt[:subplot](4,5,4)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_wound ,linewidth=2.0,"k")
	 title("APC_wound")
	 plt[:subplot](4,5,5)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_wound ,linewidth=2.0,"k")
	 title("ATIII_wound")
	 plt[:subplot](4,5,6)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_wound ,linewidth=2.0,"k")
	 title("TM_wound")
	 plt[:subplot](4,5,7)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_wound ,linewidth=2.0,"k")
	 title("TRIGGER_wound")
	 plt[:subplot](4,5,8)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrin_wound ,linewidth=2.0,"k")
	 title("Fibrin_wound")
	 plt[:subplot](4,5,9)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Plasmin_wound ,linewidth=2.0,"k")
	 title("Plasmin_wound")
	 plt[:subplot](4,5,10)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrinogen_wound ,linewidth=2.0,"k")
	 title("Fibrinogen_wound")
	 plt[:subplot](4,5,11)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Plasminogen_wound ,linewidth=2.0,"k")
	 title("Plasminogen_wound")
	 plt[:subplot](4,5,12)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, tPA_wound ,linewidth=2.0,"k")
	 title("tPA_wound")
	 plt[:subplot](4,5,13)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, uPA_wound ,linewidth=2.0,"k")
	 title("uPA_wound")
	 plt[:subplot](4,5,14)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrin_monomer_wound ,linewidth=2.0,"k")
	 title("Fibrin_monomer_wound")
	 plt[:subplot](4,5,15)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Protofibril_wound ,linewidth=2.0,"k")
	 title("Protofibril_wound")
	 plt[:subplot](4,5,16)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, antiplasmin_wound ,linewidth=2.0,"k")
	 title("antiplasmin_wound")
	 plt[:subplot](4,5,17)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PAI_1_wound ,linewidth=2.0,"k")
	 title("PAI_1_wound")
	 plt[:subplot](4,5,18)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fiber_wound ,linewidth=2.0,"k")
	 title("Fiber_wound")
	 plt[:subplot](4,5,19)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TAT_wound ,linewidth=2.0,"k")
	 title("TAT_wound")
	 plt[:subplot](4,5,20)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PAP_wound ,linewidth=2.0,"k")
	 title("PAP_wound")

	savefig("withactualparms.png")

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](3.0,3.0,1)
	 plot(t, volume_vein)
	 title("volume_vein")
	 plt[:subplot](3.0,3.0,2)
	 plot(t, volume_lungs)
	 title("volume_lungs")
	 plt[:subplot](3.0,3.0,3)
	 plot(t, volume_artery)
	 title("volume_artery")
	 plt[:subplot](3.0,3.0,4)
	 plot(t, volume_heart)
	 title("volume_heart")
	 plt[:subplot](3.0,3.0,5)
	 plot(t, volume_kidney)
	 title("volume_kidney")
	 plt[:subplot](3.0,3.0,6)
	 plot(t, volume_wound)
	 title("volume_wound")
	 end
runModel()
