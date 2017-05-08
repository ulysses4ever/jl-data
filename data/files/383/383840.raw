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
	FIIa_vein = x[:, 2]
	APC_lungs = x[:, 11]
	APC_wound = x[:, 39]
	volume_heart = x[:, 46]
	APC_heart = x[:, 25]
	TRIGGER_wound = x[:, 42]
	FII_kidney = x[:, 29]
	FII_lungs = x[:, 8]
	TM_artery = x[:, 20]
	TRIGGER_lungs = x[:, 14]
	PC_kidney = x[:, 31]
	ATIII_kidney = x[:, 33]
	APC_artery = x[:, 18]
	ATIII_heart = x[:, 26]
	TRIGGER_kidney = x[:, 35]
	PC_artery = x[:, 17]
	volume_lungs = x[:, 44]
	APC_vein = x[:, 4]
	FIIa_wound = x[:, 37]
	volume_artery = x[:, 45]
	TM_lungs = x[:, 13]
	FIIa_kidney = x[:, 30]
	FII_vein = x[:, 1]
	volume_kidney = x[:, 47]
	APC_kidney = x[:, 32]
	ATIII_wound = x[:, 40]
	TRIGGER_vein = x[:, 7]
	FIIa_lungs = x[:, 9]
	volume_vein = x[:, 43]
	TM_kidney = x[:, 34]
	PC_vein = x[:, 3]
	PC_wound = x[:, 38]
	FII_wound = x[:, 36]
	volume_wound = x[:, 48]
	ATIII_lungs = x[:, 12]
	FIIa_artery = x[:, 16]
	TRIGGER_artery = x[:, 21]
	PC_lungs = x[:, 10]
	ATIII_artery = x[:, 19]
	FII_heart = x[:, 22]
	TM_vein = x[:, 6]
	PC_heart = x[:, 24]
	TRIGGER_heart = x[:, 28]
	ATIII_vein = x[:, 5]
	FIIa_heart = x[:, 23]
	TM_heart = x[:, 27]
	TM_wound = x[:, 41]
	FII_artery = x[:, 15]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](5,7,1)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_wound ,linewidth=2.0,"k")
	 title("FII_wound")
	 plt[:subplot](5,7,2)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FIIa_wound ,linewidth=2.0,"k")
	 title("FIIa_wound")
	 plt[:subplot](5,7,3)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, PC_wound ,linewidth=2.0,"k")
	 title("PC_wound")
	 plt[:subplot](5,7,4)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, APC_wound ,linewidth=2.0,"k")
	 title("APC_wound")
	 plt[:subplot](5,7,5)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, ATIII_wound ,linewidth=2.0,"k")
	 title("ATIII_wound")
	 plt[:subplot](5,7,6)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TM_wound ,linewidth=2.0,"k")
	 title("TM_wound")
	 plt[:subplot](5,7,7)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TRIGGER_wound ,linewidth=2.0,"k")
	 title("TRIGGER_wound")
	 plt[:subplot](5,7,8)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FII_vein ,linewidth=2.0,"k")
	 title("FII_vein")
	 plt[:subplot](5,7,9)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FIIa_vein ,linewidth=2.0,"k")
	 title("FIIa_vein")
	 plt[:subplot](5,7,10)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, PC_vein ,linewidth=2.0,"k")
	 title("PC_vein")
	 plt[:subplot](5,7,11)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, APC_vein ,linewidth=2.0,"k")
	 title("APC_vein")
	 plt[:subplot](5,7,12)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, ATIII_vein ,linewidth=2.0,"k")
	 title("ATIII_vein")
	 plt[:subplot](5,7,13)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TM_vein ,linewidth=2.0,"k")
	 title("TM_vein")
	 plt[:subplot](5,7,14)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TRIGGER_vein ,linewidth=2.0,"k")
	 title("TRIGGER_vein")
	 plt[:subplot](5,7,15)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FII_artery ,linewidth=2.0,"k")
	 title("FII_artery")
	 plt[:subplot](5,7,16)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FIIa_artery ,linewidth=2.0,"k")
	 title("FIIa_artery")
	 plt[:subplot](5,7,17)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, PC_artery ,linewidth=2.0,"k")
	 title("PC_artery")
	 plt[:subplot](5,7,18)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, APC_artery ,linewidth=2.0,"k")
	 title("APC_artery")
	 plt[:subplot](5,7,19)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, ATIII_artery ,linewidth=2.0,"k")
	 title("ATIII_artery")
	 plt[:subplot](5,7,20)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TM_artery ,linewidth=2.0,"k")
	 title("TM_artery")
	 plt[:subplot](5,7,21)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TRIGGER_artery ,linewidth=2.0,"k")
	 title("TRIGGER_artery")
	 plt[:subplot](5,7,22)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FII_heart ,linewidth=2.0,"k")
	 title("FII_heart")
	 plt[:subplot](5,7,23)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FIIa_heart ,linewidth=2.0,"k")
	 title("FIIa_heart")
	 plt[:subplot](5,7,24)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, PC_heart ,linewidth=2.0,"k")
	 title("PC_heart")
	 plt[:subplot](5,7,25)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, APC_heart ,linewidth=2.0,"k")
	 title("APC_heart")
	 plt[:subplot](5,7,26)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, ATIII_heart ,linewidth=2.0,"k")
	 title("ATIII_heart")
	 plt[:subplot](5,7,27)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TM_heart ,linewidth=2.0,"k")
	 title("TM_heart")
	 plt[:subplot](5,7,28)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TRIGGER_heart ,linewidth=2.0,"k")
	 title("TRIGGER_heart")
	 plt[:subplot](5,7,29)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FII_kidney ,linewidth=2.0,"k")
	 title("FII_kidney")
	 plt[:subplot](5,7,30)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, FIIa_kidney ,linewidth=2.0,"k")
	 title("FIIa_kidney")
	 plt[:subplot](5,7,31)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, PC_kidney ,linewidth=2.0,"k")
	 title("PC_kidney")
	 plt[:subplot](5,7,32)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, APC_kidney ,linewidth=2.0,"k")
	 title("APC_kidney")
	 plt[:subplot](5,7,33)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, ATIII_kidney ,linewidth=2.0,"k")
	 title("ATIII_kidney")
	 plt[:subplot](5,7,34)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TM_kidney ,linewidth=2.0,"k")
	 title("TM_kidney")
	 plt[:subplot](5,7,35)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plot(t, TRIGGER_kidney ,linewidth=2.0,"k")
	 title("TRIGGER_kidney")

	savefig("ReducedOrderModelWFlow.pdf")

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
