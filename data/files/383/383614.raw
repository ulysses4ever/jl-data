using RCall;
using DataFrames;

function generateSampleData(numpatients, numtimepoints)
	#generate a matrix with numpatients row and numtimepoints colms
	data = 100.0+25.0*(.5-rand(numpatients,numtimepoints))
	@show typeof(data)
	return data

end

function doPCA(data)
	N = size(data,2)
	M = size(data,1)
	mn = mean(data,2)
	data =data.-mn #subtract off mean
	cov = 1./(N-1)*data*transpose(data)
	v,PC = eig(cov)
	sortedindices =sortperm(-v)
	#extract the largest ones
	v = sort(v)
	PC = PC[:,sortedindices]
	#project data
	signals = transpose(PC)*data 
	
end

function doPCAoverTime(data)
	for j in collect(1:size(data,1))
		currdata = data[:,j]
		doPCA(currdata)
	end
end

function main()
	sampleData = generateSampleData(3,10)
	times = float(ones(3,10).*transpose(collect(1:10)))
	#load the library neccessary into R
	R"library(fdapace)"
	@rput (sampleData)
	@rput times
	R"sampleData<data.frame(sampleData)"
	R"times<-data.frame(times)"
	#convert to lists
	R"datalist = list()"
	R"for (i in seq(1,nrow(sampleData))){datalist[[i]]<-as.numeric(as.vector(sampleData[i,]))}"
	R"timelist = list()"
	R"for (i in seq(1,nrow(times))){timelist[[i]]<-as.numeric(as.vector(times[i,]))}"
	
	outputFPCA=R"FPCA(datalist, timelist, list(error=FALSE, kernel='epan', verbose=TRUE, diagnosticsPlot=TRUE,userBwCov = 10))"
	convoutput =rcopy(outputFPCA)
	return convoutput
end
