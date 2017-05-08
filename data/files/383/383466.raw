using DataFrames
#using Optim
using NLopt
include("OOModelWithTimeLookUp.jl")

function processNumericalData(filename)
	n=DataFrames.names(readtable(filename, separator=',',nastrings=["-"], nrows = 1, header=true))
	df=readtable(filename, separator=',',nastrings=["-"], skipstart =2, header = false)
	names!(df, n)
	return df
end

function cleandata(data)
	#remove any rows with NAs in the places I care about
	data[~isna(data[:,symbol("_ABP_Mean_")]),:]	
	deleterows!(data,find(isna(data[:,symbol("_ABP_Mean_")])))
	data[~isna(data[:,symbol("_HR_")]),:]	
	deleterows!(data,find(isna(data[:,symbol("_HR_")])))

	if(length(data[:_Elapsed_time_])>2)
		timediff = data[:_Elapsed_time_][2]-data[:_Elapsed_time_][1]
		#@show(timediff)
		if (timediff > 10) #if there's a big gap between first and second measurement, throw out first one, start analysis at second point
			deleterows!(data,1)
			println("found large gap and removed it")
		end
	end

	return data
end

function calculatetotalMSE(params::Vector, grad::Vector)
#function calculatetotalMSE(params)
	tic()
	outputdir = "moretesting/2016_12_22/"
	inputdir = "/home/rachel/Documents/work/optimization/LinkedRecordsTimeData10min/"
	c1patients = readdlm("/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster1subjectIDs")
	c2patients = readdlm("/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster1subjectIDs")
	allpatients = [c1patients, c2patients]
	touch(string(outputdir, "usefuldatatol1E-4.txt"))
	touch(string(outputdir, "paramstol1E-4.txt"))
	totalMSE = 0.0
	usefulpatients = 0.0

	@show params
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		#println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewerstepsAndOptimizedParams", ".png")
		data= processNumericalData(string(inputdir, patient))
		sort!(data, cols = [order(:_Elapsed_time_)])
		colnames = (names(data))
		if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			#println("has complete data")
			data = cleandata(data)
			MSE= calculateHeartRate(data, params,savestr)
			@show MSE
			if(contains(string(typeof(MSE)), "Void"))
				continue
			end
			totalMSE = MSE + totalMSE
			usefulpatients = usefulpatients +1

			f = open(string(outputdir,"usefuldatatol1E-4only2steps.txt"), "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	MSE = totalMSE/usefulpatients
	g = open(string(outputdir, "paramstol1E-4only2steps.txt"), "a")
	write(g, string(params, ",", MSE, "\n"))
	close(g)
	return MSE
end

function constraint(x::Vector)
	for j in collect(1:length(x))
		if(x[j]<.1)
			x[j] = .1
		end
	end
end

function attemptOptimizationOptim()
	params0 = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	#params0=[78.97582761404169,-1.8864140993276886,0.00142967813114446,251.60453882677203,2.648725296877113,-2.0547879774326403,0.9505848336074358,1.506601105672376,-0.43857878055469035]
	res = optimize(calculatetotalMSE, params0,method = Optim.NelderMead(), show_trace = true, x_tol=1E-4, f_tol = 1E-4)
	@show res
	return res
end

function attemptOptimizationNLOpt()
	numvars = 9
	opt = Opt(:LN_NELDERMEAD,numvars)
	lb =fill(1E-4, 1, numvars)
	lb[numvars] = .1
	lb[(numvars-1)] =.1
	@show lb
	lower_bounds!(opt, vec(lb))
	#upper_bounds!(opt, vec[])
	min_objective!(opt, calculatetotalMSE)
	params0 = [75 1.5 .5 250 .5 .5 1.67 .96 .7]
	(minf, minx, ret) = NLopt.optimize(opt, vec(params0))

end


