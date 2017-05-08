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
	E1_kidney = x[:, 18]
	volume_wound = x[:, 30]
	E1_vein = x[:, 2]
	D1_heart = x[:, 16]
	E0_artery = x[:, 11]
	Z1_wound = x[:, 21]
	E0_lungs = x[:, 7]
	Z1_artery = x[:, 9]
	volume_vein = x[:, 25]
	E1_artery = x[:, 10]
	volume_lungs = x[:, 26]
	volume_kidney = x[:, 29]
	E0_kidney = x[:, 19]
	Z1_kidney = x[:, 17]
	D1_lungs = x[:, 8]
	E1_wound = x[:, 22]
	E1_lungs = x[:, 6]
	D1_wound = x[:, 24]
	D1_vein = x[:, 4]
	E0_vein = x[:, 3]
	volume_heart = x[:, 28]
	Z1_lungs = x[:, 5]
	D1_kidney = x[:, 20]
	E0_wound = x[:, 23]
	Z1_heart = x[:, 13]
	E1_heart = x[:, 14]
	volume_artery = x[:, 27]
	E0_heart = x[:, 15]
	D1_artery = x[:, 12]
	Z1_vein = x[:, 1]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](5.0,5.0,1)
	 plot(t, Z1_wound)
	 title("Z1_wound")
	 plt[:subplot](5.0,5.0,2)
	 plot(t, E1_wound)
	 title("E1_wound")
	 plt[:subplot](5.0,5.0,3)
	 plot(t, E0_wound)
	 title("E0_wound")
	 plt[:subplot](5.0,5.0,4)
	 plot(t, D1_wound)
	 title("D1_wound")
	 plt[:subplot](5.0,5.0,5)
	 plot(t, Z1_artery)
	 title("Z1_artery")
	 plt[:subplot](5.0,5.0,6)
	 plot(t, E1_artery)
	 title("E1_artery")
	 plt[:subplot](5.0,5.0,7)
	 plot(t, E0_artery)
	 title("E0_artery")
	 plt[:subplot](5.0,5.0,8)
	 plot(t, D1_artery)
	 title("D1_artery")
	 plt[:subplot](5.0,5.0,9)
	 plot(t, Z1_vein)
	 title("Z1_vein")
	 plt[:subplot](5.0,5.0,10)
	 plot(t, E1_vein)
	 title("E1_vein")
	 plt[:subplot](5.0,5.0,11)
	 plot(t, E0_vein)
	 title("E0_vein")
	 plt[:subplot](5.0,5.0,12)
	 plot(t, D1_vein)
	 title("D1_vein")
	 plt[:subplot](5.0,5.0,13)
	 plot(t, Z1_heart)
	 title("Z1_heart")
	 plt[:subplot](5.0,5.0,14)
	 plot(t, E1_heart)
	 title("E1_heart")
	 plt[:subplot](5.0,5.0,15)
	 plot(t, E0_heart)
	 title("E0_heart")
	 plt[:subplot](5.0,5.0,16)
	 plot(t, D1_heart)
	 title("D1_heart")
	 plt[:subplot](5.0,5.0,17)
	 plot(t, Z1_lungs)
	 title("Z1_lungs")
	 plt[:subplot](5.0,5.0,18)
	 plot(t, E1_lungs)
	 title("E1_lungs")
	 plt[:subplot](5.0,5.0,19)
	 plot(t, E0_lungs)
	 title("E0_lungs")
	 plt[:subplot](5.0,5.0,20)
	 plot(t, D1_lungs)
	 title("D1_lungs")
	 plt[:subplot](5.0,5.0,21)
	 plot(t, Z1_kidney)
	 title("Z1_kidney")
	 plt[:subplot](5.0,5.0,22)
	 plot(t, E1_kidney)
	 title("E1_kidney")
	 plt[:subplot](5.0,5.0,23)
	 plot(t, E0_kidney)
	 title("E0_kidney")
	 plt[:subplot](5.0,5.0,24)
	 plot(t, D1_kidney)
	 title("D1_kidney")
	 end
runModel()
