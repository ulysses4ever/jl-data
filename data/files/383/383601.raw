using DataFrames

function averageSobolOutput(datadir)
	filenames = readdir(datadir)
	for fn in filenames
		@show fn
		if(contains(fn, "SobolResults"))
			data= readtable(string(datadir,fn), header = true,  separator = ' ',makefactors = true, nrows = 13, eltypes = [UTF8String, Float64, Float64, Float64, Float64])
			@show data
		end
	end
end

averageSobolOutput("/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/PCAProcessedOutputSept9/")
