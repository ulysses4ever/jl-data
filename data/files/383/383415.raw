include("BalanceEquations.jl")
include("CoagulationModelFactoryDecentFit.jl")
include("utilities.jl")
#using Sundials
using ODE
using PyPlot

function runModel(TSTART,Ts,TSTOP)
	#TSTART = 0.0
	#Ts = .02
	#TSTOP = 1.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	TSIM = TSTART:Ts:TSTOP
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	reshaped_IC = vec(reshape(initial_condition_vector,11,1)) #may need to cast to vector for Sundials

	#calling solver
#	fbalances(t,y,ydot)=BalanceEquations(t,y,ydot,PROBLEM_DICTIONARY)
#	X = Sundials.cvode(fbalances,reshaped_IC,TSIM, abstol =1E-4, reltol=1E-4);
	fbalances(t,y)= BalanceEquations(t,y,PROBLEM_DICTIONARY) 
	t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM; abstol = 1E-8, reltol = 1E-8,points=:specified)
#	println("got here")
	return (t,X);
end

function runModelSundials(TSTART,Ts,TSTOP)

	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	TSIM = collect(TSTART:Ts:TSTOP)
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	reshaped_IC = vec(reshape(initial_condition_vector,11,1)) #may need to cast to vector for Sundials

	#calling solver
	fbalances(t,y,ydot)=BalanceEquations(t,y,ydot,PROBLEM_DICTIONARY)
	mem = Sundials.CVodeCreate(Sundials.CV_BDF, Sundials.CV_NEWTON) 
	Sundials.@checkflag Sundials.CVodeSetMaxStep(mem, .01)
	#X = Sundials.cvode(fbalances,reshaped_IC,TSIM, integrator=:Adams,reltol=1E-8, abstol=1E-8)#, abstol =1E-4, reltol=1E-4);
	flag = Sundials.CVode(mem, TSIM,fbalances, TSIM, Sundials.CV_NORMAL)
#	println("got here")
	return (X);
end

function makePlots(t,x)
	FII = x[:,1]
	FIIA = x[:,2]
	PC = x[:,3]
	APC = x[:,4]
	ATIII = x[:,5]
	TM = x[:,6]
	TRIGGER = x[:,7]

	fig = figure(figsize = (10,10))
#	y_formatter = PyPlot.ticker.ScalarFormatter(useOffset=False)
#	ax = fig.gca()
#	println(ax)
#	ax.yaxis.set_major_formatter(y_formatter)
	plt[:subplot](2,4,1)
	plot(t, FII)
	title("FII")
	plt[:subplot](2,4,2)
	plot(t, FIIA)
	title("FIIa")
	plt[:subplot](2,4,3)
	plot(t, PC)
	title("PC")
	plt[:subplot](2,4,4)
	plot(t, APC)
	title("APC")
	plt[:subplot](2,4,5)
	plot(t, ATIII)
	title("ATIII")
	plt[:subplot](2,4,6)
	plot(t, TM)
	title("TM")
	plt[:subplot](2,4,7)
	plot(t, TRIGGER)
	title("TRIGGER")

	
end

function makeLoopPlots(t,x)
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
		plot(t, [a[j] for a in x], "k")
		title(names[j])
	end
	#savefig("figures/Dec19_BeforeOpt.pdf")
end

function makePlotsfromODE4s(t,x)
	FII = Float64[]
	FIIA = Float64[]
	PC = Float64[]
	APC = Float64[]
	ATIII = Float64[]
	TM = Float64[]
	TRIGGER= Float64[]
	frac_acviated = Float64[]
	for j = 1:length(x)
		currx = x[j]
		for k = 1:length(currx)
			curritem = currx[k]
			if(k == 1)
				push!(FII, curritem)
			elseif(k == 2)
				push!(FIIA,curritem)
			elseif(k == 3)
				push!(PC, curritem)
			elseif(k == 4)
				push!(APC, curritem)
			elseif(k == 5)
				push!(ATIII, curritem)
			elseif(k == 6)
				push!(TM, curritem)
			elseif(k ==7)
				push!(TRIGGER,curritem)
			elseif(k ==8)
				push!(frac_acviated, curritem)
			end
		end
	end
	fig = figure(figsize = (10,10))
	plt[:subplot](2,4,1)
	plot(t, FII)
	title("FII")
	plt[:subplot](2,4,2)
	plot(t, FIIA)
	title("FIIa")
	plt[:subplot](2,4,3)
	plot(t, PC)
	title("PC")
	plt[:subplot](2,4,4)
	plot(t, APC)
	title("APC")
	plt[:subplot](2,4,5)
	plot(t, ATIII)
	title("ATIII")
	plt[:subplot](2,4,6)
	plot(t, TM)
	title("TM")
	plt[:subplot](2,4,7)
	plot(t, TRIGGER)
	title("TRIGGER")
	plt[:subplot](2,4,8)
	plot(t, frac_acviated)
	title("Fraction of Platelets Activated")

end

function plotFluxes(pathToData,t)
	data = readdlm(pathToData)
	fig = figure(figsize = (15,15))
	for j in collect(1:size(data,2))
		plt[:subplot](size(data,2),1,j)
		@show size(t)
		@show size(data[:,j])
		plot(t, data[:,j], ".k")
		title(string("reaction ", j))
	end
end


function main()
	pathToData = "../data/ButenasFig1B60nMFVIIa.csv"
	close("all")
	#rm("ratevector.txt")
	#rm("modifiedratevector.txt")
	#rm("times.txt")
	(t,x) = runModel(0.0, .01, 20.0)
	@show size(t)
	#remove tiny elements that are causing plotting problems
	#x[x.<=1E-20] = 0.0
	#times = readdlm("times.txt")
	#plotFluxes("ratevector.txt",times)
	#plotFluxes("modifiedratevector.txt",times)

	#println(x)
	makeLoopPlots(t,x)
	plotThrombinWData(t,x,pathToData)
	MSE, interpolatedExperimentalData=calculateMSE(t, [a[2] for a in x], readdlm(pathToData, ','))
	estimatedAUC = calculateAUC(t, [a[2] for a in x])
	experimentalAUC = calculateAUC(t, interpolatedExperimentalData)
	@show estimatedAUC, experimentalAUC
	return MSE, abs(estimatedAUC-experimentalAUC)
end


function plotThrombinWData(t,x,pathToData)
	#close("all")
	expdata = readdlm(pathToData,',')
	#fig = figure(figsize = (15,15))
	plot(t, [a[2] for a in x], "k-")
	plot(expdata[:,1], expdata[:,2], ".k")
	ylabel("Thrombin Concentration, nM")
	xlabel("Time, in minutes")
	#savefig("figures/UsingNMParameters.pdf")
end

function plotAverageThrobinWData(t,meanThrombin,stdThrombin,pathToData,MSE, savestr)
	expdata = readdlm(pathToData,',')
	fig = figure(figsize = (15,15))
	plot(expdata[:,1], expdata[:,2], ".k")
	ylabel("Thrombin Concentration, nM")
	xlabel("Time, in minutes")
	plot(t, transpose(meanThrombin), "k")
	@show size(meanThrombin)
	@show size(stdThrombin)
	@show size(t)
	upper = transpose(meanThrombin+stdThrombin)
	lower = transpose(meanThrombin-stdThrombin)
	@show size(vec(upper))
	@show size(vec(lower))
	fill_between((t), vec(upper), vec(lower), color = ".5")
	annotate(string("MSE=", MSE),
	xy=[.85;.85],
	xycoords="figure fraction",
	xytext=[0,0],
	textcoords="offset points",
	ha="right",
	va="top")
	savefig(savestr)
end


function runModelWithMultipleParams(pathToParams,pathToData,savestr)
	close("all")
	allparams = readdlm(pathToParams, ',')
	TSTART = 0.0
	Ts = .02
	TSTOP = 60.0
	TSIM = collect(TSTART:Ts:TSTOP)
	#pathToData = "../data/ButenasFig1B60nMFVIIa.csv"
	#pathToData = "../data/Luan2010Fig5F.csv"
	fig = figure(figsize = (15,15))
	alldata = zeros(1,size(TSIM,1))
	
	for j in collect(1:size(allparams,1))
		currparams = allparams[j,:]
		dict = buildDictFromOneVector(currparams)
		initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
		reshaped_IC = vec(reshape(initial_condition_vector,11,1))
		fbalances(t,y)= BalanceEquations(t,y,dict) 
		t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-4, reltol = 1E-4,points=:specified)
		#plotThrombinWData(t,X,pathToData)
		#@show alldata
		#@show size([a[2] for a in X])
		alldata=vcat(alldata,transpose([a[2] for a in X]))
	end
	alldata = alldata[2:end, :] #remove row of zeros
	alldata = map(Float64,alldata)
	meanThrombin = mean(alldata,1)
	stdThrombin = std(alldata,1)
	plotAverageThrobinWData(TSIM, meanThrombin, stdThrombin, pathToData,savestr)
	return alldata
end

function runModelWithMultipleParams(pathToParams,pathToData,index,savestr)
	close("all")
	allparams = readdlm(pathToParams, ',')
	TSTART = 0.0
	Ts = .02
	TSTOP = 60.0
	TSIM = collect(TSTART:Ts:TSTOP)
	#pathToData = "../data/ButenasFig1B60nMFVIIa.csv"
	#pathToData = "../data/Luan2010Fig5F.csv"
	fig = figure(figsize = (15,15))
	alldata = zeros(1,size(TSIM,1))
	
	for j in collect(1:size(allparams,1))
		currparams = allparams[j,:]
		dict = buildDictFromOneVector(currparams)
		dict = createCorrectDict(dict, index)
		initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
		fbalances(t,y)= BalanceEquations(t,y,dict) 
		t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-4, reltol = 1E-4,points=:specified)
		#plotThrombinWData(t,X,pathToData)
		#@show alldata
		#@show size([a[2] for a in X])
		alldata=vcat(alldata,transpose([a[2] for a in X]))
	end
	alldata = alldata[2:end, :] #remove row of zeros
	alldata = map(Float64,alldata)
	meanThrombin = mean(alldata,1)
	stdThrombin = std(alldata,1)
	MSE, interpolatedExperimentalData=calculateMSE(TSIM, transpose(meanThrombin), readdlm(pathToData, ','))
	@show MSE
	plotAverageThrobinWData(TSIM, meanThrombin, stdThrombin, pathToData, MSE,savestr)
	return alldata
end

function runModelWithParams(params)
	close("all")
	TSTART = 0.0
	Ts = .02
	TSTOP = 20.0
	TSIM = collect(TSTART:Ts:TSTOP)
	pathToData = "../data/ButenasFig1B60nMFVIIa.csv"
	#pathToData = "../data/Buentas1999Fig4100PercentProthrombin.txt"
	#pathToData = "../data/Laun2010Fig5A.csv"
	fig = figure(figsize = (15,15))
	
	dict = buildDictFromOneVector(params)
	initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
	fbalances(t,y)= BalanceEquations(t,y,dict) 
	t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-8, reltol = 1E-8)
	plotThrombinWData(t,X,pathToData)
	makeLoopPlots(t,X)
	MSE, interpolatedExperimentalData=calculateMSE(t, [a[2] for a in X], readdlm(pathToData, ','))
	return MSE
end



