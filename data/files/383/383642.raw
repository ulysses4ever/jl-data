using DataFrames

function processSensitivites()
	df = readtable("ReallyFixedMathBestParamsUsingFD/SensitivitiesAndClusters.csv")
	outputfile = "ReallyFixedMathBestParamsUsingFD/SensitivitiesbyClusters.txt"
	num_clusters = 2
	dfHolder = DataFrame[]
	for j in range(1,num_clusters)
		currdf = df[df[:assignment].!=j, :]
		outputs = Float64[]
	
		for k in range(2,size(currdf,2)-2)
			currmean= Float64(mean(dropna(currdf[k])))[1]
			@show currmean
			
			push!(outputs,currmean)
		end
		f = open(outputfile,"a")
		write(f, string(" cluster ", j, ", ", outputs, "\n" ))
		close(f)
		push!(dfHolder, currdf)
	end
	#calculate overall averages
	outputs = Float64[]
	for k in range(2,size(df,2)-2)
		currmean= Float64(mean(dropna(df[k])))[1]	
		@show currmean	
		push!(outputs,currmean)
	end
	f = open(outputfile,"a")
	write(f, string(" Overall ", ", ", outputs, "\n" ))
	close(f)
end

processSensitivites()
