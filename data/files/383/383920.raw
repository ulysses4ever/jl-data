include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot;

function runModelShort()
	close("all");
	tstart = 0;
	tend = .5;
	step = .02
	data_dict = DataFile(tstart, tend, step)
	t, x = SolveBalances(tstart, tend, step, data_dict)
	# Alias the species vector - 
	C5_C1 = x[:,1];
	C4b2a3b_C1 = x[:,2];
	C4bBb3b_C1 = x[:,3];
	C5a_C1 = x[:,4];
	C5b_C1 = x[:,5];
	MAC_C1 = x[:,6];
	C6_C9_C1 = x[:,7];

	# C2
	C5_C2 = x[8];
	C4b2a3b_C2 = x[9];
	C4bBb3b_C2 = x[10];
	C5a_C2 = x[11];
	C5b_C2 = x[12];
	MAC_C2 = x[13];
	C6_C9_C2 = x[14];
	volume_C1 = x[15];
	volume_C2 = x[16];
	
	figure(figsize=(15,20))
	PyPlot.hold(true)
	plt[:subplot](441)
	plot(t, C5_C1)
	title("C5_C1")
	plt[:subplot](442)
	plot(t, C4b2a3b_C1)
	title("C4b2a3b_C1")
	plt[:subplot](443)
	plot(t, C4bBb3b_C1)
	title("C4bBb3b_C1")
	plt[:subplot](444)
	plot(t, C5a_C1)
	title("C5a_C1")
	plt[:subplot](445)
	plot(t, C5b_C1)
	title("C5b_C1")
	
	end


runModelShort()
