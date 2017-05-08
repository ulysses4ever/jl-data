using RCall;

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

function readData(dataDir, searchStr)
	times =Array{Float64}[]
	hrdata = Array{Float64}[]
	alltimepoints = size(collect(.5:.5:599),1)
	filenames = readdir(dataDir)
	#@show filenames
	for fn in filenames
		#@show searchStr
		if(contains(fn, searchStr))
			txt = readdlm(string(dataDir,fn), header=false, ',')
			#@show txt
			#odd lines contain times, even lines contain hr
			numrows = size(txt, 1)
			numcols = size(txt,2)


			for j in collect(1:2)
				if(mod(j,2)==0)
					push!(hrdata, txt[j,:])
				else
					push!(times, txt[j,:])
				end
			end
		end
	end

	return times, hrdata
end

function reshapeData(data)
	#takes in an Array of Arrays
	maxsize = size(collect(.5:.5:599),1)
	output = Array{Float64}(size(data,1), maxsize)
	for j in collect(1:size(data,1)) #for each array in the array
		currdata = data[j]
		len = size(currdata,2)
		filledvec = [union(currdata[1:len]); fill(-1, maxsize-len,1)]   #using union to remove duplicates
		#@show size(filledvec)
		for k in collect(1:size(filledvec,1))
			#@show(j,k)
			output[j,k] = filledvec[k]
		end
	end
	return output
end

function writeEigenFunctionsToFiles(output,outputdir)
	file1EF = string(outputdir,"firstEF.txt")
	file2EF = string(outputdir,"secondEF.txt")
	file3EF = string(outputdir,"thirdEF.txt")
	file4EF = string(outputdir,"fourthEF.txt")
	file5EF = string(outputdir,"fifthEF.txt")
	file6EF = string(outputdir,"sixthEF.txt")
	file7EF = string(outputdir,"seventhEF.txt")
	file8EF = string(outputdir,"eighthEF.txt")

	EFs = output[:phi]
	files = [file1EF, file2EF, file3EF, file4EF, file5EF, file6EF, file7EF, file8EF]

	counter = 1
	for file in files
		touch(file)
		f=open(file, "a+")
		cleanedEF= string(EFs[:,counter])[2:end-1]
		#[2:end-1] is to remove brackets
		write(f, string(cleanedEF, "\n"))
		close(f)
		counter=counter+1
	end

	
end

function writeCumFVEtoFile(output,outputdir)
	filename = string(outputdir,"CumFVE.txt")
	cumFVE = output[:cumFVE]
	touch(filename)
	f = open(filename, "a+")
	cleanedFVE = string(cumFVE)[2:end-1]
	write(f, string(cleanedFVE, "\n"))
	close(f)
end	

function main()
	#sampleData = generateSampleData(3,10)
	#times = float(ones(3,10).*transpose(collect(1:10)))
	dataDir = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/testingdata25percent/"
	outputdir = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/crashtest/"
	#load the library neccessary into R
	R"library(fdapace)"
	numberOfSamples = 28

	for k in collect(8:numberOfSamples)
		tic()
		searchStr = string("set",k,".Cleaned")
		tic()
		times, sampleData = readData(dataDir, searchStr)
		toc()
		times = reshapeData(times)
		sampleData = reshapeData(sampleData)
		@show size(times)


		#transfer the data from Julia to R
		@rput (sampleData)
		@rput times

		#R"sampleData"
		#convert the data in R to dataframes
		R"sampleDatadf<-data.frame(sampleData)"
		R"timesdf<-data.frame(times)"
		#remove filler text
		R"sampleDatadf[sampleDatadf==-1]<-NA"
		R"timesdf[timesdf==-1]<-NA"

		#remove NAs
		R"cleanedData<-data.frame()"
		R"cleanedTimes<-data.frame()"
		#R"for (i in seq(1,nrow(sampleDatadf))){idx<-!is.na(sampleDatadf[i,]); cleanedData[[i]]<-sampleDatadf[i,idx]}"
		#R"for (i in seq(1,nrow(timesdf))){idx<-!is.na(timesdf[i,]); cleanedTimes[[i]]<-timesdf[i,idx]}"

		#R"for (i in seq(1,nrow(sampleDatadf))){idx<-!is.na(sampleDatadf[i,]); sampleDatadf[i,]<-sampleDatadf[i,idx]}"
		#R"for (i in seq(1,nrow(timesdf))){idx<-!is.na(timesdf[i,]); timesdf[i,]<-timesdf[i,idx]}"

	#	#convert to lists
		R"datalist = list()"
		#R"for (i in seq(1,nrow(sampleDatadf))){datalist[[i]]<-as.numeric(as.vector(na.omit(sampleDatadf[i,])))}"
		R"for (i in seq(1,nrow(sampleDatadf))){cleanedvector<-sampleDatadf[i,];length(cleanedvector)<-sum(!is.na(cleanedvector));datalist[[i]]<-as.numeric(cleanedvector)}"
		R"timelist = list()"
		#R"for (i in seq(1,nrow(timesdf))){timelist[[i]]<-as.numeric(as.vector(na.omit(timesdf[i,])))}"
		R"for (i in seq(1,nrow(timesdf))){cleanedvector<-timesdf[i,];length(cleanedvector)<-sum(!is.na(cleanedvector));timelist[[i]]<-as.numeric(cleanedvector)}"
		datalist = rcopy(R"datalist")
		timelist = rcopy(R"timelist")

		#@show datalist

		writedlm(string(outputdir,"timelistSet", k, ".txt"), timelist)
		writedlm(string(outputdir,"datalistSet", k, ".txt"), datalist)	
	
	#	#run FPCA
		tic()
		outputFPCA=R"FPCA(datalist, timelist, list(error=FALSE, kernel='epan', verbose=TRUE, diagnosticsPlot=TRUE,userBwCov = 10, maxK = 10))"
		toc()
		#outputFPCA=R"FPCA(sampleData, times, list(error=FALSE, kernel='epan', verbose=TRUE, diagnosticsPlot=TRUE,userBwCov = 10))"
		#transfer the output back to Julia
		convoutput =rcopy(outputFPCA)
		writeEigenFunctionsToFiles(convoutput,outputdir)
		writeCumFVEtoFile(convoutput,outputdir)
		toc()
	end
	return convoutput
end
