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
	 tend=45
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	savestr = "output/HRfofbleedout"
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
	 volumecounter = 1
	 volumeoffset = 56
	 plotcounter = 1
	 j=1
	 upperlim = 64

	while(plotcounter<=upperlim)
		adjustedplotcounter = plotcounter -1
		if(mod(plotcounter,8)==0)
			plt[:subplot](8,8,plotcounter)
			currindex = volumeoffset+volumecounter

			plt[:tick_params](axis="both", which="major", labelsize=7)
			plt[:tick_params](axis="both", which="minor", labelsize=7)
			plt[:ticklabel_format](axis="y", useOffset=false)

			plot(t,x[:,currindex] ,linewidth=2.0,color = "k")
			plotcounter = plotcounter+1
			volumecounter = volumecounter+1
			adjustedplotcounter = plotcounter -1
		end
		if(plotcounter>upperlim)
			break
		end

		plt[:subplot](8,8,plotcounter)
		plt[:tick_params](axis="both", which="major", labelsize=7)
		plt[:tick_params](axis="both", which="minor", labelsize=7)
		plt[:ticklabel_format](axis="y", useOffset=false)
		plot(t,x[:,j] ,linewidth=2.0,color = "k")
		
		plotcounter = plotcounter+1
		j=j+1
	end	 
	
	#make y-axis same for each component 
	components = 8
	for j in collect(1:64)
		plt[:subplot](8,8,j)
		ax = gca()
		correctedindex = j-1
		if(mod(correctedindex,components)==0)
			ax[:set_ylim]([0,1400])
		elseif(mod(correctedindex,components)==1)
			ax[:set_ylim]([0,250])
		elseif(mod(correctedindex,components)==2)
			ax[:set_ylim]([0,60])
		elseif(mod(correctedindex,components)==3)
			ax[:set_ylim]([0,20])
		elseif(mod(correctedindex,components)==4)
			ax[:set_ylim]([0,5000])
		elseif(mod(correctedindex,components)==5)
			ax[:set_ylim]([10, 60])
		elseif(mod(correctedindex,components)==6)
			ax[:set_ylim]([0,.2])
		elseif(mod(correctedindex,components)==8)
			ax[:set_ylim]([0,.2])
		end

		#plt[:subplot](8,8,j)
		#ax = gca()
		#ax[:set_xticklabels]([])
		#ax[:set_yticklabels]([])
	end

	savefig(string(savestr,".pdf"))

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](3.0,3.0,1)
	 plot(t, volume_vein)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_vein")
	 plt[:subplot](3.0,3.0,2)
	 plot(t, volume_heart)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_heart")
	 plt[:subplot](3.0,3.0,3)
	 plot(t, volume_lungs)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_lungs")
	 plt[:subplot](3.0,3.0,4)
	 plot(t, volume_artery)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_artery")
	 plt[:subplot](3.0,3.0,5)
	 plot(t, volume_kidney)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_kidney")
	 plt[:subplot](3.0,3.0,6)
	 plot(t, volume_liver)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_liver")
	 plt[:subplot](3.0,3.0,components)
	 plot(t, volume_bulk)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_bulk")
	 plt[:subplot](3.0,3.0,8)
	 plot(t, volume_wound)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 #title("volume_wound")

	savefig(string(savestr, "vols", ".pdf"))

	combinedArr = [transpose(reshape(t,1,length(t))) x]
	#@show combinedArr
	writedlm(string(savestr,".csv"), combinedArr)
	 end
runModel()
