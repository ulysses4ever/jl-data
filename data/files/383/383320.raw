include("BalanceEquations.jl")
include("CoagulationModelFactory.jl")
include("utilities.jl")
#using Sundials
using ODE
using NLopt

# some global parameters -
BIG = 1e10
SMALL = 1e-9

#globally load data so that we don't have to reload on each iteration
pathsToData = ["../data/Luan2010Fig5A.csv", "../data/Luan2010Fig5B.csv","../data/Luan2010Fig5C.csv", "../data/Luan2010Fig5D.csv", "../data/Luan2010Fig5E.csv","../data/Luan2010Fig5F.csv"]
allexperimentaldata = Array[]
for j in collect(1:size(pathsToData,1))
	currdata = readdlm(pathsToData[j], ',')
	push!(allexperimentaldata, currdata)
end


function objectiveForNLOpt(params::Vector, grad::Vector)
	#tic()
	TSTART = 0.0
	Ts = .02
	TSTOP = 60.0
	TSIM = collect(TSTART:Ts:TSTOP)
	initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
	dict["FVIII_CONTROL"] =params[1]
	@show params
	fbalances(t,y)= BalanceEquations(t,y,dict)
	#println("got here") 
	t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-6, reltol = 1E-6)
	FIIa = [a[2] for a in X]
	MSE, interpolatedExperimentalData=calculateMSE(t, FIIa, experimentaldata)
	#hold("on")
	#plot(t, FIIa, alpha = .5)
	#write params to file
	f = open(savestr, "a+")
	write(f, string(params, ",", MSE, "\n"))
	close(f)
	#toc()
	@show MSE
	return MSE
end

function attemptOptimizationNLOptF8(exp_index,dict)
	numvars = 1
	opt = Opt(:LN_NELDERMEAD, numvars)
	lower_bounds!(opt, vec(fill(1E-3,1,numvars)))
	upper_bounds!(opt, vec(fill(1E2,1,numvars)))
	min_objective!(opt, objectiveForNLOpt)
	dict = createCorrectDict(dict, exp_index)
	(minf, minx, ret) = NLopt.optimize(opt, vec([.5]))
	println("got $minf at $minx after $count iterations (returned $ret)")
	return minf, minx, ret
	
	
end

function runOpt(exp_index)
	global experimentaldata = allexperimentaldata[exp_index]
	global savestr = string("parameterEstimation/fitF8/NM10022017EstFVIIIparamDataSet",exp_index, ".txt")
	params = readdlm("parameterEstimation/bestparamsafter2rounds.txt", ',')
	global dict =buildDictFromOneVector(params)
	dict = createCorrectDict(dict, exp_index)
	minf, minx, ret=attemptOptimizationNLOptF8(exp_index, dict)
	return minf, minx, ret
end

function runAllOpt()
	results = Array{Float64}(5,2)
	for j in collect(2:6)
		minf, minx, ret=runOpt(j)
		results[j-1,1] = minf
		results[j-1,2] = minx[1]
	end	
	return results
end
