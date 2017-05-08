include("BalanceEquations.jl")
include("CoagulationModelFactoryDecentFit.jl")
include("utilities.jl")
using DifferentialEquations
using ParameterizedFunctions
using PyPlot
using ODEInterfaceDiffEq
using ODE
using RecursiveArrayTools

function solveModelUsingDE()
	TSTART = 0.0
	TSTOP = 20.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	@show initial_condition_vector
	problem_vec = dict_to_vec(PROBLEM_DICTIONARY)
	pf = ParameterizedFunction(BalanceEquationsDE_f, problem_vec)
	prob = ODEProblem(pf,initial_condition_vector,(TSTART, TSTOP))
	@show prob
	sol = solve(prob,Rosenbrock23(),abstol = 1E-4, reltol = 1E-8)#, dtmax=.001,abstol = 1E-4, reltol = 1E-8)#alg_hints=[:stiff])#, abstol = 1E-4, reltol = 1E-8)
	makeLoopPlots(sol)
	return prob

end

function ModelSensitivity()
	TSTART = 0.0
	TSTOP = 20.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	problem_vec = dict_to_vec(PROBLEM_DICTIONARY)
	prob_expr_vec = Expr[]
	for j in collect(1:size(problem_vec,1))
		push!(prob_expr_vec,parse("p_$(j) => $(problem_vec[j])"))
	end
	
	opts = Dict{Symbol,Bool}(
	      :build_tgrad => true,
	      :build_jac => true,
	      :build_expjac => false,
	      :build_invjac => true,
	      :build_invW => true,
	      :build_invW_t => true,
	      :build_hes => true,
	      :build_invhes => true,
	      :build_dpfuncs => true)
	pf = ParameterizedFunction(BalanceEquationsDE_f, problem_vec)
	pf_def = ode_def_opts(:pf, opts, Meta.quot(pf), prob_expr_vec...)
	@show pf
	@show pf.p
	prob = ODELocalSensitivityProblem(pf,initial_condition_vector,(TSTART, TSTOP))
	#prob = ODEProblem(pf,initial_condition_vector,(TSTART, TSTOP))
	@show prob
	sol = solve(prob,Rosenbrock23(), dtmax = .01)#,abstol = 1E-4, reltol = 1E-8)#, dtmax=.001,abstol = 1E-4, reltol = 1E-8)#alg_hints=[:stiff])#, abstol = 1E-4, reltol = 1E-8)
	#@show sol[:,1]
	x=vecvec_to_mat([sol[i][1:sol.prob.indvars] for i in 1:length(sol)])
	makeLoopPlots(sol)
	return sol

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
		#@show sol.t
		plot(sol.t, sol[:,j], "k")
		title(names[j])
	end
	savefig("figures/Jan_27_Itworks.pdf")
end

