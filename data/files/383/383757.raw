using DataFrames
using Optim
include("OlufsenModel2011calcHRtweaked.jl")

function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable("tempoutputTA.csv", df)
	dfnew = readtable("tempoutputTA.csv", separator=',')
	return dfnew, units
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

function calculatetotalMSE(params)
	tic()
	outputdir = "moretesting/forcepositivity/withPertabationToInitals/1/"
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	allpatients = readdir(inputdir)
	touch(string(outputdir, "usefuldatatolAll1E-4only2steps.txt"))
	touch(string(outputdir, "paramstolAll1E-4only2steps.txt"))
	totalMSE = 0.0
	usefulpatients = 0.0

	#force positivity on all parameters
	lowerbound = 1E-9
	for j in range(1,length(params))
		if(params[j])<0
			params[j] = lowerbound
		end
	end

	@show params
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		#println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
		data, units= processNumericalData(string(inputdir, patient))
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

			f = open(string(outputdir,"usefuldatatolAll1E-4only2steps.txt"), "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	overallMSE = totalMSE/usefulpatients
	g = open(string(outputdir, "paramstolAll1E-4only2steps.txt"), "a")
	write(g, string(params, ",", overallMSE, "\n"))
	close(g)
	return overallMSE
end

function attemptOptimization()
	paramsinit = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	#params0 = [74.8046791647614,2.2100289590001516,1.210028959000152,248.37669562566663,1.210028959000152,1.210028959000152,2.3800289590001515,0.56496570694513,0.4869913126042523]
	#params0 = [75.21000543804477,2.6153552322835445,1.615355232283545,248.78202189894995,0.39313301006132306,1.615355232283545,2.1089396000684912,0.4695365249024631,0.5240186739256277]
	#params0 = [75.39244094279405,2.797790737032849,1.7977907370328494,248.96445740369927,0.5755685148106278,1.7977907370328494,2.0949738323201768,0.3531876225255054,0.4890325507680174]
	params0 = Float64[]
	for j in range(1,length(paramsinit))
		push!(params0, paramsinit+(.5-rand()))
	end

	res = optimize(calculatetotalMSE, params0,method = Optim.NelderMead(), show_trace = true, ftol = 1E-3)
	@show res
	return res
end
#attemptOptimization()


