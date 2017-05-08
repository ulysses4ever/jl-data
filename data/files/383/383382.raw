include("BalanceEquations.jl")
include("CoagulationModelFactoryDecentFit.jl")
include("utilities.jl")
using DifferentialEquations
using ParameterizedFunctions
using PyPlot

function solveModelUsingDE()
	TSTART = 0.0
	TSTOP = 20.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	@show initial_condition_vector
	problem_vec = dict_to_vec(PROBLEM_DICTIONARY)
#	@show PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"]
#	@show problem_vec[1:6]
#	@show PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"]
#	@show problem_vec[7:26]
#	@show PROBLEM_DICTIONARY["PLATELET_PARAMS"]
#	@show problem_vec[27:32]
#	@show PROBLEM_DICTIONARY["TIME_DELAY"]
#	@show problem_vec[33:34]
#	@show PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"]
#	@show problem_vec[35:52]
	pf = ParameterizedFunction(BalanceEquationsDE,problem_vec)
	#prob = ODELocalSensitivityProblem(pf, initial_condition_vector, (TSTART, TSTOP))
	prob = ODEProblem(pf,initial_condition_vector,(TSTART, TSTOP))
	sol = solve(prob,DP8(),abstol = 1E-4, reltol = 1E-8, maxiters=1E7, dt=.0001)#alg_hints=[:stiff])#, abstol = 1E-4, reltol = 1E-8)
	#@show sol[:,1]
	makeLoopPlots(sol)

end

function makeLoopPlots(sol)
	close("all")
	names = ["FII", "FIIa", "PC", "APC", "ATIII", "TM", "TRIGGER", "Fraction Activated Platelets", "FV_FX", "FV_FXa", "Prothombinase-Platelets"]
	fig = figure(figsize = (15,15))
#	y_formatter = PyPlot.ticker.ScalarFormatter(useOffset=false)
#	ax = fig.gca()
#	println(ax)
#	ax.yaxis.set_major_formatter(y_formatter)
	#@show size(t)
	for j in collect(1:size(names,1))
		plt[:subplot](4,3,j)
		#@show size([a[j] for a in x])
#		@show typeof(sol[:,j])
#		@show typeof(sol.t)
#		@show j
		plot(sol.t, sol[:,j], "k")
		title(names[j])
	end
	savefig("figures/Jan_24_UsingDE.pdf")
end
