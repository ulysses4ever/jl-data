@everywhere using DataFrames
@everywhere using Debug

require("/home/rachel/Documents/optimization/SingleObjective/OlufsenModel2011calcHRtweaked.jl")

@everywhere function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable(string("tempoutputParallel", myid(),".csv"), df)
	dfnew = readtable(string("tempoutputParallel", myid(),".csv"), separator=',')
	return dfnew, units
end

@everywhere function cleandata(data)
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

function calculateTotalMSE(cluster,clusterCounter,params)
	tic()
	outputdir = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputJun16testing/"
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	allpatients = cluster
	datasavestr = string(outputdir,"cluster",clusterCounter, "usefuldatatol1E-8.txt")
	paramssavestr= string(outputdir,"cluster",clusterCounter, "paramstolAll1E-8.txt")
	touch(datasavestr)
	touch(paramssavestr)

	#force positivity on all parameters
	lowerbound = 1E-9
	for j in range(1,length(params))
		if(params[j])<0
			params[j] = lowerbound
		end
	end

	@show params
	totalMSE = 0.0
	usefulpatients = 0.0
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		#println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
		data, units= processNumericalData(string(inputdir, patient))
		sort!(data, cols = [order(:_Elapsed_time_)])
		colnames = (names(data))
		if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			println("has complete data")
			data = cleandata(data)
			MSE= calculateHeartRate(data, params,savestr)
			@show MSE
			if(contains(string(typeof(MSE)), "Void"))
				continue
			end
			totalMSE = MSE + totalMSE
			usefulpatients = usefulpatients +1

			f = open(datasavestr, "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	overallMSE = totalMSE/usefulpatients
	g = open(paramssavestr, "a")
	write(g, string(params, ",", overallMSE, "\n"))
	close(g)

	return overallMSE
end

@Debug.debug function multidimensionalMSE(params)
	multidimensionalMSE = ones(2,1)
	cluster1path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	multiDstorage = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputMay31/mutliDparams.txt"
	cluster1IDs = AbstractString[]
	cluster2IDs = AbstractString[]

	f = open(cluster1path)

	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster1IDs, strip(ln))
		end
	end
	close(f)
	g = open(cluster2path)
	for ln in eachline(g)
		if(length(ln)>1)
			push!(cluster2IDs, strip(ln))
		end
	end

	allIDs = Array[]
	push!(allIDs, cluster1IDs)
	push!(allIDs, cluster2IDs)
	clusterCounter = 1
	for cluster in allIDs
		totalMSE = calculateTotalMSE(cluster,clusterCounter, params)
		multidimensionalMSE[clusterCounter,1] = totalMSE
		clusterCounter=clusterCounter+1
	end
	f = open(multiDstorage, "a")
	write(f, string(params, ",", multidimensionalMSE[1,1], ",", multidimensionalMSE[2,1],"\n"))
	close(f)
	@show multidimensionalMSE
	return multidimensionalMSE
end

function parallel_calculateTotalMSE(cluster,clusterCounter,params)
	tic()
	outputdir = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputJun16parallel/"
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	allpatients = cluster
	datasavestr = string(outputdir,"cluster",clusterCounter, "usefuldatatol1E-8.txt")
	paramssavestr= string(outputdir,"cluster",clusterCounter, "paramstolAll1E-8.txt")
	touch(datasavestr)
	touch(paramssavestr)

	#force positivity on all parameters
	lowerbound = 1E-9
	for j in range(1,length(params))
		if(params[j])<0
			params[j] = lowerbound
		end
	end

#	@show params
	#usefulpatients = 0.0
	addPatient = 0
	#println("got here")
	calcMSE = 0.0
	totalMSE = @parallel (+) for patient in allpatients
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
			#@show MSE
			if(contains(string(typeof(MSE)), "Void"))
				addPatient = 0
				 0.0
			else
				addPatient = 1
				f = open(datasavestr, "a")
				f = write(f, string(patient, ",", MSE, "\n"))
				close(f)
				 MSE
			end
			#totalMSE = MSE + totalMSE
			#usefulpatients = usefulpatients +addPatient
			#println(usefulpatients)
		else
			0.0	
		end
		
	end
	toc()
	totalMSE
end



function multidimensionalMSE_usingparallel(params)
	multidimensionalMSE = ones(2,1)
	cluster1path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	multiDstorage = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputJun3parallel/mutliDparams.txt"
	cluster1IDs = AbstractString[]
	cluster2IDs = AbstractString[]

	f = open(cluster1path)

	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster1IDs, strip(ln))
		end
	end
	close(f)
	g = open(cluster2path)
	for ln in eachline(g)
		if(length(ln)>1)
			push!(cluster2IDs, strip(ln))
		end
	end
	clusterlengths = [length(cluster1IDs), length(cluster2IDs)]

	allIDs = Array[]
	push!(allIDs, cluster1IDs)
	push!(allIDs, cluster2IDs)
	clusterCounter = 1
	for cluster in allIDs
		totalMSE = parallel_calculateTotalMSE(cluster,clusterCounter, params)
		
		@show totalMSE
		multidimensionalMSE[clusterCounter,1] = totalMSE/clusterlengths[clusterCounter]
		clusterCounter=clusterCounter+1
	end
	f = open(multiDstorage, "a")
	write(f, string(params, ",", multidimensionalMSE[1,1], ",", multidimensionalMSE[2,1],"\n"))
	close(f)
	@show multidimensionalMSE
	return multidimensionalMSE
end
