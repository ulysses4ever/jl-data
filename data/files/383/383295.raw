include("BalanceEquations.jl")
include("CoagulationModelFactory.jl")
include("utilities.jl")
include("runModel.jl")
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
	@show dict["FACTOR_LEVEL_VECTOR"][3], dict["FVIII_CONTROL"]
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
	opt = Opt(:LN_COBYLA, numvars)
	lower_bounds!(opt, vec(fill(1E-4,1,numvars)))
	upper_bounds!(opt, vec(fill(1E3,1,numvars)))
	min_objective!(opt, objectiveForNLOpt)
	dict = createCorrectDict(dict, exp_index)
	(minf, minx, ret) = NLopt.optimize(opt, vec([500]))
	println("got $minf at $minx after $count iterations (returned $ret)")
	return minf, minx, ret
	
	
end

function runOpt(exp_index)
	global experimentaldata = allexperimentaldata[exp_index]
	global savestr = string("parameterEstimation/fitF8/NM17032017EstFVIIIparamDataSet",exp_index, ".txt")
	params = readdlm("parameterEstimation/bestAfterNMround302_15_2017.txt", ',')
	global dict =buildDictFromOneVector(params)
	dict = createCorrectDict(dict, exp_index)
	@show dict["FACTOR_LEVEL_VECTOR"][3]
	#if I want to fiddle with IC to make better fit
	initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
	initial_condition_vector = setIC(initial_condition_vector, exp_index)
	dict["INITIAL_CONDITION_VECTOR"]=initial_condition_vector
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
	f8 = [1.07,.39,.07,.01, 0.0]
	f8control = results[:,2]
	figure()
	semilogy(f8, f8control, "k.")
	xlabel("FVIII Level")
	ylabel("FVIII Control")
	savefig("figures/FVIIIControl.pdf")	
	return results
end

function makeFigures()
	params = readdlm("parameterEstimation/AfterCalculatingF8FunctionPostNM.txt", ',')
	indices = [2,3,4,5,6,1]
	f8 = [1.07,.39,.07,.01, 0.0, 1.0]
	j = 1
	for ind in indices
		MSE=runModelWithParamsSetF8(params, calculateF8control(f8[j]), ind)
		@show MSE
		j = j+1
	end
end

function makeOneFigure()
	close("all")
	params = readdlm("parameterEstimation/bestAfterNMround302_15_2017.txt", ',')
	indices = [2,3,4,5,6,1]
	f8 = [1.07,.39,.07,.01, 0.0, 1.0]
	j = 1
	fig = figure(figsize = (15,15))
	hold(true)
	for ind in indices
		fig=runModelWithParamsSetF8OnePlot(fig, params, calculateF8control(f8[j]), ind)
		#@show MSE
		j = j+1
	end
	#legend(["FVIII=107%", "FVIII=100%", "FVIII=39%", "FVIII=7%", "FVIII=1%", "FVIII=0%"])
	axis([0, 60, 0, 400])
	savefig("figures/MasterFigure_15_03_2017.pdf")
end

#old
#function calculateF8control(f8)
#	control = 4.6863*f8^2+.5357*f8-.01319
#	return abs(control)
#end

#new
function calculateF8control(f8)
	control = -1.30954*f8^2+2.5819*f8-.0032
	return abs(control)
	
end
