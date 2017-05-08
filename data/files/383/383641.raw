#to process outputs from the multiobjective sensitivity analysis
using DataFrames

function processMultiobjectiveSensitivities()
	dirOfInterest = "/home/rachel/Documents/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsCluster1n10Jun22/"
	outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsIntermediateDirCluster1n10Jun22/"
	filesinDir = readdir(dirOfInterest)
	usefulfiles = AbstractString[]
	totaldata = DataFrame(patientIDs = Any[], dhdN = Any[], dhdk1=Any[], dhdtau1 = Any[], dhdtau2 = Any[], dhdtauach = Any[], dhdtaunor = Any[], dhdh0 = Any[], dhdmnor = Any[], dhdmach = Any[])
	#totaldata = DataFrame(x1=Any[], x2 = Any[], x3 = Any[], x4 = Any[], x5 = Any[], x6=Any[], x7=Any[], x8=Any[], x9 = Any[], x10=Any[])
	for name in filesinDir
		if(contains(name, "S0"))
			push!(usefulfiles, name)
		end
	end
	@show usefulfiles
	
	for file in usefulfiles
		allinfo = readall(string(dirOfInterest, file))
		cleanedinfo = replace(replace(allinfo, "[", ""), "]", "")
		outputfilename =string(outputdir, file, "cleaned.txt")
		touch(outputfilename)
		f = open(outputfilename, "w")
		write(f,cleanedinfo)
		close(f)
		data = readtable(outputfilename, header = false)
		#@show typeof(data[:x2])
		for row in eachrow(data)
			usefulrow = convert(Array, row)		
			push!(totaldata,usefulrow)
		end
	end
	@show size(totaldata)
	summary =DataFrame(name =Any[], mean= Float64[], stdev = Float64[])
	for j in collect(2:size(totaldata,2))
		println(string("for column ", names(totaldata)[j], " mean ", mean(totaldata[j]), " std ", std(totaldata[j])))
		push!(summary, @data([names(totaldata)[j], mean(totaldata[j]), std(totaldata[j])]))
	end
	sort!(summary, cols=[order(:mean)] )
	@show summary
	writetable(string(outputdir, "with10setsofparams.txt"),summary)
end
