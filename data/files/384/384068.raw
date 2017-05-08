using DataFrames
require("/home/rachel/Documents/optimization/sensitivityanalysis/OlufsenModel2011calcHRSensitivites.jl")

@everywhere function processNumericalData(filename)
	df=readtable(filename, separator=',',nastrings=["-"])
	units = df[1,:]
	deleterows!(df,1) #remove the row that had units
	writetable(string("tempoutputSF", myid(), ".csv"), df)
	dfnew = readtable(string("tempoutputSF", myid(), ".csv"), separator=',')
	return dfnew, units
end

@everywhere function cleandata(data)
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

@everywhere function calculateS0(DFhr,DFdxdp,changableparams)
	tic()
	S0 = Float64[]
	@show DFhr
	@show DFdxdp
	for j in range(1, length(changableparams))
		sum = 0.0
		for i in range(1, size(DFdxdp,1))
			@show 1/DFhr[i,1][1]
			@show DFdxdp[i,j][1]
			currTerm = (1/DFhr[i,1][1]*DFdxdp[i,j][1])^2
			sum = sum+currTerm
		end
		itermediateterm = sqrt(sum)
		S0j = changableparams[j]*itermediateterm
		push!(S0, S0j)
	end
	toc()
	return S0
end

function doSensitivities()
	tic()
	 N = 75.0
        M = 120.0
	 beta = 6
	params= [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	outputdir = "sensitivityanalysis/usingBestParamsAsOfMay19FroS0Tol1E-8h1E-8/"
	allpatients = readdir(inputdir)
	for patient in allpatients
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
		data, units= processNumericalData(string(inputdir, patient))
		colnames = (names(data))
		if(!in(:_Elapsed_time_, colnames))
			continue
		end
		sort!(data, cols = [order(:_Elapsed_time_)])
		
		if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			println("has complete data")
			data = cleandata(data)
			rowcounter = 0
			n1 = -1.0
			n2 = -1.0
			pbar = -1.0
			cnor = -1.0
			cach = -1.0
			phi = -1.0
			for row in eachrow(data)
				Pdata = convert(Array ,[row[:_ABP_Mean_], row[:_ABP_Mean_]+10^15*eps()])
				#@show Pdata
				tdata = convert(Array, [row[:_Elapsed_time_],row[:_Elapsed_time_]+10^15*eps()])
				currt = row[:_Elapsed_time_]
				if(rowcounter<2)
					nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0];
					bfprev = [0.0,0.0,90.0];

				else 
					nsprev = [n1, n2, pbar]
					bfprev = [cnor, cach, phi]	
				end
				
				#	hr,cnor,cach,n,n1,n2,fpar,fsym,pbar,phi 
				res= calculateModel(Pdata, tdata,nsprev, bfprev,params)
				#@show res
				if(contains(string(typeof(res)), "Void"))
					continue
				end
				hr = res[1]
				cnor = res[2]
				cach = res[3]
				n = res[4]
				n1 = res[5]
				n2 = res[6]
				fpar = res[7]
				fsym = res[8]
				pbar = res[9]
				phi = res[10]
				S= calculateSensitivities(cnor, cach,fsym, fpar,n,currt,params,Pdata,tdata,nsprev,bfprev)
				#@show S
				f = open(string(outputdir, "SensitivitiesForPatient", patient, ".csv"), "a")
				write(f, string(currt, ",", S, "\n"))
				close(f)
				rowcounter = rowcounter+1

			end
		end
	end

	toc()
end

function doSensitivitiesMakeDFs()
	 N = 75.0
        M = 120.0
	 beta = 6
	#params= [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	#params = [77.21810611260562,14.0659798715,2.3595665995,252.9553108258,0.4708140794,9.7720706413,1.7454283859,0.1612547652,0.30946585943989047]
	params =[107.33612908104033,41.138842557517954,14.062116217939991,202.92519160829795,2.941876046317941e-5,8.15596008945017,1.4743606995666585,0.1654851281383664,0.05218327316554491]
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/usingBestParamsJun20/"
	touch(string(outputdir, "AllS0.txt"))
	allpatients = readdir(inputdir)
	for patient in allpatients
		tic()
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
		data, units= processNumericalData(string(inputdir, patient))
		colnames = (names(data))
		if(!in(:_Elapsed_time_, colnames))
			continue
		end
		sort!(data, cols = [order(:_Elapsed_time_)])

		
		if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
			data = cleandata(data)
			if(size(data,1)==0)
				continue
			end
			println("has complete data")
			rowcounter = 0
			n1 = -1.0
			n2 = -1.0
			pbar = -1.0
			cnor = -1.0
			cach = -1.0
			phi = -1.0
			DFdxdp = DataFrame(dhdN = Float64[], dhdk1=Float64[], dhdtau1 = Float64[], dhdtau2 = Float64[], dhdtauach = Float64[], dhdtaunor = Float64[], dhdh0 = Float64[], dhdmnor = Float64[], dhdmach = Float64[])
			DFhr = DataFrame(HR = Float64[])
			patientOfInterest = true
			for row in eachrow(data)
				Pdata = convert(Array ,[row[:_ABP_Mean_], row[:_ABP_Mean_]+10^15*eps()])
				tdata = convert(Array, [row[:_Elapsed_time_],row[:_Elapsed_time_]+10^15*eps()])
				currt = row[:_Elapsed_time_]
				@show currt
				if(rowcounter<2)
					nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0];
					bfprev = [0.0,0.0,90.0];

				else 
					nsprev = [n1, n2, pbar]
					bfprev = [cnor, cach, phi]	
				end
				
				#	hr,cnor,cach,n,n1,n2,fpar,fsym,pbar,phi 
				res= calculateModel(Pdata, tdata,nsprev, bfprev,params)
				if(contains(string(typeof(res)), "Void"))
					patientOfInterest = false
					continue
				end
				hr = res[1]
				cnor = res[2]
				cach = res[3]
				n = res[4]
				n1 = res[5]
				n2 = res[6]
				fpar = res[7]
				fsym = res[8]
				pbar = res[9]
				phi = res[10]
				S= calculateSensitivitesUsingCDForAll(cnor, cach,fsym, fpar,n,currt,params,Pdata,tdata,nsprev,bfprev)
				push!(DFdxdp, S)
				push!(DFhr, hr)
				f = open(string(outputdir, "SensitivitiesForPatient", patient, ".csv"), "a")
				write(f, string(currt, ",", S, "\n"))
				close(f)
				rowcounter = rowcounter+1

			end

			if(patientOfInterest==true)
				S0=calculateS0(DFhr,DFdxdp,params)
				g = open(string(outputdir, "AllS0.txt"), "a")
				write(g, string(patient, ",", S0, "\n"))
				close(g)
			end
			toc()
		end
	end
end

function doSensitivitiesMakeDFs_parallel()
	 N = 75.0
        M = 120.0
	 beta = 6
	params= [75,1.5,.5,250, .5, .5, 1.67,.96, .7]
	#params = [77.21810611260562,14.0659798715,2.3595665995,252.9553108258,0.4708140794,9.7720706413,1.7454283859,0.1612547652,0.30946585943989047]
	params =[107.33612908104033,41.138842557517954,14.062116217939991,202.92519160829795,2.941876046317941e-5,8.15596008945017,1.4743606995666585,0.1654851281383664,0.05218327316554491]
	inputdir = "/home/rachel/Documents/modelingHR/LinkedRecordsTimeData10min/"
	#outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/usingBestParamsJun20/"
	outputdir = "/home/rachel/Documents/optimization/sensitivityanalysis/usingOriginalParamsJun23/"
	touch(string(outputdir, "AllS0.txt"))
	cluster1path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/cluster2subjectIDs"

	allpatients = AbstractString[]
	f = open(cluster1path)

	for ln in eachline(f)
		if(length(ln)>1)
			push!(allpatients, strip(ln))
		end
	end
	close(f)

	f = open(cluster2path)

	for ln in eachline(f)
		if(length(ln)>1)
			push!(allpatients, strip(ln))
		end
	end
	close(f)

	allres= @parallel (vcat) for patient in allpatients
		tic()
		numericPatientID = patient[2:6]
		date = patient[7:end-7]
		println(string("processing patient", patient))
		savestr = string(outputdir, "Id = ", patient,"usingfewersteps", ".png")
		data, units= processNumericalData(string(inputdir, patient))
		colnames = (names(data))
		if(!in(:_Elapsed_time_, colnames))
			#continue
		else
			sort!(data, cols = [order(:_Elapsed_time_)])
			DFdxdp = DataFrame(dhdN = Float64[], dhdk1=Float64[], dhdtau1 = Float64[], dhdtau2 = Float64[], dhdtauach = Float64[], dhdtaunor = Float64[], dhdh0 = Float64[], dhdmnor = Float64[], dhdmach = Float64[])
			DFhr = DataFrame(HR = Float64[])
		
			if(in(:_ABP_Mean_, colnames) && in(:_HR_, colnames)&& (length(data[:_Elapsed_time_])>2))
				data = cleandata(data)
				if(size(data,1)==0)
					#continue

				else
					println("has complete data")
					rowcounter = 0
					n1 = -1.0
					n2 = -1.0   
					pbar = -1.0
					cnor = -1.0
					cach = -1.0
					phi = -1.0
					patientOfInterest = true
					for row in eachrow(data)
						Pdata = convert(Array ,[row[:_ABP_Mean_], row[:_ABP_Mean_]+10^15*eps()])
						tdata = convert(Array, [row[:_Elapsed_time_],row[:_Elapsed_time_]+10^15*eps()])
						currt = row[:_Elapsed_time_]
						@show currt
						if(rowcounter<2)
							nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0];
							bfprev = [0.0,0.0,90.0];

						else 
							nsprev = [n1, n2, pbar]
							bfprev = [cnor, cach, phi]	
						end
				
						#	hr,cnor,cach,n,n1,n2,fpar,fsym,pbar,phi 
						res= calculateModel(Pdata, tdata,nsprev, bfprev,params)
						if(contains(string(typeof(res)), "Void"))
							patientOfInterest = false
						else 
							patientOfInterest= true
							hr = res[1]
							cnor = res[2]
							cach = res[3]
							n = res[4]
							n1 = res[5]
							n2 = res[6]
							fpar = res[7]
							fsym = res[8]
							pbar = res[9]
							phi = res[10]
							S= calculateSensitivitesUsingCDForAll(cnor, cach,fsym, fpar,n,currt,params,Pdata,tdata,nsprev,bfprev)
							push!(DFdxdp, S)
							push!(DFhr, hr)
							f = open(string(outputdir,"SensitivitiesForPatient", patient, ".csv"), "a")
							write(f, string(currt, ",", S, "\n"))
							close(f)
							rowcounter = rowcounter+1
						end
	
				
				end

			if(patientOfInterest==true)
				S0=calculateS0(DFhr,DFdxdp,params)
				g = open(string(outputdir, myid(),"AllS0.txt"), "a")
				write(g, string(patient, ",", S0, "\n"))
				close(g)
			end
				end

		end
		together = hcat(DFhr, DFdxdp)
		#@show together
		together
		end
		toc()
		
	end
	allres
end

doSensitivitiesMakeDFs_parallel()
