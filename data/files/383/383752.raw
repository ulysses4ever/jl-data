using DataFrames
using Optim
include("OlufsenModel2011calcHR.jl")

function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable("tempoutput.csv", df)
	dfnew = readtable("tempoutput.csv", separator=',')
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

function calculatetotalMSE(params)
	tic()
	outputdir = "moretesting/"
	inputdir = "/home/rachel/Documents/optimization/5testingRecords10min/"
	allpatients = readdir(inputdir)
	touch(string(outputdir, "usefuldata.txt"))
	touch(string(outputdir, "params.txt"))
	totalMSE = 0.0
	usefulpatients = 0.0
	@show params
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		#println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient, ".png")
		data, units= processNumericalData(string(inputdir, patient))
		sort!(data, cols = [order(:_Elapsed_time_)])
		colnames = (names(data))
		if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			#println("has complete data")
			data = cleandata(data)
			MSE= calculateHeartRate(data, params,savestr)
			@show MSE
			if(contains(string(typeof(MSE)), "Void"))
				continue
			end
			totalMSE = MSE + totalMSE
			usefulpatients = usefulpatients +1

			f = open(string(outputdir,"usefuldata.txt"), "a")
			write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	MSE = totalMSE/usefulpatients
	g = open(string(outputdir, "params.txt"), "a")
	write(g, string(params, ",", MSE, "\n"))
	close(g)
	return MSE
end

function attemptOptimization()
	params0 = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	res = optimize(calculatetotalMSE, params0,method = Optim.NelderMead(), show_trace = true, ftol = 1E-3)
	@show res
	return res
end
attemptOptimization()
#attemptOptimization()

