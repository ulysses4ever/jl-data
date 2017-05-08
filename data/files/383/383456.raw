using ODE
#using Sundials
using PyPlot
using DataFrames

function eqns(t,y,PTframe)
	ydot = Float64[]
	#if(mod(t,.05)==0)
		@show t
	#end
	cnor =y[1]
	cach = y[2]
	n1 = y[3]
	n2 = y[4]
	pbar =y[5]
	n = n1+n2+N

	if(cnor<0)
		cnor =0.0
	end

	if(cach<0)
		cach = 0.0
	end

	if(cach >10)
		cach = 10.0
	end

	if(cnor >10)
		cnor = 10.0
	end

	fpar =calculatefpar(n)
	fsym =calculatefsym(n,t,fpar)	

	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach
	push!(ydot, dcnordt)
	push!(ydot, dcachdt)
	
	currP = lookUpP(t,PTframe)
	@show currP	

	dpbardt = alpha*(currP-pbar)
	dn1dt = k1.*dpbardt.*n.*(M-n)./(M/2)^2-n1./tau1
	dn2dt = k2.*dpbardt.*n.*(M-n)./(M/2)^2-n2./tau2
	
	push!(ydot, dn1dt)
	push!(ydot, dn2dt)
	push!(ydot, dpbardt)

	return ydot
end

function eqnsLowF(t,y,PTframe, lookUpDict)
	ydot = Float64[]
	#if(mod(t,.05)==0)
	#end
	cnor =y[1]
	cach = y[2]
	n1 = y[3]
	n2 = y[4]
	pbar =y[5]
	n = n1+n2+N

#	if(cnor<0)
#		cnor =0.0
#	end

#	if(cach<0)
#		cach = 0.0
#	end

#	if(cach >10)
#		cach = 10.0
#	end

#	if(cnor >10)
#		cnor = 10.0
#	end

	fpar =calculatefpar(n)
	fsym =calculatefsym(n,t,fpar, lookUpDict["HISTORICAL"])	

	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach
	push!(ydot, dcnordt)
	push!(ydot, dcachdt)
	
	currP = lookUpPlowF(t,PTframe)

	dpbardt = alpha*(currP-pbar)
	dn1dt = k1.*dpbardt.*n.*(M-n)./(M/2)^2-n1./tau1
	dn2dt = k2.*dpbardt.*n.*(M-n)./(M/2)^2-n2./tau2
	
	push!(ydot, dn1dt)
	push!(ydot, dn2dt)
	push!(ydot, dpbardt)

	lookUpDict["HISTORICAL"] =storeData(t, n, lookUpDict["HISTORICAL"])
	#@show t, fsym, n1, n2
	return ydot
end

function eqnsSundials(t,y,ydot,PTframe)
	ydot = Float64[]
	@show t
	cnor =y[1]
	cach = y[2]
	n1 = y[3]
	n2 = y[4]
	pbar =y[5]
	n = n1+n2+N

	if(cnor<0)
		cnor =0.0
	end

	if(cach<0)
		cach = 0.0
	end

	if(cach >10)
		cach = 10.0
	end

	if(cnor >10)
		cnor = 10.0
	end

	fpar =calculatefpar(n)
	fsym =calculatefsym(n,t,fpar)	

	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach
	push!(ydot, dcnordt)
	push!(ydot, dcachdt)
	
	currP = lookUpP(t,PTframe)	

	dpbardt = alpha*(currP-pbar)
	dn1dt = k1.*dpbardt.*n.*(M-n)./(M/2)^2-n1./tau1
	dn2dt = k2.*dpbardt.*n.*(M-n)./(M/2)^2-n2./tau2
	
	push!(ydot, dn1dt)
	push!(ydot, dn2dt)
	push!(ydot, dpbardt)

	return ydot
end

function calculatefpar(n)
	fpar = n/M
	return fpar
end

function calculatefsym(n,t,fpar,data)
	fsym = (1-lookUpValue(data,t-tauD)./M)./(1+beta.*fpar)
	if(fsym < 0)
		fsym = 0.0
	end

	return fsym
end

function calculatefsymArr(n,t,fpar,historical_data)
	fsymAll = Float64[]
	#@show sizeof(n), sizeof(t), sizeof(fpar)
	for j in collect(1:size(t,1))
		currt = t[j]
		#@show currt
		fsym = (1-lookUpValue(historical_data, currt-tauD)./M)./(1+beta.*fpar)[1]
		#@show fsym,j
		push!(fsymAll,fsym)
	end
	#@show size(fsymAll)
	return fsymAll
end

function calculateHR2012(cnor, cach)
	hconv = h0*60;
	h = hconv.*(1+Mnor.*cnor-Mach.*cach)
	return h
end

function storeData(time, n, historical_data)
	row = [time, n]
	newdata = [historical_data; transpose(row)]
	return newdata
end

function linInerp(lowerval, upperval, tstart, tend, tdesired)
	val = lowerval +(upperval-lowerval)/(tend-tstart)*(tdesired-tstart)
	return val
end

function findBounds(time, data)
	index=searchsortedfirst(vec(data[:,1]),time, by=abs)
	return index
end

function lookUpValue(data, desiredtime)
	defaultvalue = 0.0
	if(desiredtime<0)
		return defaultvalue
	elseif(desiredtime>data[1,end]) #if we somehow get too far ahead in time, use last value
		return data[2,end]
	end
	upperindex = findBounds(desiredtime,data)
	if(upperindex ==1)
		lowerindex = 1
	else
		lowerindex = upperindex -1
	end
	return linInerp(data[lowerindex,2], data[upperindex,2], data[lowerindex,1], data[upperindex,1], desiredtime)
end



function lookUpP(t,PTframe)
	ff = 1.0/125.0
	currP = PTframe[PTframe[:_Elapsed_time_].==t, :_ABP_]

	if(length(currP)==0)
		lowerlim = t-ff
		upperlim = t+ff
		tester= PTframe[((PTframe[:, :_Elapsed_time_].<upperlim)& (PTframe[:,:_Elapsed_time_].>lowerlim)),:]
		#@show tester
		while(size(tester,1)==0)
			#@show currP
			#println("In loop")
			ff = ff+.05
			lowerlim = t-ff
			upperlim = t+ff
			tester = PTframe[((PTframe[:, :_Elapsed_time_].<=upperlim)& (PTframe[:,:_Elapsed_time_].>=lowerlim)),:]
		end
		currP = PTframe[((PTframe[:, :_Elapsed_time_].<upperlim)& (PTframe[:,:_Elapsed_time_].>lowerlim)),:][:_ABP_][1]
	else
		currP = PTframe[PTframe[:_Elapsed_time_].==t, :_ABP_][1]
	end
	return currP
end

function lookUpPlowF(t,PTframe)
	ff = 1.0/125.0
	currP = PTframe[PTframe[:_Elapsed_time_].==t, :_ABP_Mean_]

	if(length(currP)==0)
		lowerlim = t-ff
		upperlim = t+ff
		tester= PTframe[((PTframe[:, :_Elapsed_time_].<upperlim)& (PTframe[:,:_Elapsed_time_].>lowerlim)),:]
		#@show tester
		while(size(tester,1)==0)
			#@show currP
			#println("In loop")
			ff = ff+.05
			lowerlim = t-ff
			upperlim = t+ff
			tester = PTframe[((PTframe[:, :_Elapsed_time_].<=upperlim)& (PTframe[:,:_Elapsed_time_].>=lowerlim)),:]
		end
		currP = PTframe[((PTframe[:, :_Elapsed_time_].<upperlim)& (PTframe[:,:_Elapsed_time_].>lowerlim)),:][:_ABP_Mean_][1]
	else
		currP = PTframe[PTframe[:_Elapsed_time_].==t, :_ABP_Mean_][1]
	end
	return currP
end

function calculateMSE(tdata, HRdata, tsim, HRsim)
	#need to map tdata to tsim
	totalError = 0.0;
	indexdata = 1;
	indexsim = 1;
	eps = 1E-6;
	startindex = 1;
	numMatched = 0.0
	
	for timeSim in tsim
		for time in tdata
			if(timeSim==time|| (timeSim <= time+eps && timeSim>=time-eps))
				indexdata = findfirst(tdata,time)
				indexsim = findfirst(tsim,timeSim)

				currError = (HRdata[indexdata]-HRsim[indexsim])^2
				totalError = totalError+currError
				numMatched = numMatched+1;
				continue
			else
				#no exact match found, find one close enough
				##println(string("no match found at t = ", tdata[indexdata]))
				##println(string("tsim is ", timeSim))
			end
		end
	end
	#println(string("matched ", numMatched, " out of ", length(HRdata)))
	MSE = totalError/(numMatched)
	return MSE
end


function plotPrettyHighF(tdata, pdata, HRdata, tsim, HRsim, Psim, savestr)
	figure(figsize=(40,20))
	patientID = savestr[1:search(savestr, 'P')-1]
	selectedTdata = Float64[]
	selectedPdata = Float64[]
	#selectedHRdata = Float64[]
	@show tdata
	for j in collect(1:size(tdata,1))
		if(mod(j,2)==0)
			push!(selectedTdata, tdata[j])
			push!(selectedPdata, pdata[j])
			#push!(selectedHRdata, HRdata[j])
		end
	end
	 PyPlot.hold(true)
	# plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](2,1,1)
	plt[:xticks](fontsize=20)
	plt[:yticks](fontsize=20)
	title(patientID, fontsize = 20)
	plot(tsim, Psim, color=".8", linewidth=.8)
	xlabel("Time, in seconds", fontsize = 20)
	ylabel("Pressure, in mmHg", fontsize = 20)
	plot(selectedTdata, selectedPdata, "kx")
	legend(["Average Pressure, as calculated by model", "Pressure"])

	plt[:subplot](2,1,2)
	plt[:xticks](fontsize=20)
	plt[:yticks](fontsize=20)
	plot(tsim, HRsim, color=".8", linewidth = .8)
	plot(tdata, HRdata, "kx")
	xlabel("Time, in seconds", fontsize = 20)
	ylabel("Heart Rate, in BPM", fontsize = 20)
	legend(["Heart Rate, as predicted by 2012 model", "Heart Rate"])
	savefig(savestr)
	
end

function plotall(t, pbarTS, n1TS, n2TS, nTS, fparTS, fsymTS, CnorTS, CachTS, heartRate,heartRate2012, tdata, savestr)
	figure(figsize=(30,20))
	 PyPlot.hold(true)
	# plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](2,3,1)
	plot(t, pbarTS, "k", linewidth=1)
	xlabel("time")
	ylabel("pressure")

	plt[:subplot](2,3,3)
	 PyPlot.hold(true)
	#@show n1TS
	plot(t, nTS, "k", linewidth=1)
	plot(t, n1TS, "b",linewidth=1)
	plot(t, n2TS,"g",linewidth=1)
	xlabel("time")
	ylabel("firing rate")
	legend(["n", "n1", "n2"])
	axis([t[1], tdata[end], -10, 150])

	plt[:subplot](2,3,4)
	#@show fsymTS
	plot(t, fparTS, "k",linewidth=1)
	plot(t, fsymTS, "r",linewidth=1)
	xlabel("time")
	legend(["fpar", "fsym"])
	axis([t[1], tdata[end], -1,2])

	plt[:subplot](2,3,5)
	plot(t, CnorTS,linewidth=1)
	plot(t, CachTS,linewidth=1)
	xlabel("time")
	ylabel("concentration")
	legend(["Cnor", "Cach"])
	axis([t[1], tdata[end], 0,2])

	plt[:subplot](2,3,6)
	#plot(t, HR,linewidth=1)
	plot(tdata, heartRate, "kx")
	plot(t, heartRate2012, "g")
	xlabel("time")
	ylabel("heart rate")
	axis([t[1], tdata[end], 40, 200])

	savefig(savestr)
	PyPlot.close()
end

function plotPretty(tdata, pdata, HRdata, tsim, HRsim, Psim, savestr)
	figure(figsize=(20,20))
	patientID = savestr[1:search(savestr, 'P')-1]
	
	 PyPlot.hold(true)
	# plt[:tight_layout]() 	 #to prevent plots from overlapping
	 plt[:subplot](2,1,1)
	plt[:xticks](fontsize=20)
	plt[:yticks](fontsize=20)
	title(patientID, fontsize = 20)
	plot(tsim, Psim, "k", linewidth=.9)
	xlabel("Time, in seconds", fontsize = 20)
	ylabel("Pressure, in mmHg", fontsize = 20)
	plot(tdata, pdata, "x",color=".75",  linewidth=.9)
	legend(["Average Pressure, as calculated by model", "Pressure"])

	plt[:subplot](2,1,2)
	plt[:xticks](fontsize=20)
	plt[:yticks](fontsize=20)
	plot(tdata, HRdata, "x",color=".75",  linewidth=.9)
	plot(tsim, HRsim, "k", linewidth = .9)
	xlabel("Time, in seconds", fontsize = 20)
	ylabel("Heart Rate, in BPM", fontsize = 20)
	legend(["Heart Rate", "Heart Rate, as predicted by 2012 model"])
	savefig(savestr)
	
end

function saveDataToFile(tsim, HRsim,filename)
	f = open(filename, "a")
	write(f, string(tsim, "\n"))
	write(f, string(HRsim, "\n"))
	close(f)
end

function calculateHeartRateHigherFdata(data,lowfdata,params,savestr)
	tic()
	Pdata = data[:_ABP_]
	tdata = data[:_Elapsed_time_]

	lowFreqt = Array(lowfdata[:_Elapsed_time_])
	global alpha =1.5
	global beta = 6
	global M = 120
	global k2 = 1.5
	global tauD = 7

	global N = params[1]
	global k1 = params[2]
	global tau1 = params[3]
	global tau2 = params[4]
	global tauach = params[5]
	global taunor = params[6]
	global h0 = params[7]
	global Mnor = params[8]
	global Mach = params[9]

	initialconditions = [(1-N/M)/(1+beta*N/M), N/M,0.0,0.0,100.0]
	fedeqns(lowFreqt,y) = eqns(lowFreqt,y,data)
	tout,res = ODE.ode23s(fedeqns, initialconditions, lowFreqt, reltol = 6E-4, abstol =1E-4, points=:specified)


	Cnor = [a[1] for a in res]
	Cach = [a[2] for a in res]
	n1 = [a[3] for a in res]
	n2 = [a[4] for a in res]
	Pbar = [a[5] for a in res]

#	initialconditions = [(1-N/M)/(1+beta*N/M); N/M;0.0;0.0;90.0]
#	fedeqns(t,y,ydot)= eqnsSundials(t,y,ydot,data)
#	X = Sundials.cvode(fedeqns,initialconditions,lowFreqt, abstol = 1E-10, reltol = 1E-10)
#	Cnor = X[:,1]
#	Cach = X[:,2]
#	n1 = X[:,3]
#	n2 = X[:,4]
#	Pbar = X[:,5]
#	tout = lowFreqt

	@show sizeof(lowFreqt)
	@show sizeof(tout)
	@show sizeof(Cnor)
	n = n1+n2+N
	fpar =  calculatefpar(n)
	fsym = calculatefsymArr(n,tout,fpar)
	h = calculateHR2012(Cnor, Cach)
	@show size(h)
	#plotPrettyHighF(lowfdata[:_Elapsed_time_], Pdata, lowfdata[:_HR_], tout,h,Pbar,string(savestr, ".pdf"))
	plotall(tout, Pbar, n1, n2, n,fpar, fsym,Cnor, Cach,lowfdata[:_HR_], h, lowfdata[:_Elapsed_time_],string(savestr, "allvars.pdf"))
	saveDataToFile(tout,h,string(savestr,".txt"))
	toc()

end

function calculateHeartRatelowerFdata(data,params,savestr)
	tic()
	Pdata = data[:_ABP_Mean_]
	tdata = data[:_Elapsed_time_]
	#@show head(data)

	lowFreqt = Array(data[:_Elapsed_time_])
	global alpha =1.5
	global beta = 6
	global M = 120
	global k2 = 1.5
	global tauD = 7

	global N = params[1]
	global k1 = params[2]
	global tau1 = params[3]
	global tau2 = params[4]
	global tauach = params[5]
	global taunor = params[6]
	global h0 = params[7]
	global Mnor = params[8]
	global Mach = params[9]
	historical_data = zeros(1,2)
	lookUpDict = Dict()
	lookUpDict["HISTORICAL"] = historical_data

	initialconditions = [(1-N/M)/(1+beta*N/M), N/M,0.0,0.0,115.0]
	fedeqns(lowFreqt,y) = eqnsLowF(lowFreqt,y,data, lookUpDict)
	tout,res = ODE.ode23s(fedeqns, initialconditions, lowFreqt,reltol = 6E-4, abstol =1E-4, points=:specified)


	Cnor = [a[1] for a in res]
	Cach = [a[2] for a in res]
	n1 = [a[3] for a in res]
	n2 = n1 = [a[4] for a in res]
	Pbar = [a[5] for a in res]

#	initialconditions = [(1-N/M)/(1+beta*N/M); N/M;0.0;0.0;90.0]
#	fedeqns(t,y,ydot)= eqnsSundials(t,y,ydot,data)
#	X = Sundials.cvode(fedeqns,initialconditions,lowFreqt, abstol = 1E-10, reltol = 1E-10)
#	Cnor = X[:,1]
#	Cach = X[:,2]
#	n1 = X[:,3]
#	n2 = X[:,4]
#	Pbar = X[:,5]
#	tout = lowFreqt

	#n = n1+n2+N
	#fpar =  calculatefpar(n)
	#historical_data = hcat(tout,n)
	#fsym = calculatefsymArr(n,lowFreqt,fpar,historical_data)
	h = calculateHR2012(Cnor, Cach)
#	plotPretty(tdata, Pdata, data[:_HR_], tout,h,Pbar,string(savestr, ".pdf"))
#	plotall(tout, Pbar, n1, n2, n,fpar, fsym,Cnor, Cach,data[:_HR_], h, data[:_Elapsed_time_],string(savestr, "allvars.pdf"))
#	saveDataToFile(tout,h,string(savestr,".txt"))
	MSE=calculateMSE(tdata, data[:_HR_], tout, h)
	toc()
	return MSE


end
