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
	 tend=30
	 step=0.02
	 data_dict = DataFile(tstart, tend, step)
	 t, x = SolveBalances(tstart, tend, step, data_dict)
	 #Alias the species vector
	Plasminogen_C1 = x[:, 18]
	active_initiator_C1 = x[:, 2]
	D_dimer_C1 = x[:, 16]
	TFPI_C1 = x[:, 11]
	antiplasmin_C1 = x[:, 21]
	PLa_C1 = x[:, 7]
	APC_C1 = x[:, 9]
	volume_C1 = x[:, 25]
	ATIII_C1 = x[:, 10]
	tPA_C1 = x[:, 19]
	Plasmin_C1 = x[:, 17]
	PC_C1 = x[:, 8]
	TAFI_C1 = x[:, 22]
	PL_C1 = x[:, 6]
	fXIII_C1 = x[:, 24]
	FII_C1 = x[:, 4]
	trigger_C1 = x[:, 3]
	FIIa_C1 = x[:, 5]
	uPA_C1 = x[:, 20]
	PAI_1_C1 = x[:, 23]
	Fibrin_monomer_C1 = x[:, 13]
	Protofibril_C1 = x[:, 14]
	Fibrin_C1 = x[:, 15]
	Fibrinogen_C1 = x[:, 12]
	inactive_initiator_C1 = x[:, 1]

	 #code to plot, using subplots
	 figure(figsize=(30,10))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](1,15,1)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, inactive_initiator_C1 ,linewidth=2.0,"k")
	 title("inactive_initiator_C1" ,fontsize = 10)
	 plt[:subplot](1,15,2)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, active_initiator_C1 ,linewidth=2.0,"k")
	 title("active_initiator_C1" ,fontsize = 10)
	 plt[:subplot](1,15,3)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, trigger_C1 ,linewidth=2.0,"k")
	 title("trigger_C1" ,fontsize = 10)
	 plt[:subplot](1,15,4)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FII_C1 ,linewidth=2.0,"k")
	 title("FII_C1" ,fontsize = 10)
	 plt[:subplot](1,15,5)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, FIIa_C1 ,linewidth=2.0,"k")
	 title("FIIa_C1" ,fontsize = 10)
	 plt[:subplot](1,15,6)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PL_C1 ,linewidth=2.0,"k")
	 title("PL_C1" ,fontsize = 10)
	 plt[:subplot](1,15,7)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PLa_C1 ,linewidth=2.0,"k")
	 title("PLa_C1" ,fontsize = 10)
	 plt[:subplot](1,15,8)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, PC_C1 ,linewidth=2.0,"k")
	 title("PC_C1" ,fontsize = 10)
	 plt[:subplot](1,15,9)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, APC_C1 ,linewidth=2.0,"k")
	 title("APC_C1" ,fontsize = 10)
	 plt[:subplot](1,15,10)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, ATIII_C1 ,linewidth=2.0,"k")
	 title("ATIII_C1" ,fontsize = 10)
	 plt[:subplot](1,15,11)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, TFPI_C1 ,linewidth=2.0,"k")
	 title("TFPI_C1" ,fontsize = 10)
	 plt[:subplot](1,15,12)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrinogen_C1 ,linewidth=2.0,"k")
	 title("Fibrinogen_C1" ,fontsize = 10)
	 plt[:subplot](1,15,13)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrin_monomer_C1 ,linewidth=2.0,"k")
	 title("Fibrin_monomer_C1" ,fontsize = 10)
	 plt[:subplot](1,15,14)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Protofibril_C1 ,linewidth=2.0,"k")
	 title("Protofibril_C1" ,fontsize = 10)
	 plt[:subplot](1,15,15)
	 plt[:tick_params](axis="both", which="major", labelsize=7)
	 plt[:tick_params](axis="both", which="minor", labelsize=7)
	 plt[:ticklabel_format](axis="y", useOffset=false)
	 plot(t, Fibrin_C1 ,linewidth=2.0,"k")
	 title("Fibrin_C1" ,fontsize = 10)

	 #code to plot compartment volumes, using subplots
	 figure(figsize=(20,20))
	 PyPlot.hold(true)
	 plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](1,1,1)
	 plot(t, volume_C1)
	 title("volume_C1")
	 end
runModel()
