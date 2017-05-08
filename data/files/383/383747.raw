using DataFrames
using Optim
include("OOModelHighFreq.jl")

function processNumericalData(filename)
	filesize = stat(filename).size
	if(filesize>0)
		df=readtable(filename, separator=',',nastrings=["-"])
		units = df[1,:]
		deleterows!(df,1) #remove the row that had units
		writetable("tempoutputG.csv", df)
		dfnew = readtable("tempoutputG.csv", separator=',')
	else
		dfnew = DataFrame()
		units = AbstractString[]
	end
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

function cleanHighFreqData(data)
	data[~isna(data[:,symbol("_ABP_")]),:]	
	deleterows!(data,find(isna(data[:,symbol("_ABP_")])))
	numrows = size(data,1)
	j = 1
	while(j<numrows)
		if(data[:_ABP_][j]<40.0)
			deleterows!(data,j)# remove unphysical measurements
		end
		numrows = size(data,1)
		j = j+1
	end

	return data
end

function linearInterp(lowerVal, upperVal, tstart, tend,step)
	val = lowerVal + (upperVal-lowerVal)/(tend-tstart)*step
	return val
end

function generateCombinedFrame(lowFdata, highFdata)
	CombinedFrame = DataFrame()
	CombinedFrame[:_Elapsed_time_] = highFdata[:_Elapsed_time_]
	CombinedFrame[:_ABP_]= highFdata[:_ABP_]
	CombinedFrame[:_HR_] = @data(squeeze(fill(1.0,size(CombinedFrame,1),1),2))
	@show head(lowFdata)
	@show head(highFdata)	

	prevHR = lowFdata[:_HR_][1]
	prevT = lowFdata[:_Elapsed_time_][1]
	currHR = lowFdata[:_HR_][2]
	currT = lowFdata[:_Elapsed_time_][2]
	#step = 1.0/125.0 #high freq data collected at 125 hz
	slowCounter = 3

	maxSlowCounter = size(lowFdata,1)
	startT = CombinedFrame[:_Elapsed_time_][1]
	for j in collect(1:size(CombinedFrame,1))
		step = CombinedFrame[:_Elapsed_time_][j]-startT #calculate step size
		CombinedFrame[:_HR_][j] = linearInterp(prevHR, currHR,prevT, currT, step) #calculate interpolated heart rate
		#@show CombinedFrame[:_HR_][j], linearInterp(prevHR, currHR,prevT, currT, step)
		if(CombinedFrame[:_Elapsed_time_][j]>currT) #if we've moved past the upper limits for interpolating, set new limits
			prevT = currT
			prevHR = currHR
			startT =CombinedFrame[:_Elapsed_time_][j]
		
			currHR=lowFdata[:_HR_][slowCounter]
			currT = lowFdata[:_Elapsed_time_][slowCounter]
			if(slowCounter<maxSlowCounter)
				slowCounter = slowCounter+1
			end
		end

	end
	return CombinedFrame
end

function calculatetotalMSE(params)
	tic()
	outputdir = "/moretesting/higherFreqPbestParams/"
	inputdir = "../LinkedRecordsTimeData10min/"
	inputdirHighFreqP = "../LinkedRecordsTimeData10minNonNumerics/"
	allpatients = readdir(inputdir)
	#allpatients =["s00652-2965-06-14-18-19n"]
	highFreqPatients = readdir(inputdirHighFreqP)
	dataWriteTo = string(outputdir, "usefuldatatolAll1E-4only2steps", ".txt")
	paramsWriteTo = string(outputdir, "paramstolAll1E-4only2steps", ".txt")
	#touch(dataWriteTo)
	#touch(paramsWriteTo)
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
		println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient)
		data, units= processNumericalData(string(inputdir, patient))
		if(in(patient[1:end-1], highFreqPatients))
			highFreqData, units=processNumericalData(string(inputdirHighFreqP, patient[1:end-1]))
			if(size(highFreqData,1)>0)
				highFreqCols = names(highFreqData)
			else
				highFreqCols = AbstractString[]

			end
			sort!(data, cols = [order(:_Elapsed_time_)])
			colnames = (names(data))
			if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2) &&in(:_ABP_, highFreqCols)&&(length(highFreqData[:_Elapsed_time_])>2))
				println("has complete data")
				data = cleandata(data)
				highFreqData = cleanHighFreqData(highFreqData)
				if(size(data,1)>5 && size(highFreqData,1)>5)
					combinedframe = generateCombinedFrame(data, highFreqData)
					@show head(combinedframe)
					#MSE= calculateHeartRate(data, params,savestr)
					MSE = calculateHeartRateHigherFdata(combinedframe, data, params, savestr)
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
		end
		overallMSE = totalMSE/usefulpatients
		g = open(paramsWriteTo, "a")
		write(g, string(params, ",", overallMSE, "\n"))
		close(g)
	end
	toc()
	return overallMSE
end

function findpatients()
	tic()
	outputdir = "/home/rachel/Documents/optimization/SingleObjective/moretesting/higherFreqPbestParams/"
	inputdir = "../LinkedRecordsTimeData10min/"
	inputdirHighFreqP = "../LinkedRecordsTimeData10minNonNumerics/"
	#allpatients = readdir(inputdir)
	#allpatients =["s00652-2965-06-14-18-19n"]
	highFreqPatients = readdir(inputdirHighFreqP)
	dataWriteTo = string(outputdir, "usefulpatientsThrowingAwayBadPdataStartingWClusteredPatients", ".txt")
	paramsWriteTo = string(outputdir, "paramstolAll1E-4only2steps", ".txt")
	touch(dataWriteTo)
	touch(paramsWriteTo)
	totalMSE = 0.0
	usefulpatients = 0.0
	cluster1path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	allpatients = AbstractString[]

	f = open(cluster1path)
	for ln in eachline(f)
		if(length(ln)>1)
			push!(allpatients, strip(ln))
		end
	end
	close(f)

	f = open(cluster2path)
	for ln in eachline(f)
		if(length(ln)>1)
			push!(allpatients, strip(ln))
		end
	end
	close(f)


	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient)
		data, units= processNumericalData(string(inputdir, patient))
		if(in(patient[1:end-1], highFreqPatients))
			highFreqData, units=processNumericalData(string(inputdirHighFreqP, patient[1:end-1]))
			if(size(highFreqData,1)>0)
				highFreqCols = names(highFreqData)
			else
				highFreqCols = AbstractString[]

			end
			sort!(data, cols = [order(:_Elapsed_time_)])
			colnames = (names(data))
			if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2) &&in(:_ABP_, highFreqCols)&&(length(highFreqData[:_Elapsed_time_])>2))
				println("has complete data")
				data = cleandata(data)
				highFreqData = cleanHighFreqData(highFreqData)
				if(size(data,1)>5 && size(highFreqData,1)>5)
					combinedframe = generateCombinedFrame(data, highFreqData)
					@show head(combinedframe)
					#MSE= calculateHeartRate(data, params,savestr)
					#MSE = calculateHeartRateHigherFdata(combinedframe, data, params, savestr)
					#@show MSE
					#if(contains(string(typeof(MSE)), "Void"))
					#	continue
					#end
					#totalMSE = MSE + totalMSE
					usefulpatients = usefulpatients +1

					f = open(dataWriteTo, "a")
					f = write(f, string(patient, "\n"))
					close(f)
				end
			end
		end
		#overallMSE = totalMSE/usefulpatients
		#g = open(paramsWriteTo, "a")
		#write(g, string(patient, "\n"))
		#close(g)
	end
	toc()
	#return overallMSE
end

#params = [75.0,1.5,0.5,250.0,0.5,0.5,1.67,0.96,0.7]
#bestparams =[107.33612908104033,41.138842557517954,14.062116217939991,202.92519160829795,2.941876046317941e-5,8.15596008945017,1.4743606995666585,0.1654851281383664,0.05218327316554491]
#calculatetotalMSE(bestparams)

