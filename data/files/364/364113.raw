function setOptions ()

	#------Options for the iterative search loop-------

	#  Optional user defined bounds for the initial parameter search (Px2) array

	#SS::Array{Float64} = [1e-4 1e-4 1e-4 1e-4 1e-4 0.1 1e-4 1e-4;1e4 1e4 1e4 1e4 1e4 3.0 1e4 1e4]

					#---Options---
					#
	IS::Int64 = 20			#	Number of local optimisations to run i.e. Latin hypercube size
	SR::Int64 = 20			#	Number of reductions in search space
	SS::Int64 = 10			#	Initial search space or user specified array (replace float with array name)
					#
	TS::Float64 = 1.		#	Initial trust region size
	TA::Float64 = 1e-2		#	Termination tolerance for cost function as fraction
	TT::Float64 = 1e-5		#	Termination tolerance for trust region size
	MI::Int64 = 400		#	Maximum iterations before termination of local optimisation
					#
	ST::Float64 = 1e-6		#	Relative step tolerence
	MN::Float64 = 1e-10		#	Minimum step size
	MX::Float64 = 1.		#	Maximum stepsize

	#  Absolute step tolerance for each variable: consider adjusting for poorly scaled experimental data

	AT::Vector{Float64} = [1e-6, 1e-6, 1e-6, 1e-6, 1e-6,1e-6];

	opt = Options(IS,SR,SS,TS,TA,TT,MI,MN,MX,ST,AT)

	return(opt)

end

function setSolverData ()

	#------Data and options for the cost function------

	#  Experimental data and sample times for the data

	smpt::Vector{Float64} = linspace(0,20,30)
	xdat::Matrix{Float64} = readdlm("repdata.txt",' ')

	#  Observed variables, indexes ODE values to experimental data: same length as columns in expdat

	obsv::Vector{Int64} = [1,2,3,4,5,6]

	#  Initial conditions for the ODE. If these are to be calculated as parameters specify which with integer values

	init::Vector{Float64} = [0.1,0.1,0.1,0.1,0.1,90.]

	#  Prepare data

	maxt::Int64 = length(smpt)
	xdat = transpose(xdat)
	edat = ErrorData(obsv,smpt,maxt,xdat,init)

	return(edat)
end

function setGraphingData ()

	#------Data and options for the cost function------

	#  Experimental data and sample times for the data

	smpt::Vector{Float64} = linspace(0,20,30)
	xdat::Matrix{Float64} = readdlm("repdata.txt",' ')

	#  Observed variables, indexes ODE values to experimental data: same length as columns in expdat

	obsv::Vector{Int64} = [1, 2, 3, 4, 5, 6]

	#  Initial conditions for the ODE. If these are to be calculated as parameters specify which with integer values

	init::Vector{Float64} = [0.1,0.1,0.1,0.1,0.1,90.]

	# Solver options
	
	stp = 1e-6
	abstol = [1e-6, 1e-6, 1e-6, 1e-6, 1e-6,1e-6, 1e-6,1e-6, 1e-6];	
	min = 1e-6
	max = 0.1

	#  Prepare data

	maxt::Int64 = length(smpt)
	xdat = transpose(xdat)
	pdat = PlotData(obsv,smpt,maxt,xdat,init,stp,abstol,min,max)

	return(pdat)
end

