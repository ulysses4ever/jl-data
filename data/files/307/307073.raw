module bioOptimize

	using Sundials
	using PyPlot

	export	optimizeODE,
		plotODE,
		setOptions,
		setSolverData,
		setGraphingData	

	#structures for this module		
	include("structures.jl")

	#Initialise options and data
	include("Setup.jl")

	#Main caller
	include("Optimisation_main.jl")

	#Latin hyper cube sample
	include("lhc_func.jl")

	#Calculate Hessian and Jacobian
	include("Hes_Jac.jl")

	#Cost function caluclation
	include("Error_function.jl")

	#Local optimization
	include("Parameter_search.jl")

	#ODE to be optimised
	include("ODE.jl")
end 
