using DataFrames
using PyPlot

function findUsefulPatients()
	usefulPatients = AbstractString[]
	possPatients = readdlm("linkedRecordsnonNumeric.txt")
	lowFdata = Any[]
	highFdata = Any[]
	for person in possPatients
		lowFstring = string(person, "n")
		try 
			lowFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$lowFstring -p -v -H -t 600 -c`)), ',', '\n');
			highFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$person -p -v -H -t 600 -c`)), ',', '\n');
			@show lowFdata[1:3, :]
			@show highFdata[1:3, :]
		catch 
			lowFdata = Any[]
			highFdata = Any[]

		end
		if(testLowFData(lowFdata) && testHighFData(highFdata))
			@show person
			push!(usefulPatients, person)
		end
		@show usefulPatients
	end
	writedlm("usefulPatients.txt", usefulPatients)
end

function testLowFData(lowFdata)
	@show size(lowFdata)
	if(size(lowFdata,1)>=600)
		return true
	end
	
	return false
end

function testHighFData(highFdata)
	if(size(highFdata,1)>0)
		@show string(highFdata[1,:])
		if(contains(string(highFdata[1,:]), "ABP"))
			return true
		end
	end
	return false
end

function processUsefulPatients()
	actuallyUsefulPatients = AbstractString[]
	usefulPatients = readdlm("usefulPatients.txt")
	for patient in usefulPatients
		lowFstring = string(patient, "n")
		lowFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$lowFstring -p -v -H -t 600 -c`)), ',', '\n');
		highFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$patient -p -v -H -t 600 -c`)), ',', '\n');
		#@show lowFdata[lowFdata .=="-"]
		lowFdata[lowFdata .=="-"] =0.0
		highFdata[highFdata.=="-"] = 0.0
		lowFdataDF=  DataFrame(lowFdata);
		highFdataDF = DataFrame(highFdata); 
		lowFnames = Symbol[]
		highFnames = Symbol[]
		for j in collect(1:size(lowFdata,2))
			push!(lowFnames, replace(replace(strip(lowFdata[1,j]), " ", ""), "'", ""))
		end

		for j in collect(1:size(highFdata,2))
			push!(highFnames, replace(replace(strip(highFdata[1,j]), " ", ""), "'", ""))
		end

		#@show lowFnames
		names!(lowFdataDF, lowFnames)
		names!(highFdataDF, highFnames)
		deleterows!(lowFdataDF, 1:2)
		deleterows!(highFdataDF, 1:2)
		#@show head(lowFdataDF)
		@show countnz(highFdataDF[:ABP])
		nonzeros = countnz(highFdataDF[:ABP])

		if(nonzeros>100)
			plotData(lowFdataDF, highFdataDF, patient)
			push!(actuallyUsefulPatients, patient)
		end
	end
	writedlm("ActuallyUsefulPatients.txt", actuallyUsefulPatients)
end

function plotData(lowFdata, highFdata, patient)
	close("all")
	#@show lowFdata[:Elapsedtime]
	figure()
	plt[:subplot](2,1,1)
	plot(lowFdata[:Elapsedtime], lowFdata[:HR], "k.")
	plt[:subplot](2,1,2)
	plot(highFdata[:Elapsedtime], highFdata[:ABP], "k-")
	@show string("figures/",patient[8:end], ".pdf")
	savefig(string("figures/",patient[8:end], ".pdf"))

end

function extractdata(patient)
		lowFstring = string(patient, "n")
		lowFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$lowFstring -p -v -H -t 600 -c`)), ',', '\n');
		highFdata =  readdlm(IOBuffer(readall(`rdsamp -r mimic2wdb/matched/$patient -p -v -H -t 600 -c`)), ',', '\n');
		lowFdata[lowFdata .=="-"] =0.0
		highFdata[highFdata.=="-"] = 0.0
		lowFdataDF=  DataFrame(lowFdata);
		highFdataDF = DataFrame(highFdata); 
		lowFnames = Symbol[]
		highFnames = Symbol[]
		for j in collect(1:size(lowFdata,2))
			push!(lowFnames, replace(replace(strip(lowFdata[1,j]), " ", ""), "'", ""))
		end

		for j in collect(1:size(highFdata,2))
			push!(highFnames, replace(replace(strip(highFdata[1,j]), " ", ""), "'", ""))
		end

		#@show lowFnames
		names!(lowFdataDF, lowFnames)
		names!(highFdataDF, highFnames)
		deleterows!(lowFdataDF, 1:2)
		deleterows!(highFdataDF, 1:2)
		return lowFdataDF, highFdataDF;
	
end
