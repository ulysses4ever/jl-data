using DataFrames

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

function removeCols(data,desiredColumns)
	counter = 1
	colnames = names(data)
	for name in colnames
		if(!in(string(name), desiredColumns))
			delete!(data, name)
		end
		counter+=1
	end
	return data
end

function getUsefulData(filename)
	data,units = processNumericalData(filename)
	sort!(data, cols = [order(:_Elapsed_time_)])
	colnames = (names(data))
	desiredColumns = ["_Elapsed_time_", "_HR_", "_ABP_Mean_"]
	if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			#println("has complete data")
			data = cleandata(data)
			data = removeCols(data, desiredColumns)
	end
	#@show data
	return data
end

function getPressureAtSelectedTime(time, data)
	#if time is less than where we have data for, return average P, do same if time greater
	currP = 0
	fudgefactor = .5
	if(time < data[:_Elapsed_time_][1]-fudgefactor)
		currP = mean(data[:_ABP_Mean_])

	elseif(time > data[:_Elapsed_time_][end]+fudgefactor)
		currP = mean(data[:_ABP_Mean_])
	else
		println("in interp")
		interP = data[(data[:_Elapsed_time_].<=time+fudgefactor) & (data[:_Elapsed_time_].>=time-fudgefactor), :_ABP_Mean_]
		@show interP
		if(size(interP,1)==0)
			interP = mean(data[:_ABP_Mean_])
		else
			currP = interP[1]
		end
		
	end
	@show (time, currP)
	return currP
end
