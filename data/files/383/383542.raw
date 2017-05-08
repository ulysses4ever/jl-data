using DataFrames

@everywhere function processNumericalData(filename)
	n=readline(filename)
	n = chomp(n) #remove trailing newline
	n = replace(n, ' ', '_')# replace spaces with underscores
	tempcolnames = split(n, ',')
	colnames = Symbol[]
	for j in 1:length(tempcolnames)
		push!(colnames, Symbol(replace(tempcolnames[j], '\'', "")))
	end
	#df=DataFrames.readtable(filename, separator=',',nastrings=["-"])
	dfattempt2=DataFrames.readtable(filename, header = false, skipstart = 2, separator=',',nastrings=["-"], eltypes = vec(fill(Float64,1,length(colnames))), names = colnames) #so we don't have to rewrite
	#units = df[1,:]
	#DataFrames.deleterows!(df,1) #remove the row that had units
	#DataFrames.writetable(string("tempoutputTA", myid(),".csv"), df)
	#dfnew = DataFrames.readtable(string("tempoutputTA", myid(),".csv"), separator=',')
	return dfattempt2, Float64[]
end

@everywhere function cleandata(data)
	#remove any rows with NAs in the places I care about
	data[~isna(data[:,symbol("ABP_Mean")]),:]	
	DataFrames.deleterows!(data,find(isna(data[:,symbol("ABP_Mean")])))
	data[~isna(data[:,symbol("HR")]),:]	
	DataFrames.deleterows!(data,find(isna(data[:,symbol("HR")])))

	if(length(data[:Elapsed_time])>2)
		timediff = data[:Elapsed_time][2]-data[:Elapsed_time][1]
		#@show(timediff)
		if (timediff > 10) #if there's a big gap between first and second measurement, throw out first one, start analysis at second point
			DataFrames.deleterows!(data,1)
			println("found large gap and removed it")
		end
	end

	return data
end

@everywhere function removeCols(data,desiredColumns)
	counter = 1
	colnames = DataFrames.names(data)
	for name in colnames
		if(!in(string(name), desiredColumns))
			DataFrames.delete!(data, name)
		end
		counter+=1
	end
	return data
end

@everywhere function getUsefulData(filename)
	data,units = processNumericalData(filename)
	sort!(data, cols = [DataFrames.order(:Elapsed_time)])
	colnames = DataFrames.names(data)
	desiredColumns = ["Elapsed_time", "HR", "ABP_Mean"]
	if(in(:ABP_Mean, colnames) && in(:HR, colnames)&& (length(data[:Elapsed_time])>2))
			#println("has complete data")
			data = cleandata(data)
			data = removeCols(data, desiredColumns)
	end
	#@show data
	return data
end

@everywhere function getPressureAtSelectedTime(time, data)
	#if time is less than where we have data for, return average P, do same if time greater
	currP = 0
	fudgefactor = .5
	if(time < data[:Elapsed_time][1]-fudgefactor)
		currP = mean(data[:ABP_Mean])

	elseif(time > data[:Elapsed_time][end]+fudgefactor)
		currP = mean(data[:ABP_Mean])
	else
		println("in interp")
		interP = data[(data[:Elapsed_time].<=time+fudgefactor) & (data[:Elapsed_time].>=time-fudgefactor), :ABP_Mean]
		@show interP
		if(size(interP,1)==0)
			interP = mean(data[:ABP_Mean])
		else
			currP = interP[1]
		end
		
	end
	#@show (time, currP)
	return currP
end
