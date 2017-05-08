include("BalanceEquations.jl")
include("CoagulationModelFactory.jl")
#using Sundials
using ODE
using PyPlot

function runAdisModel(TSTART,Ts,TSTOP)
	#TSTART = 0.0
	#Ts = .02
	#TSTOP = 1.0
	PROBLEM_DICTIONARY = Dict()
	PROBLEM_DICTIONARY = buildCoagulationModelDictionary()
	TSIM = [TSTART:Ts:TSTOP]
	initial_condition_vector = PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"]
	reshaped_IC = vec(reshape(initial_condition_vector,1,7)) #may need to cast to vector for Sundials
	@show(initial_condition_vector)
	@show(typeof(initial_condition_vector))
	@show(size(initial_condition_vector))
	@show(size(reshaped_IC))
	@show(reshaped_IC)

	#calling solver
	#fbalances(t,y,ydot)=BalanceEquations(t,y,ydot,PROBLEM_DICTIONARY)
	#X = Sundials.cvode(fbalances,reshaped_IC,TSIM);
	fbalances(t,y)= BalanceEquations(t,y,PROBLEM_DICTIONARY) 
	t,x = ode4s(fbalances, reshaped_IC,TSIM)
	#println("got here")
	return (TSIM,x);
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
	y_formatter = PyPlot.ticker.ScalarFormatter(useOffset=False)
	ax = fig.gca()
	println(ax)
	ax.yaxis.set_major_formatter(y_formatter)
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

function makePlotsfromODE4s(t,x)
	FII = Float64[]
	FIIA = Float64[]
	PC = Float64[]
	APC = Float64[]
	ATIII = Float64[]
	TM = Float64[]
	TRIGGER= Float64[]
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

end
function main()
	close("all")
	(t,x) = runAdisModel(0.0, .02, 10)
	#remove tiny elements that are causing plotting problems
	#x[x.<=1E-20] = 0.0


	#println(x)
	makePlotsfromODE4s(t,x)
end

main()
