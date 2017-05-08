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
	Z2_wound = x[:, 18]
	volume_C1 = x[:, 30]
	volume_C2 = x[:, 32]
	E1_supply = x[:, 2]
	E1_wound = x[:, 16]
	Z2_C1 = x[:, 11]
	D2_wound = x[:, 21]
	D2_supply = x[:, 7]
	E1_C1 = x[:, 9]
	Z2_C2 = x[:, 25]
	E0_C1 = x[:, 10]
	E2_C2 = x[:, 26]
	volume_supply = x[:, 29]
	E2_wound = x[:, 19]
	E0_wound = x[:, 17]
	Z1_C1 = x[:, 8]
	Z1_C2 = x[:, 22]
	D1_supply = x[:, 6]
	E0_C2 = x[:, 24]
	Z2_supply = x[:, 4]
	E0_supply = x[:, 3]
	D2_C2 = x[:, 28]
	E2_supply = x[:, 5]
	D1_wound = x[:, 20]
	E1_C2 = x[:, 23]
	D1_C1 = x[:, 13]
	D2_C1 = x[:, 14]
	volume_wound = x[:, 31]
	D1_C2 = x[:, 27]
	Z1_wound = x[:, 15]
	E2_C1 = x[:, 12]
	Z1_supply = x[:, 1]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](3,7,1)
	 plot(t, Z1_C1)
	 #title("Z1_C1")
	 plt[:subplot](3,7,2)
	 plot(t, E1_C1)
	 #title("E1_C1")
	 plt[:subplot](3,7,3)
	 plot(t, E0_C1)
	 #title("E0_C1")
	 plt[:subplot](3,7,4)
	 plot(t, Z2_C1)
	 #title("Z2_C1")
	 plt[:subplot](3,7,5)
	 plot(t, E2_C1)
	 #title("E2_C1")
	 plt[:subplot](3,7,6)
	 plot(t, D1_C1)
	 #title("D1_C1")
	 plt[:subplot](3,7,7)
	 plot(t, D2_C1)
	 #title("D2_C1")
	 plt[:subplot](3,7,8)
	 plot(t, Z1_wound)
	 #title("Z1_wound")
	 plt[:subplot](3,7,9)
	 plot(t, E1_wound)
	 #title("E1_wound")
	 plt[:subplot](3,7,10)
	 plot(t, E0_wound)
	 #title("E0_wound")
	 plt[:subplot](3,7,11)
	 plot(t, Z2_wound)
	 #title("Z2_wound")
	 plt[:subplot](3,7,12)
	 plot(t, E2_wound)
	 #title("E2_wound")
	 plt[:subplot](3,7,13)
	 plot(t, D1_wound)
	 #title("D1_wound")
	 plt[:subplot](3,7,14)
	 plot(t, D2_wound)
	 #title("D2_wound")
	 plt[:subplot](3,7,15)
	 plot(t, Z1_C2)
	 #title("Z1_C2")
	 plt[:subplot](3,7,16)
	 plot(t, E1_C2)
	 #title("E1_C2")
	 plt[:subplot](3,7,17)
	 plot(t, E0_C2)
	 #title("E0_C2")
	 plt[:subplot](3,7,18)
	 plot(t, Z2_C2)
	 #title("Z2_C2")
	 plt[:subplot](3,7,19)
	 plot(t, E2_C2)
	 #title("E2_C2")
	 plt[:subplot](3,7,20)
	 plot(t, D1_C2)
	 #title("D1_C2")
	 plt[:subplot](3,7,21)
	 plot(t, D2_C2)
	 #title("D2_C2")
	savefig("figure.png")

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](1,4,1)
	 plot(t, volume_supply)
	 #title("volume_supply")
	 plt[:subplot](1,4,2)
	 plot(t, volume_C1)
	 #title("volume_C1")
	 plt[:subplot](1,4,3)
	 plot(t, volume_wound)
	 #title("volume_wound")
	 plt[:subplot](1,4,4)
	 plot(t, volume_C2)
	 #title("volume_C2")
	 end
runModel()
