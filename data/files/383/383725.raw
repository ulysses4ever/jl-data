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
	 step=0.002
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	FIIa_vein = x[:, 2]
	APC_heart = x[:, 11]
	APC_liver = x[:, 39]
	APC_bulk = x[:, 46]
	APC_artery = x[:, 25]
	TM_wound = x[:, 55]
	TRIGGER_liver = x[:, 42]
	FII_kidney = x[:, 29]
	volume_heart = x[:, 58]
	volume_lungs = x[:, 59]
	FII_heart = x[:, 8]
	volume_vein = x[:, 57]
	TM_lungs = x[:, 20]
	TRIGGER_heart = x[:, 14]
	PC_kidney = x[:, 31]
	ATIII_kidney = x[:, 33]
	APC_lungs = x[:, 18]
	PC_wound = x[:, 52]
	ATIII_artery = x[:, 26]
	TRIGGER_kidney = x[:, 35]
	PC_lungs = x[:, 17]
	volume_wound = x[:, 64]
	TRIGGER_bulk = x[:, 49]
	FIIa_bulk = x[:, 44]
	APC_vein = x[:, 4]
	FIIa_liver = x[:, 37]
	PC_bulk = x[:, 45]
	TM_heart = x[:, 13]
	FIIa_kidney = x[:, 30]
	FII_vein = x[:, 1]
	ATIII_bulk = x[:, 47]
	ATIII_wound = x[:, 54]
	APC_kidney = x[:, 32]
	FII_wound = x[:, 50]
	ATIII_liver = x[:, 40]
	TRIGGER_vein = x[:, 7]
	FIIa_heart = x[:, 9]
	FII_bulk = x[:, 43]
	volume_artery = x[:, 60]
	TM_kidney = x[:, 34]
	PC_vein = x[:, 3]
	volume_kidney = x[:, 61]
	PC_liver = x[:, 38]
	FII_liver = x[:, 36]
	TM_bulk = x[:, 48]
	ATIII_heart = x[:, 12]
	FIIa_lungs = x[:, 16]
	volume_liver = x[:, 62]
	TRIGGER_lungs = x[:, 21]
	PC_heart = x[:, 10]
	ATIII_lungs = x[:, 19]
	FIIa_wound = x[:, 51]
	FII_artery = x[:, 22]
	TM_vein = x[:, 6]
	PC_artery = x[:, 24]
	APC_wound = x[:, 53]
	TRIGGER_artery = x[:, 28]
	ATIII_vein = x[:, 5]
	FIIa_artery = x[:, 23]
	volume_bulk = x[:, 63]
	TM_artery = x[:, 27]
	TRIGGER_wound = x[:, 56]
	TM_liver = x[:, 41]
	FII_lungs = x[:, 15]

	 #code to plot, using subplots
	 figure(figsize=(30,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](8,7,1)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_wound ,linewidth=2.0,"k")
	 title("FII_wound")
	 plt[:subplot](8,7,2)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_wound ,linewidth=2.0,"k")
	 title("FIIa_wound")
	 plt[:subplot](8,7,3)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_wound ,linewidth=2.0,"k")
	 title("PC_wound")
	 plt[:subplot](8,7,4)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_wound ,linewidth=2.0,"k")
	 title("APC_wound")
	 plt[:subplot](8,7,5)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_wound ,linewidth=2.0,"k")
	 title("ATIII_wound")
	 plt[:subplot](8,7,6)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_wound ,linewidth=2.0,"k")
	 title("TM_wound")
	 plt[:subplot](8,7,7)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_wound ,linewidth=2.0,"k")
	 title("TRIGGER_wound")
	 plt[:subplot](8,7,8)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_vein ,linewidth=2.0,"k")
	 title("FII_vein")
	 plt[:subplot](8,7,9)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_vein ,linewidth=2.0,"k")
	 title("FIIa_vein")
	 plt[:subplot](8,7,10)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_vein ,linewidth=2.0,"k")
	 title("PC_vein")
	 plt[:subplot](8,7,11)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_vein ,linewidth=2.0,"k")
	 title("APC_vein")
	 plt[:subplot](8,7,12)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_vein ,linewidth=2.0,"k")
	 title("ATIII_vein")
	 plt[:subplot](8,7,13)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_vein ,linewidth=2.0,"k")
	 title("TM_vein")
	 plt[:subplot](8,7,14)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_vein ,linewidth=2.0,"k")
	 title("TRIGGER_vein")
	 plt[:subplot](8,7,15)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_artery ,linewidth=2.0,"k")
	 title("FII_artery")
	 plt[:subplot](8,7,16)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_artery ,linewidth=2.0,"k")
	 title("FIIa_artery")
	 plt[:subplot](8,7,17)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_artery ,linewidth=2.0,"k")
	 title("PC_artery")
	 plt[:subplot](8,7,18)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_artery ,linewidth=2.0,"k")
	 title("APC_artery")
	 plt[:subplot](8,7,19)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_artery ,linewidth=2.0,"k")
	 title("ATIII_artery")
	 plt[:subplot](8,7,20)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_artery ,linewidth=2.0,"k")
	 title("TM_artery")
	 plt[:subplot](8,7,21)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_artery ,linewidth=2.0,"k")
	 title("TRIGGER_artery")
	 plt[:subplot](8,7,22)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_heart ,linewidth=2.0,"k")
	 title("FII_heart")
	 plt[:subplot](8,7,23)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_heart ,linewidth=2.0,"k")
	 title("FIIa_heart")
	 plt[:subplot](8,7,24)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_heart ,linewidth=2.0,"k")
	 title("PC_heart")
	 plt[:subplot](8,7,25)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_heart ,linewidth=2.0,"k")
	 title("APC_heart")
	 plt[:subplot](8,7,26)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_heart ,linewidth=2.0,"k")
	 title("ATIII_heart")
	 plt[:subplot](8,7,27)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_heart ,linewidth=2.0,"k")
	 title("TM_heart")
	 plt[:subplot](8,7,28)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_heart ,linewidth=2.0,"k")
	 title("TRIGGER_heart")
	 plt[:subplot](8,7,29)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_kidney ,linewidth=2.0,"k")
	 title("FII_kidney")
	 plt[:subplot](8,7,30)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_kidney ,linewidth=2.0,"k")
	 title("FIIa_kidney")
	 plt[:subplot](8,7,31)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_kidney ,linewidth=2.0,"k")
	 title("PC_kidney")
	 plt[:subplot](8,7,32)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_kidney ,linewidth=2.0,"k")
	 title("APC_kidney")
	 plt[:subplot](8,7,33)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_kidney ,linewidth=2.0,"k")
	 title("ATIII_kidney")
	 plt[:subplot](8,7,34)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_kidney ,linewidth=2.0,"k")
	 title("TM_kidney")
	 plt[:subplot](8,7,35)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_kidney ,linewidth=2.0,"k")
	 title("TRIGGER_kidney")
	 plt[:subplot](8,7,36)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_lungs ,linewidth=2.0,"k")
	 title("FII_lungs")
	 plt[:subplot](8,7,37)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_lungs ,linewidth=2.0,"k")
	 title("FIIa_lungs")
	 plt[:subplot](8,7,38)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_lungs ,linewidth=2.0,"k")
	 title("PC_lungs")
	 plt[:subplot](8,7,39)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_lungs ,linewidth=2.0,"k")
	 title("APC_lungs")
	 plt[:subplot](8,7,40)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_lungs ,linewidth=2.0,"k")
	 title("ATIII_lungs")
	 plt[:subplot](8,7,41)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_lungs ,linewidth=2.0,"k")
	 title("TM_lungs")
	 plt[:subplot](8,7,42)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_lungs ,linewidth=2.0,"k")
	 title("TRIGGER_lungs")
	 plt[:subplot](8,7,43)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_liver ,linewidth=2.0,"k")
	 title("FII_liver")
	 plt[:subplot](8,7,44)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_liver ,linewidth=2.0,"k")
	 title("FIIa_liver")
	 plt[:subplot](8,7,45)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_liver ,linewidth=2.0,"k")
	 title("PC_liver")
	 plt[:subplot](8,7,46)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_liver ,linewidth=2.0,"k")
	 title("APC_liver")
	 plt[:subplot](8,7,47)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_liver ,linewidth=2.0,"k")
	 title("ATIII_liver")
	 plt[:subplot](8,7,48)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_liver ,linewidth=2.0,"k")
	 title("TM_liver")
	 plt[:subplot](8,7,49)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_liver ,linewidth=2.0,"k")
	 title("TRIGGER_liver")
	 plt[:subplot](8,7,50)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_bulk ,linewidth=2.0,"k")
	 title("FII_bulk")
	 plt[:subplot](8,7,51)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_bulk ,linewidth=2.0,"k")
	 title("FIIa_bulk")
	 plt[:subplot](8,7,52)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_bulk ,linewidth=2.0,"k")
	 title("PC_bulk")
	 plt[:subplot](8,7,53)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_bulk ,linewidth=2.0,"k")
	 title("APC_bulk")
	 plt[:subplot](8,7,54)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_bulk ,linewidth=2.0,"k")
	 title("ATIII_bulk")
	 plt[:subplot](8,7,55)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TM_bulk ,linewidth=2.0,"k")
	 title("TM_bulk")
	 plt[:subplot](8,7,56)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TRIGGER_bulk ,linewidth=2.0,"k")
	 title("TRIGGER_bulk")
	#println("should have saved")
	#savefig("usingPressureTrackFromPatient_s01004-2531-07-20-08-50n.png")

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](3.0,3.0,1)
	 plot(t, volume_vein)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_vein")
	 plt[:subplot](3.0,3.0,2)
	 plot(t, volume_heart)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_heart")
	 plt[:subplot](3.0,3.0,3)
	 plot(t, volume_lungs)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_lungs")
	 plt[:subplot](3.0,3.0,4)
	 plot(t, volume_artery)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_artery")
	 plt[:subplot](3.0,3.0,5)
	 plot(t, volume_kidney)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_kidney")
	 plt[:subplot](3.0,3.0,6)
	 plot(t, volume_liver)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_liver")
	 plt[:subplot](3.0,3.0,7)
	 plot(t, volume_bulk)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_bulk")
	 plt[:subplot](3.0,3.0,8)
	 plot(t, volume_wound)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 title("volume_wound")

	combinedArr = [transpose(reshape(t,1,length(t))) x]
	@show combinedArr
	writedlm("outputs/HeartRateConst100.csv", combinedArr)
	 end
runModel()
