include("SolveBalances.jl")
include("DataFile.jl")
using PyPlot;

function runModel()
	close("all");
	tstart = 0;
	tend = .5;
	step = .02
	data_dict = DataFile(tstart, tend, step)
	t, x = SolveBalances(tstart, tend, step, data_dict)
	# Alias the species vector - 
	C1q_C1 = x[:,1];
	MBL_C1 = x[:,2];
	C3_C3H2O_C1 = x[:,3];
	C3_C1 = x[:,4];
	C3_convertase_C1 = x[:,5];
	C3a_C1 = x[:,6];
	C3b_C1 = x[:,7];
	C5_C1 = x[:,8];
	C5a_C1 = x[:,9];
	C5b_C1 = x[:,10];
	platelet_C1 = x[:,11];
	activated_platelet_C1 = x[:,12];
	B_C1 = x[:,13];

	# C2
	C1q_C2 = x[:,14];
	MBL_C2 = x[:,15];
	C3_C3H2O_C2 = x[:,16];
	C3_C2 = x[:,17];
	C3_convertase_C2 = x[:,18];
	C3a_C2 = x[:,19];
	C3b_C2 = x[:,20];
	C5_C2 = x[:,21];
	C5a_C2 = x[:,22];
	C5b_C2 = x[:,23];
	platelet_C2 = x[:,24];
	activated_platelet_C2 = x[:,25];
	B_C2 = x[:,26];
	volume_C1 = x[:,27];
	volume_C2 = x[:,28];
	
	figure(figsize=(15,20))
	PyPlot.hold(true)
	plt[:subplot](441)
	plot(t, C1q_C1)
	title("C1q_C1")
	plt[:subplot](442)
	plot(t, MBL_C1)
	title("MBL_C1")
	plt[:subplot](443)
	plot(t, C3_C3H2O_C1)
	title("C3_C3H2O_C1")
	plt[:subplot](444)
	plot(t, C3_C1)
	title("C3_C1")
	plt[:subplot](445)
	plot(t, C3_convertase_C1)
	title("C3_convertase_C1")
	plt[:subplot](446)
	plot(t, C3a_C1)
	title("C3a_C1")
	plt[:subplot](447)
	plot(t, C3b_C1)
	title("C3b_C1")
	plt[:subplot](448)
	plot(t, platelet_C1)
	title("platelet_C1")
	plt[:subplot](449)
	plot(t, activated_platelet_C1)
	title("activated_platelet_C1")
	plt[:subplot](4,4,10)
	plot(t, platelet_C2)
	title("platelet_C2 ")
	


	
	end


runModel()
