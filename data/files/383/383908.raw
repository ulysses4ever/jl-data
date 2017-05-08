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
function runMode()
	 close("all") #close already open windows
	#set start time, stop time and step sizes
	 tstart=0
	 tend=0.5
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	MASP1_2_C1 = x[:, 2]
	Ag_Ab_C1 = x[:, 11]
	C2_C2 = x[:, 39]
	microbes_C2 = x[:, 46]
	C3bBb3b_C1 = x[:, 25]
	C4b2a3b_C2 = x[:, 55]
	Ag_Ab_C2 = x[:, 42]
	C5b_C1 = x[:, 29]
	C4bBb3b_C2 = x[:, 58]
	C5a_C2 = x[:, 59]
	C2_C1 = x[:, 8]
	C5_C2 = x[:, 57]
	properdin_C1 = x[:, 20]
	C3b_C1 = x[:, 14]
	C6_C9_C1 = x[:, 31]
	MASP1_2_C2 = x[:, 33]
	factor_D_C1 = x[:, 18]
	C3bBb_C2 = x[:, 52]
	C5_C1 = x[:, 26]
	C4_C2 = x[:, 35]
	factor_B_C1 = x[:, 17]
	volume_C2 = x[:, 64]
	factor_D_C2 = x[:, 49]
	C3a_C2 = x[:, 44]
	C4_C1 = x[:, 4]
	C4b_C2 = x[:, 37]
	C3b_C2 = x[:, 45]
	C3a_C1 = x[:, 13]
	MAC_C1 = x[:, 30]
	MBL_C1 = x[:, 1]
	Bb_C2 = x[:, 47]
	C4b2a_C2 = x[:, 54]
	MBL_C2 = x[:, 32]
	Ba_C2 = x[:, 50]
	C1_C2 = x[:, 40]
	C4b2_C1 = x[:, 7]
	C1_C1 = x[:, 9]
	C3_C2 = x[:, 43]
	C5b_C2 = x[:, 60]
	C1_a_similar_C2 = x[:, 34]
	C1_a_similar_C1 = x[:, 3]
	MAC_C2 = x[:, 61]
	C4b2_C2 = x[:, 38]
	C4a_C2 = x[:, 36]
	factor_B_C2 = x[:, 48]
	C3_C1 = x[:, 12]
	Bb_C1 = x[:, 16]
	C6_C9_C2 = x[:, 62]
	C3bBb_C1 = x[:, 21]
	C1a_C1 = x[:, 10]
	Ba_C1 = x[:, 19]
	properdin_C2 = x[:, 51]
	C2b_C1 = x[:, 22]
	C4b_C1 = x[:, 6]
	C4b2a3b_C1 = x[:, 24]
	C2b_C2 = x[:, 53]
	C5a_C1 = x[:, 28]
	C4a_C1 = x[:, 5]
	C4b2a_C1 = x[:, 23]
	volume_C1 = x[:, 63]
	C4bBb3b_C1 = x[:, 27]
	C3bBb3b_C2 = x[:, 56]
	C1a_C2 = x[:, 41]
	microbes_C1 = x[:, 15]

	 #code to plot, using subplots
	 figure(figsize(20,20))
	 PyPlot.hold(true)
	 plt[:subplot](1,3,1)
	 plot(t, C4_C1)
	 title("C4_C1")
	 plt[:subplot](1,3,2)
	 plot(t, C4a_C1)
	 title("C4a_C1")
	 plt[:subplot](1,3,3)
	 plot(t, C4b_C1)
	 title("C4b_C1")
	 end
runModel()
