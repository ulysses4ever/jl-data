require("utilsForOptTweakedAllRunFromScript.jl")
#@everywhere using Optim
@everywhere using NLopt

function attemptOptimization(params0)
	#params0 = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	#params0 = [74.8046791647614,2.2100289590001516,1.210028959000152,248.37669562566663,1.210028959000152,1.210028959000152,2.3800289590001515,0.56496570694513,0.4869913126042523]
	#params0 = [75.21000543804477,2.6153552322835445,1.615355232283545,248.78202189894995,0.39313301006132306,1.615355232283545,2.1089396000684912,0.4695365249024631,0.5240186739256277]
	#params0 = [75.39244094279405,2.797790737032849,1.7977907370328494,248.96445740369927,0.5755685148106278,1.7977907370328494,2.0949738323201768,0.3531876225255054,0.4890325507680174]
	#params = ARGS
	outputdir = "moretesting/forcepositivity/usingScriptToRestartAgainParallel/"
	finalresult = string(outputdir, "finalresult.txt")
	global startTime = now()
	@show startTime
	num_useful_patients = 274.0
	res = optimize(parallel_calculateTotalMSE, params0,method = Optim.NelderMead(), show_trace = true, store_trace = true, show_every = true)
	@show res
	f = open(finalresult, "a")
	write(f, res)
	close(f)
	return res
end

function attemptOptimizationusingNLopt(params0)
	outputdir = "/outputAug29/"
	finalresult = string(outputdir, "finalresult.txt")
	global startTime = now()
	@show startTime
	opt = Opt(:LN_NELDERMEAD,11)
	#lower_bounds!(opt, vec(zeros(1,11)))#constrain all parameters to be positive
	lower_bounds!(opt, vec(fill(eps(),1,11)))#constrain all parameters to be positive and non zero
	xtol_rel!(opt,1e-2)
	min_objective!(opt, parallel_calculateTotalMSENL)
	(minf,minx,ret) = NLopt.optimize(opt, params0)
	f = open(finalresult, "a")
	write(f,"got $minf at $minx after $count iterations (returned $ret)")
	close(f)
end

#@show ARGS
println("made it here")
#params0 = Float64[]
#for j in range(1,length(ARGS))
#	push!(params0, float(ARGS[j]))
#end
#attemptOptimization(params0)
params0 = [75,1.5,.5,250, .5, .5, 1.67,.96, .7,6,1.5]
attemptOptimizationusingNLopt(params0)

