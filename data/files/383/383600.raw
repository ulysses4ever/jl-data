#to agglomerate data for each patient

function processFPCAdata(numParamSets, dataDir,inNameStr, outNameStr,outputdir)
	filenames = readdir(dataDir)
	counter = 1
	while(counter<=numParamSets)
		nameStr = string(inNameStr, counter)
		file = string(dataDir,nameStr, ".txt")
			data = readdlm(file)
			for k in collect(1:size(data,1))
				fn = string(outputdir, outNameStr, k, ".txt")
				f = open(fn, "a+")
				write(f, string(string(data[k,:])[2:end-1], "\n"))
				close(f)
			end
		counter = counter+1
	end

end

function main()
	numParamSets = 28
	dataDir = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/PCAoutputSept8Take2/"
	inNameStr = "PCscores"
	outNameStr = "PCScoresForPatient"
	outputdir = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/PCAProcessedOutputSept9/"
	processFPCAdata(numParamSets, dataDir,inNameStr, outNameStr,outputdir)
end
