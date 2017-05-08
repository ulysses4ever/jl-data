include("/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/OlufsenModel2011calcHRtweaked.jl")
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

function getClusterParams(pathtoclusterparams)
	number_of_parameters = 13
	allparams = readdlm(pathtoclusterparams)
	return transpose(allparams)

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

function getAverageMSE(patientID,outputdir)
	inputdir = "/home/rachel/Documents/work/optimization/LinkedRecordsTimeData10min/"
	pathtocluster1params = "/home/rachel/Documents/work/optimization/sensitivityanalysis/cluster1bestparamskeep.txt"
	pathtocluster2params = "/home/rachel/Documents/work/optimization/sensitivityanalysis/cluster2bestparamskeep.txt"
	#outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/cluster1figure/"
	datasavestr = string(outputdir, patientID, ".txt")
	#allparamsets = getClusterParams(pathtocluster1params)
	allparamsets = getClusterParams(pathtocluster2params)
	
	savestr = string(outputdir, "Id = ", patientID,"usingfewersteps", ".png")
	data, units= processNumericalData(string(inputdir, patientID))
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	cleaneddata = cleandata(data)
	totalMSE = 0.0
	@show size(allparamsets, 2)
	for j in collect(1:size(allparamsets, 2))
		currparams = allparamsets[:, j]
		#@show currparams
		MSE = calculateHeartRateForSaving(cleaneddata,currparams, savestr, datasavestr)
		@show MSE
		totalMSE = MSE +totalMSE
		
	end

	avgMSE = totalMSE/size(allparamsets,2)
	return cleaneddata, avgMSE

end

function writeMSEtoFile(filename,patientID,MSE)
	f = open(filename, "a")
	write(f, string(patientID, ",", MSE, "\n"))
	close(f)
end

function generateDataSingleObj(patientID,outputdir)
	inputdir = "/home/rachel/Documents/work/optimization/LinkedRecordsTimeData10min/"
	pathtoparams ="/home/rachel/Documents/work/optimization/sensitivityanalysis/usingSALib/morrisParamsN100.txt" 
	pathToMSEAllParams = string(outputdir, "MSEAllParams.txt")
	allparamsets = getClusterParams(pathtoparams)
	#allparamsets = [[1.5,75.0,120.0, 1.5, 1.5, .5, 250.0, .5, .5, 6, 1.67, .96, .7]]

	savestr = string(outputdir, "Id = ", patientID,"usingfewersteps", ".png")
	data, units= processNumericalData(string(inputdir, patientID))
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	cleaneddata = cleandata(data)
	for j in collect(1:size(allparamsets, 2))
		currparams = allparamsets[:, j]
		datasavestr = string(outputdir, patientID, "paramset", j, ".txt")
		@show currparams
		MSE = calculateHeartRateForSaving(cleaneddata,currparams, savestr, datasavestr)
		writeMSEtoFile(pathToMSEAllParams,patientID,MSE)
		
	end

	return cleaneddata

end


function mainforSingleObjective()
	cluster1path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
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
	#[1:length(allpatients)][allpatients .=="s17795-3483-10-23-06-36n"] #to look up index of a patient
	for j in collect(158:length(allpatients))
		close("all")
		patientID = allpatients[j]
		@show patientID
		
		mainoutputdir = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/data25PercentMorrisN100/"
		MIMICdata = generateDataSingleObj(patientID,mainoutputdir)

	end
end


