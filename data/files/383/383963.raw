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
	 tend=1.2
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	E0_compartment_1 = x[:, 7]
	D1_wound = x[:, 4]
	volume_wound = x[:, 9]
	volume_compartment_1 = x[:, 10]
	E1_wound = x[:, 2]
	E0_wound = x[:, 3]
	Z1_compartment_1 = x[:, 5]
	D1_compartment_1 = x[:, 8]
	E1_compartment_1 = x[:, 6]
	Z1_wound = x[:, 1]

	 #code to plot, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](1,4,1)
	 plot(t, Z1_wound)
	 title("Z1_wound")
	 plt[:subplot](1,4,2)
	 plot(t, E1_wound)
	 title("E1_wound")
	 plt[:subplot](1,4,3)
	 plot(t, E0_wound)
	 title("E0_wound")
	 plt[:subplot](1,4,4)
	 plot(t, D1_wound)
	 title("D1_wound")
	 end
runModel()
