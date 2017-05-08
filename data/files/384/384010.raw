include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot;

function runModel()
	close("all");
	tstart = 0;
	tend = .3;
	step = .02
	data_dict = DataFile(tstart, tend, step)
	t, x = SolveBalances(tstart, tend, step, data_dict)
	# Alias the species vector - 
	# compartment_1
	A_compartment_1 = x[:,1];
	B_compartment_1 = x[:,2];
	E_compartment_1 = x[:,3];

	# compartment_2
	A_compartment_2 = x[:,4];
	B_compartment_2 = x[:,5];
	E_compartment_2 = x[:,6];

	# compartment_3
	A_compartment_3 = x[:,7];
	B_compartment_3 = x[:,8];
	E_compartment_3 = x[:,9];
	volume_compartment_1 = x[:,10];
	volume_compartment_2 = x[:,11];
	volume_compartment_3 = x[:,12];

	#println(size(t))
	#println(size(A_compartment_1))

	
	figure(figsize = (10,10))
	PyPlot.hold(true)
	plt[:subplot](331)
	plot(t, A_compartment_1)
	title("A_compartment_1")
	plt[:subplot](332)
	plot(t, A_compartment_2)
	title("A_compartment_2")
	plt[:subplot](333)
	plot(t, A_compartment_3)
	title("A_compartment_3")
	plt[:subplot](334)
	plot(t, B_compartment_1)
	title("B_compartment_1")
	plt[:subplot](335)
	plot(t, B_compartment_2)
	title("B_compartment_2")
	plt[:subplot](336)
	plot(t, B_compartment_3)
	title("B_compartment_3")
	plt[:subplot](337)
	plot(t, E_compartment_1)
	title("E_compartment_1")
	plt[:subplot](338)
	plot(t, E_compartment_2)
	title("E_compartment_2")
	plt[:subplot](339)
	plot(t, E_compartment_3)
	title("E_compartment_3")

	figure(figsize = (10,10))
	plt[:subplot](131)
	plot(t, volume_compartment_1)
	title("volume_compartment_1")
	plt[:subplot](132)
	plot(t, volume_compartment_2)
	title("volume_compartment_2")
	plt[:subplot](133)
	plot(t, volume_compartment_3)
	title("volume_compartment_3")


	
	
	end


runModel()
