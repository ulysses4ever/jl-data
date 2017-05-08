include("BalanceEquations.jl")
include("CoagulationModelFactoryDecentFit.jl")
include("utilities.jl")
using DifferentialEquations
using ParameterizedFunctions

function solveModelUsingDE()
	TSTART = 0.0
	TSTOP = 20.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	problem_vec = dict_to_vec(PROBLEM_DICTIONARY)
	@show problem_vec
	pf = ParameterizedFunction(BalanceEquationsDE,problem_vec)
	prob = ODELocalSensitivityProblem(pf, initial_condition_vector, (TSTART, TSTOP))
	sol = solve(prob, DP8())

end


