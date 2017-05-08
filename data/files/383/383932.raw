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
	 tend=2.5
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	volume_lungs = x[:, 68]
	E1_vein = x[:, 2]
	D4_vein = x[:, 11]
	D2_heart = x[:, 39]
	E1_kidney = x[:, 46]
	D1_artery = x[:, 25]
	D4_kidney = x[:, 55]
	D3_heart = x[:, 42]
	E3_artery = x[:, 29]
	D1_wound = x[:, 58]
	D4_wound = x[:, 66]
	Z2_wound = x[:, 59]
	E4_vein = x[:, 8]
	E1_wound = x[:, 57]
	D3_lungs = x[:, 20]
	D1_lungs = x[:, 14]
	D3_artery = x[:, 31]
	volume_heart = x[:, 70]
	D4_artery = x[:, 33]
	E3_lungs = x[:, 18]
	E4_kidney = x[:, 52]
	volume_artery = x[:, 69]
	Z2_artery = x[:, 26]
	E1_heart = x[:, 35]
	D2_lungs = x[:, 17]
	D3_wound = x[:, 64]
	Z4_wound = x[:, 65]
	E2_kidney = x[:, 49]
	D4_heart = x[:, 44]
	Z2_vein = x[:, 4]
	Z2_heart = x[:, 37]
	Z1_kidney = x[:, 45]
	E1_lungs = x[:, 13]
	volume_vein = x[:, 67]
	E4_artery = x[:, 30]
	Z1_vein = x[:, 1]
	D1_kidney = x[:, 47]
	Z4_kidney = x[:, 54]
	Z4_artery = x[:, 32]
	D2_kidney = x[:, 50]
	E3_heart = x[:, 40]
	E3_vein = x[:, 7]
	D3_vein = x[:, 9]
	Z4_heart = x[:, 43]
	E2_wound = x[:, 60]
	Z1_heart = x[:, 34]
	D1_vein = x[:, 3]
	D2_wound = x[:, 61]
	E2_heart = x[:, 38]
	volume_kidney = x[:, 71]
	D1_heart = x[:, 36]
	Z2_kidney = x[:, 48]
	Z1_lungs = x[:, 12]
	E2_lungs = x[:, 16]
	E3_wound = x[:, 62]
	Z4_lungs = x[:, 21]
	Z4_vein = x[:, 10]
	E4_lungs = x[:, 19]
	E3_kidney = x[:, 51]
	D4_lungs = x[:, 22]
	D2_vein = x[:, 6]
	E1_artery = x[:, 24]
	D3_kidney = x[:, 53]
	volume_wound = x[:, 72]
	D2_artery = x[:, 28]
	E2_vein = x[:, 5]
	Z1_artery = x[:, 23]
	E4_wound = x[:, 63]
	E2_artery = x[:, 27]
	Z1_wound = x[:, 56]
	E4_heart = x[:, 41]
	Z2_lungs = x[:, 15]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](6.0,6.0,1)
	 plot(t, Z1_wound)
	 title("Z1_wound")
	 plt[:subplot](6.0,6.0,2)
	 plot(t, E1_wound)
	 title("E1_wound")
	 plt[:subplot](6.0,6.0,3)
	 plot(t, D1_wound)
	 title("D1_wound")
	 plt[:subplot](6.0,6.0,4)
	 plot(t, Z2_wound)
	 title("Z2_wound")
	 plt[:subplot](6.0,6.0,5)
	 plot(t, E2_wound)
	 title("E2_wound")
	 plt[:subplot](6.0,6.0,6)
	 plot(t, D2_wound)
	 title("D2_wound")
	 plt[:subplot](6.0,6.0,7)
	 plot(t, E3_wound)
	 title("E3_wound")
	 plt[:subplot](6.0,6.0,8)
	 plot(t, E4_wound)
	 title("E4_wound")
	 plt[:subplot](6.0,6.0,9)
	 plot(t, D3_wound)
	 title("D3_wound")
	 plt[:subplot](6.0,6.0,10)
	 plot(t, Z4_wound)
	 title("Z4_wound")
	 plt[:subplot](6.0,6.0,11)
	 plot(t, D4_wound)
	 title("D4_wound")
	 plt[:subplot](6.0,6.0,12)
	 plot(t, Z1_vein)
	 title("Z1_vein")
	 plt[:subplot](6.0,6.0,13)
	 plot(t, E1_vein)
	 title("E1_vein")
	 plt[:subplot](6.0,6.0,14)
	 plot(t, D1_vein)
	 title("D1_vein")
	 plt[:subplot](6.0,6.0,15)
	 plot(t, Z2_vein)
	 title("Z2_vein")
	 plt[:subplot](6.0,6.0,16)
	 plot(t, E2_vein)
	 title("E2_vein")
	 plt[:subplot](6.0,6.0,17)
	 plot(t, D2_vein)
	 title("D2_vein")
	 plt[:subplot](6.0,6.0,18)
	 plot(t, E3_vein)
	 title("E3_vein")
	 plt[:subplot](6.0,6.0,19)
	 plot(t, E4_vein)
	 title("E4_vein")
	 plt[:subplot](6.0,6.0,20)
	 plot(t, D3_vein)
	 title("D3_vein")
	 plt[:subplot](6.0,6.0,21)
	 plot(t, Z4_vein)
	 title("Z4_vein")
	 plt[:subplot](6.0,6.0,22)
	 plot(t, D4_vein)
	 title("D4_vein")
	 plt[:subplot](6.0,6.0,23)
	 plot(t, Z1_artery)
	 title("Z1_artery")
	 plt[:subplot](6.0,6.0,24)
	 plot(t, E1_artery)
	 title("E1_artery")
	 plt[:subplot](6.0,6.0,25)
	 plot(t, D1_artery)
	 title("D1_artery")
	 plt[:subplot](6.0,6.0,26)
	 plot(t, Z2_artery)
	 title("Z2_artery")
	 plt[:subplot](6.0,6.0,27)
	 plot(t, E2_artery)
	 title("E2_artery")
	 plt[:subplot](6.0,6.0,28)
	 plot(t, D2_artery)
	 title("D2_artery")
	 plt[:subplot](6.0,6.0,29)
	 plot(t, E3_artery)
	 title("E3_artery")
	 plt[:subplot](6.0,6.0,30)
	 plot(t, E4_artery)
	 title("E4_artery")
	 plt[:subplot](6.0,6.0,31)
	 plot(t, D3_artery)
	 title("D3_artery")
	 plt[:subplot](6.0,6.0,32)
	 plot(t, Z4_artery)
	 title("Z4_artery")
	 plt[:subplot](6.0,6.0,33)
	 plot(t, D4_artery)
	 title("D4_artery")

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
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
