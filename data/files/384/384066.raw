using DataFrames
using Optim
include("OlufsenModel2011calcHRtweakedPlotOn.jl")

function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable("tempoutputG.csv", df)
	dfnew = readtable("tempoutputG.csv", separator=',')
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
	outputdir = "moretesting/currentbestMay31/"
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	allpatients = readdir(inputdir)
	dataWriteTo = string(outputdir, "usefuldatatolAll1E-4only2steps", ".txt")
	paramsWriteTo = string(outputdir, "paramstolAll1E-4only2steps", ".txt")
	touch(dataWriteTo)
	touch(paramsWriteTo)
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

			f = open(dataWriteTo, "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	overallMSE = totalMSE/usefulpatients
	g = open(paramsWriteTo, "a")
	write(g, string(params, ",", overallMSE, "\n"))
	close(g)
	return overallMSE
end

function makeGraphsForCluster(params)
	tic()
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	outputdir = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/graphsforcluster1Jun1/"
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

	dataWriteTo = string(outputdir, "usefuldatatolAll1E-4only2steps", ".txt")
	paramsWriteTo = string(outputdir, "paramstolAll1E-4only2steps", ".txt")
	touch(dataWriteTo)
	touch(paramsWriteTo)
	totalMSE = 0.0
	usefulpatients = 0.0

	#force positivity on all parameters
	lowerbound = 1E-9
	for j in range(1,length(params))
		if(params[j])<0
			params[j] = lowerbound
		end
	end
	allpatients = cluster1IDs
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

			f = open(dataWriteTo, "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	overallMSE = totalMSE/usefulpatients
	g = open(paramsWriteTo, "a")
	write(g, string(params, ",", overallMSE, "\n"))
	close(g)
	return overallMSE
end


#params0 = [119.5623539942,366.3460933283,0.7780693376,218.5663921848,38.3398575219,50.8979614138,2.4148727713,0.2570577866,0.4516920024,338.5960559755]
#calculatetotalMSE(params0)
bestparamscluster1 = [7.0412565739 0.4517491325 0.0590838127 60.0631494889 0.3801447431 0.0605251009 1.2330453563 0.0544532091 0.1044144738]
makeGraphsForCluster(bestparamscluster1)



