using DataFrames
using Optim
include("OlufsenModel2011calcHRtweaked.jl")

function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable("tempoutputP.csv", df)
	dfnew = readtable("tempoutputP.csv", separator=',')
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
	outputdir = "moretesting/forcepositivity/withPertabationToInitals/8/"
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	allpatients = readdir(inputdir)
	touch(string(outputdir, "usefuldatatolAll1E-4only2steps.txt"))
	touch(string(outputdir, "paramstolAll1E-4only2steps.txt"))
	totalMSE = 0.0
	usefulpatients = 0.0

	#force positivity on all parameters
	lowerbound = 1E-9
	for j in range(1,length(params))
		if(params[j])<0
			params[j] = lowerbound
		end
	end

	@show params
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		#println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
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

			f = open(string(outputdir,"usefuldatatolAll1E-4only2steps.txt"), "a")
			f = write(f, string(patient, ",", MSE, "\n"))
			close(f)
		end
	end
	toc()
	overallMSE = totalMSE/usefulpatients
	g = open(string(outputdir, "paramstolAll1E-4only2steps.txt"), "a")
	write(g, string(params, ",", overallMSE, "\n"))
	close(g)
	return overallMSE
end

function attemptOptimization()
	paramsinit = [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
#	params0 = Float64[]
#	for j in range(1,length(paramsinit))
#		push!(params0, paramsinit[j]+(.5-rand()))
#	end
#	params0 = [74.87675930767426,2.2473996192451686,1.083759147077279,250.506285718555,1.0610692098865953,1.3831601151638702,2.3486187679107786,0.7969901288142013,0.6615823072219913]	
#	params0 = [73.97276005951569,5.958365667504933,5.346906561949464,251.73793608560624,1.7574123573345104,1.1797161495402193,1.9007309168917983,0.11276091927165068,0.44820037756111797]
#	params0= [58.51344235220117,24.54429350495017,2.5695133704288375,234.0873230142152,11.380548200282782,0.5032129710525912,1.4748645050800118,0.13599746954042266,0.08064310638415392]
#	params0 =[58.64918655416411,24.680037706913115,2.7052575723917878,234.2230672161781,11.516292402245728,0.6389571730155421,1.4866845278414689,0.12146188603591107,0.08527966755922906]
#	params0 =[58.95436028413554,24.985211436884537,3.0104313023632123,234.52824094614948,10.599243909994925,0.9441309029869671,1.47969962724679,0.13424103469440934,0.08681887067812175]
#	params0 = [66.97011052672144,25.375812194759106,2.4684457508447943,232.34414013055545,6.9572267146137605,0.13706746470723896,1.4759098047782966,0.18872861746230712,0.07667871794503917]
	params0 = [66.97011052672144,25.375812194759106,3.4684457508447943,232.34414013055545,6.9572267146137605,0.13706746470723896,1.4759098047782966,0.18872861746230712,0.07667871794503917]
	res = optimize(calculatetotalMSE, params0,method = Optim.NelderMead(), show_trace = true, ftol = 1E-3)
	@show res
	return res
end
attemptOptimization()


