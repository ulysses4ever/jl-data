include("/home/rachel/Documents/optimization/SingleObjective/OOModelHighFreq.jl")
#include("/home/rachel/Documents/optimization/SingleObjective/OlufsenModel2011calcHRtweakedPlotOn.jl")
using PyPlot

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

function getClusterParams(pathtoclusterparams)
	number_of_parameters = 9
	f = open(pathtoclusterparams)
	alltext = readall(f)
	close(f)

	tempfile = "temp.txt"

	paramArray = zeros(number_of_parameters)
	for grouping in matchall(r"\[([^]]+)\]", alltext)
		cleanedgrouping = replace(grouping, "[", "")
		nocommas = replace(cleanedgrouping, ","," ")
		allcleaned = replace(nocommas, "]", "")
		outfile = open(tempfile, "w")
		write(outfile, allcleaned)
		close(outfile)
		formatted = readdlm(tempfile)
		paramArray=[paramArray transpose(formatted)]
	end

	return paramArray[:, 2:end]
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

function getGeneratedData(filename, numdatapoints)
	generatedData =zeros(numdatapoints)
	f = open(filename)
	alltext = readall(f)
	close(f)
	tempfile = "temp.txt"
	counter = 1
	for grouping in matchall(r"\[([^]]+)\]", alltext)
		cleanedgrouping = replace(grouping, "[", "")
		nocommas = replace(cleanedgrouping, ","," ")
		allcleaned = replace(nocommas, "]", "")
		outfile = open(tempfile, "w")
		write(outfile, allcleaned)
		close(outfile)
		formatted = readdlm(tempfile)
		@show size(formatted)
		if(mod(counter,2)==0)
			generatedData=[generatedData transpose(formatted)]
		end
		counter = counter+1
	end
	return generatedData[:, 2:end]
end

function getTimes(filename)
	
	f = open(filename)
	alltext = readall(f)
	close(f)
	tempfile = "temp.txt"
	counter = 1
	grouping =match(r"\[([^]]+)\]", alltext).match
	cleanedgrouping = replace(grouping, "[", "")
	nocommas = replace(cleanedgrouping, ","," ")
	allcleaned = replace(nocommas, "]", "")
	outfile = open(tempfile, "w")
	write(outfile, allcleaned)
	close(outfile)
	formatted = readdlm(tempfile)
	times=formatted
	return times
end

function generateData(patientID,outputdir)
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	pathtocluster1params = "/home/rachel/Documents/optimization/sensitivityanalysis/cluster1bestparams.txt"
	pathtocluster2params = "/home/rachel/Documents/optimization/sensitivityanalysis/cluster2bestparams.txt"
	#outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/cluster1figure/"
	datasavestr = string(outputdir, patientID, ".txt")
	allparamsets = getClusterParams(pathtocluster1params)
	#allparamsets = getClusterParams(pathtocluster2params)
	
	savestr = string(outputdir, "Id = ", patientID,"usingfewersteps", ".png")
	data, units= processNumericalData(string(inputdir, patientID))
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	cleaneddata = cleandata(data)
	for j in collect(1:size(allparamsets, 2))
		currparams = allparamsets[:, j]
		@show currparams
		MSE = calculateHeartRateForSaving(cleaneddata,currparams, savestr, datasavestr)
		
	end

	return cleaneddata

end

function linearInterp(lowerVal, upperVal, tstart, tend,step)
	val = lowerVal + (upperVal-lowerVal)/(tend-tstart)*step
	return val
end

function generateDataSingleObj(patientID,outputdir)
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	pathtoparams = "/home/rachel/Documents/optimization/SingleObjective/paramsSingleObjectiveJun20.txt"
	datasavestr = string(outputdir, patientID, ".txt")
	allparamsets = getClusterParams(pathtoparams)
	#allparamsets = getClusterParams(pathtocluster2params)
	
	savestr = string(outputdir, "Id = ", patientID,"usingfewersteps", ".png")
	data, units= processNumericalData(string(inputdir, patientID))
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	cleaneddata = cleandata(data)
	for j in collect(1:size(allparamsets, 2))
		currparams = allparamsets[:, j]
		@show currparams
		MSE = calculateHeartRateForSaving(cleaneddata,currparams, savestr, datasavestr)
		
	end

	return cleaneddata

end

function generateDataSingleObjHighF(patientID,outputdir)
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	pathtoparams = "/home/rachel/Documents/optimization/SingleObjective/paramsSingleObjectiveJun20.txt"
	inputdirHighFreqP = "../LinkedRecordsTimeData10minNonNumerics/"
	datasavestr = string(outputdir, patientID, ".txt")
	allparamsets = getClusterParams(pathtoparams)
	#allparamsets = getClusterParams(pathtocluster2params)
	
	savestr = string(outputdir, patientID)
	data, units= processNumericalData(string(inputdir, patientID))
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	cleaneddata = cleandata(data)
	highFreqData, units=processNumericalData(string(inputdirHighFreqP, patientID[1:end-1]))
		if(size(highFreqData,1)>0)
			highFreqCols = names(highFreqData)
		else
			highFreqCols = AbstractString[]

		end
	highFreqData = cleanHighFreqData(highFreqData)
	combinedframe = generateCombinedFrame(cleaneddata, highFreqData)
	for j in collect(1:size(allparamsets, 2))
		currparams = allparamsets[:, j]
		@show currparams
		MSE = calculateHeartRateHigherFdata(combinedframe,cleaneddata,currparams, savestr)
		
	end

	return cleaneddata

end

function makeGraph(data,times, MIMICdata,savestr)
	means = Float64[]
	stdevs = Float64[]
	for k in collect(1:size(data,1))
		currmean = mean(data[k,:])
		currstdev = std(data[k,:])
		push!(means, currmean)
		push!(stdevs, currstdev)
	end
	@show means
	@show MIMICdata[:_Elapsed_time_]
	@show MIMICdata[:_HR_]
	figure()
	hold("on")
	postive95conf = means+1.96.*stdevs
	negative95conf = means-1.96.*stdevs	
	plot(times, transpose(means), "k.")
	plot(MIMICdata[:_Elapsed_time_], MIMICdata[:_HR_], "x", color = ".25")
	fill_between(squeeze(times,1), squeeze(transpose(negative95conf),1), squeeze(transpose(postive95conf),1), color = ".75")
	xlabel("Time in Seconds", fontsize=18)
	ylabel("Heart Rate, in BPM", fontsize=18)
	savefig(savestr)
end

function makeGraphSingle(data,times, MIMICdata,savestr)
	@show data
	p1=plot(MIMICdata[:_Elapsed_time_], MIMICdata[:_HR_], "x", color = "0.0") #actual data
	p2=plot(times, transpose(data[:,1]), "v", color = ".5",markeredgewidth=0.0,markersize = 2.5) #using original params
	p3= plot(times, transpose(data[:,2]), "o", color = ".25",markeredgewidth=0.0,markersize = 2.5) #using new estimated params
	xlabel("Time in Seconds", fontsize=18)
	ylabel("Heart Rate, in BPM", fontsize=18)
	#legend([p1,p2,p3],["Actual Data", "Using Original Parameters", "Using Optimized Parameters"])
	ax = gca()
	ax[:set_ylim]([0,220])
	savefig(savestr)
end

function mainforclusters()
	cluster1path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	cluster1IDs = AbstractString[]
	cluster2IDs = AbstractString[]

	f = open(cluster1path)
	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster1IDs, strip(ln))
		end
	end
	close(f)
#	f = open(cluster2path)
#	for ln in eachline(f)
#		if(length(ln)>1)
#			push!(cluster2IDs, strip(ln))
#		end
#	end
#	close(f)


	for patientID in cluster1IDs
		close("all")
		@show patientID
		
		mainoutputdir = "/home/rachel/Documents/optimization/singleobjective/highFreqFigures/"
		MIMICdata = generateData(patientID,mainoutputdir)
		curroutput = string(mainoutputdir, patientID, ".txt")
		times =getTimes(curroutput)
		numdatapoints = size(times,2)
		alldata = getGeneratedData(curroutput,numdatapoints)
		savestr = string(mainoutputdir, patientID, ".pdf")
		makeGraph(alldata,times, MIMICdata,savestr)
	end
end

function mainforSingleObjective()
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

	for patientID in allpatients
		close("all")
		@show patientID
		
		mainoutputdir = "/home/rachel/Documents/optimization/SingleObjective/outputfigsusingJun20bestparams/"
		MIMICdata = generateDataSingleObj(patientID,mainoutputdir)
		curroutput = string(mainoutputdir, patientID, ".txt")
		times =getTimes(curroutput)
		numdatapoints = size(times,2)
		alldata = getGeneratedData(curroutput,numdatapoints)
		savestr = string(mainoutputdir, patientID, ".pdf")
		makeGraphSingle(alldata,times, MIMICdata,savestr)
	end
end

function mainforSingleObjectiveHighF()
	highFpatientsPath = "/home/rachel/Documents/optimization/SingleObjective/usefulpatientsThrowingAwayBadPdata.txt"
	
	allpatients = AbstractString[]

	f = open((highFpatientsPath))
	for ln in eachline(f)
		if(length(ln)>1)
			push!(allpatients, strip(ln))
		end
	end
	close(f)

	#shuffle!(allpatients)
	for patientID in allpatients
		close("all")
		@show patientID
		mainoutputdir = "/home/rachel/Documents/optimization/SingleObjective/highFreqFiguresJul11lowtol/"
		MIMICdata = generateDataSingleObjHighF(patientID,mainoutputdir)
		curroutput = string(mainoutputdir, patientID, ".txt")
		times =getTimes(curroutput)
		numdatapoints = size(times,2)
		alldata = getGeneratedData(curroutput,numdatapoints)
		savestr = string(mainoutputdir, patientID, ".pdf")
		makeGraphSingle(alldata,times, MIMICdata,savestr)
	end
end
