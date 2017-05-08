using ODE
using PyPlot
using DataFrames

function nervous_system(t,y,fsym,fpar)
#	#H0 = 1.67 #beats/sec
#	H0=2.17 #beats/sec, corresponds to resting HR of 80 bpm
#	#H0 =100.0
#	taunor = .5
#	tauach = .5
#	Mach = .7
#	Mnor = .96
#	#from third line in 2012 paper
##	taunor =.558
##	tauach= .509
##	Mach = .699
##	Mnor =.963
#	
	cnor = y[1]
	cach = y[2]
	phi = y[3]
	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach
	dphidt = 1/h0*(1+Mnor*cnor-Mach*cach)
	ydot = [dcnordt, dcachdt, dphidt]
	return ydot
end

function baroreflex(t,y,currP)
	##println("got here")
	n1=y[1]
	n2=y[2]
	pbar=y[3]
	#constants, as givien by Olufsen 2011 in healthy young
#	k1 = 1.5
#	k2 = 1.5
#	tau1 = .5
#	tau2 = 250
#	#from third line in 2012 paper
##	k1 =.945
##	k2 = 1.5
##	tau1 = .896
##	tau2 = 229
#	

	dpbardt = alpha*(currP-pbar)
	n = n1+n2+N

	dn1dt = k1.*dpbardt.*n.*(M-n)./(M/2)^2-n1./tau1
	dn2dt = k2.*dpbardt.*n.*(M-n)./(M/2)^2-n2./tau2

	
	ydot = [dn1dt, dn2dt, dpbardt]
	return ydot
end

function calculatefpar(n)
	M = 120
	fpar = n/M
	return fpar
end

function calculatefsym(n,t,fpar)
#	M = 120.0#*10000
#	tauD = 7
#	beta = 6

	fsym = (1-n*(t-tauD)/M)/(1+beta*fpar)
	if(fsym < 0)
		fsym = 0.0
	end

	return fsym
end

function calculatefsymStretched(n,t,fpar, stretch)
	M = 120.*stretch
	tauD = 7
	beta = 6

	fsym = (1-n*(t-tauD)/M)/(1+beta*fpar)
	if(fsym < 0)
		fsym = 0.0
	end

	return fsym
end

function linearInterp(lowerVal, upperVal, tstart, tend,step)
	val = lowerVal + (upperVal-lowerVal)/(tend-tstart)*step
	return val
end

function calculateHR(phiTS, times)
	#HR = fill(100.0, length(phiTS), 1) #originally, fill with basic heart rate
	HR = Float64[]
	tprev = 0.0
	currHR = 100
	buffer = .01
	for j = 1:length(phiTS)
		currPhi = phiTS[j]
		##println(currPhi)
		if(currPhi>1-tolHR && currPhi<1+tolHR && tprev+buffer<times[j])
			##println("found a beat!")
			##println(times[j])
			currHR = 1/(times[j]-tprev)*60
			tprev = times[j]
		end
		push!(HR, currHR)
	end

	return HR
end

function calculateHR2012(cnor, cach)
#	h0 = 2.17*60;
#	Mach = .7
#	Mnor = .96
	hconv = h0*60;
	h = hconv*(1+Mnor*cnor-Mach*cach)
	return h
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

function calculateSensitivities(cnor, cach,fsym, fpar,n,t,params,Pdata,tdata,nsprev,bfprev)
	S = Float64[]
	delta = 1E-8;
	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach

	dhdmnor = h0*cnor
	dhdmach =-h0*cach
	dhdh0= 1+Mnor*cnor-Mach*cach
	#dhdtaunor = -h0*(Mnor*dcnordt+Mnor/taunor*(fsym-cnor))
	#dhdtauach = h0*(Mach*dcachdt-Mach/tauach*(fpar-cach))

	paramsForN = params + delta*params[2]*squeeze(eye(2,length(params))[1,:],1)
	hforN = delta*params[1]
	paramsFork1 = params + delta*params[2]*squeeze(eye(2,length(params))[2,:],1)
	hfork1 = delta*params[2]
	paramsFortau1 = params + delta*params[3]*squeeze(eye(3,length(params))[3,:],1)
	hfortau1 = delta*params[3]
	paramsFortau2 = params + delta*params[4]*squeeze(eye(4,length(params))[4,:],1)
	hfortau2 = delta*params[4]
	paramsFortaunor = params+delta*params[5]*squeeze(eye(5,length(params))[5,:],1)
	hfortaunor = delta*params[5]
	paramsFortauach = params+delta*params[6]*squeeze(eye(6,length(params))[6,:],1)
	hfortauach = delta*params[6]
	
	
	dhdN = calculateFiniteDiff(Pdata,tdata,params, paramsForN,nsprev,bfprev,hforN)
	dhdk1 = calculateFiniteDiff(Pdata,tdata,params, paramsFork1,nsprev,bfprev,hfork1)
	dhdtau1 = calculateFiniteDiff(Pdata,tdata,params, paramsFortau1,nsprev,bfprev,hfortau1)
	dhdtau2 = calculateFiniteDiff(Pdata,tdata,params, paramsFortau2,nsprev,bfprev,hfortau2)
	dhdtauach = calculateFiniteDiff(Pdata,tdata,params, paramsFortauach,nsprev,bfprev,hfortauach)
	dhdtaunor = calculateFiniteDiff(Pdata,tdata,params, paramsFortaunor,nsprev,bfprev,hfortaunor)

	push!(S,dhdN)
	push!(S,dhdk1)
	push!(S,dhdtau1)
	push!(S,dhdtau2)
	push!(S,dhdtauach)
	push!(S,dhdtaunor)
	push!(S,dhdh0)
	push!(S,dhdmnor)
	push!(S,dhdmach)
	return S
end

function calculateSensitivitesUsingCDForAll(cnor, cach,fsym, fpar,n,t,params,Pdata,tdata,nsprev,bfprev)
	S = Float64[]
	delta = 1E-8;
	num_params = 9
	for j in collect(1:num_params)
		dhdthetaj = calculateCenteredFD(Pdata, tdata, params, nsprev, bfprev,delta, j)
		push!(S,dhdthetaj)
	end
	return S
end

function calculateSensitivitesUsingCDForSetParams(cnor, cach,fsym, fpar,n,t,params,Pdata,tdata,nsprev,bfprev)
	S = Float64[]
	num_params = 5
	startindex = 10
	delta = 1E-8;
	for j in collect(startindex:startindex+num_params-1)
		dhdthetaj = calculateCenteredFDSetParams(Pdata, tdata, params, nsprev, bfprev,delta, j)
		#@show S
		push!(S,dhdthetaj)
	end
	return S
end

function calculateFiniteDiff(Pdata, tdata, params0,params1,nsprev, bfprev,h)
	
	fd = (calculateModel(Pdata,tdata,nsprev, bfprev,params0)[1]-calculateModel(Pdata,tdata,nsprev, bfprev,params1)[1])/h
	return fd
end

function calculateCenteredFD(Pdata, tdata, params, nsprev, bfprev,delta, index)
	#tic()
	h = delta*params[index]
	paramsforward = params+h/2.0*squeeze(eye(index,length(params))[index,:],1)
	paramsbackwards = params-h/2.0*squeeze(eye(index,length(params))[index,:],1)
	fForward = calculateModel(Pdata,tdata,nsprev, bfprev,paramsforward)[1]
	fBackwards = calculateModel(Pdata,tdata,nsprev, bfprev,paramsbackwards)[1]

	cd = (fForward-fBackwards)/h
	#toc()
	#@show paramsforward, paramsbackwards, fForward, fBackwards, cd
	return cd
end

function calculateCenteredFDSetParams(Pdata, tdata, params, nsprev, bfprev,delta, index)
	tic()
	h = delta*params[index]
	paramsforward = params+h/2.0*squeeze(eye(index,length(params))[index,:],1)
	paramsbackwards = params-h/2.0*squeeze(eye(index,length(params))[index,:],1)
	fForward = calculateModelPassInMore(Pdata,tdata,nsprev, bfprev,paramsforward)[1]
	fBackwards = calculateModelPassInMore(Pdata,tdata,nsprev, bfprev,paramsbackwards)[1]

	cd = (fForward-fBackwards)/h
	toc()
	#@show paramsforward, paramsbackwards, fForward, fBackwards, cd
	return cd
end


function calculateModel(Pdata,tdata,nsprev, bfprev,params)
		
	t = Float64[]
	P = Float64[]

	tstepavg = 0.0

	#@show length(tdata)
	#@show length(Pdata)
	numIntervals = 2.0
	hasData = Int[] #to keep track of gaps in the data. 1 means data present, 0 means gap
	for j = 1:length(tdata)-1
		tstep = tdata[j+1]-tdata[j];
		dataPresent = 1
		if(tstep>5)
			#println(string("found gap in data at between t = "), tdata[j+1], " and t = ", tdata[j])
			dataPresent = 0
			numIntervals = tstep*2.0
		else
			dataPresent = 1
			numIntervals = 2.0
		end
		for k = 1:numIntervals
			step = tstep/numIntervals*k
			currT = tdata[j]+step
			currP = linearInterp(Pdata[j], Pdata[j+1], tdata[j], tdata[j+1],step)
			if(!in(currT,t)&& !in(currT+eps(), t) && !in(currT-eps(), t))
				push!(t, currT)
				push!(P, currP)
				push!(hasData, dataPresent)
			end
		end
	end
	tstep = 1.0/numIntervals
	counter = 1
	#define parametrse to optimize
	#both alpha,beta, M,k2 , taud are set, not estimated
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
	


	#should play with these
	global tol = .1
	global tolHR = .15
	treset =0.0 #for heartbeat logic
	#nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0]
	#bfprev = [0.0,0.0,90.0]

	n1TS = Float64[]
	n2TS =Float64[]
	nTS = Float64[]

	pbarTS = Float64[]

	CnorTS = Float64[]
	CachTS = Float64[]
	phiTS = Float64[]

	fparTS = Float64[]
	fsymTS = Float64[]
	beatsTS = Float64[]
	push!(beatsTS,0)#put in an initial value
	heartRate = Float64[]
	heartRate2012= Float64[]
	currHR = 100;
	currn = 0

	for time in t
		if(mod(counter,10000)==0)
			#println(string("at time "), time)
		end
		currP = P[counter]
		bf(tspan,y)= baroreflex(tspan,y,currP)
		tspan = collect(time-5*tstep:tstep/10:time)
		tout, res = ODE.ode78(bf, bfprev,tspan,abstol = 1E-8, reltol = 1E-8)

		y1 = [a[1] for a in res]
		y2 = [a[2] for a in res]
		y3 =[a[3] for a in res]

		push!(n1TS, y1[end])
		push!(n2TS, y2[end])
		push!(pbarTS, y3[end])

		currn= y1[end]+y2[end]+N
		push!(nTS, currn)
		fpar = calculatefpar(currn)
		
		fsym = calculatefsym(currn,time,fpar)
		push!(fparTS, fpar)
		push!(fsymTS, fsym)

		ns(tspan, y)=nervous_system(tspan, y, fsym, fpar)
		tout, nsRes = ODE.ode23(ns, nsprev, tspan, abstol = 1E-8, reltol = 1E-8)
		Cnor = [a[1] for a in nsRes]
		Cach = [a[2] for a in nsRes]
		phi = [a[3] for a in nsRes]

		if(Cnor[end]< 0)
			Cnor[end] = 0.0
		end

		if(Cach[end]<0)
			Cach[end] = 0.0
		end

		push!(CnorTS, Cnor[end])
		push!(CachTS, Cach[end])
		currHeartRate =calculateHR2012(Cnor[end], Cach[end])
		push!(heartRate2012, currHeartRate)
	
		counter = counter+1
		#use previous result as starting point for next integration
		bfprev = [y1[end],y2[end],y3[end]]

		currPhi = phi[end]

		tbuffer = tstep*1.1
		if(counter>2)
		
			if(currPhi-.8>0 && phiTS[counter-2]-.8<0)# && time-tbuffer>treset)
				##println("In this logic")
				#currPhi = 0.0
				treset = time
				push!(beatsTS, time)
				currHR = 1/(time-beatsTS[length(beatsTS)-1])*60
			end
			if(currPhi-1>0 && phiTS[counter-2]-1<0)
				currPhi = 0.0
			end
		end


		push!(phiTS, currPhi)
		push!(heartRate, currHR)
		nsprev = [Cnor[end], Cach[end], currPhi]
	end
#	savestrpretty = string(savestr[1:search(savestr, '.')-1], "Pretty", savestr[search(savestr, '.'):end])
#	plotPretty(tdata, Pdata, data[:_HR_], t, heartRate2012, pbarTS, savestrpretty)
#	PyPlot.close()
	return [heartRate2012[end], CnorTS[end], CachTS[end], currn, n1TS[end], n2TS[end], fparTS[end], fsymTS[end], pbarTS[end], phiTS[end]]
		
end

function calculateModelPassInMore(Pdata,tdata,nsprev, bfprev,params)
		
	t = Float64[]
	P = Float64[]

	tstepavg = 0.0

	#@show length(tdata)
	#@show length(Pdata)
	numIntervals = 2.0
	hasData = Int[] #to keep track of gaps in the data. 1 means data present, 0 means gap
	for j = 1:length(tdata)-1
		tstep = tdata[j+1]-tdata[j];
		dataPresent = 1
		if(tstep>5)
			#println(string("found gap in data at between t = "), tdata[j+1], " and t = ", tdata[j])
			dataPresent = 0
			numIntervals = tstep*2.0
		else
			dataPresent = 1
			numIntervals = 2.0
		end
		for k = 1:numIntervals
			step = tstep/numIntervals*k
			currT = tdata[j]+step
			currP = linearInterp(Pdata[j], Pdata[j+1], tdata[j], tdata[j+1],step)
			if(!in(currT,t)&& !in(currT+eps(), t) && !in(currT-eps(), t))
				push!(t, currT)
				push!(P, currP)
				push!(hasData, dataPresent)
			end
		end
	end
	tstep = 1.0/numIntervals
	counter = 1
	#define parametrse to optimize
	#both alpha,beta, M,k2 , taud are set, not estimated
	global alpha =params[10]
	global beta = params[11]
	global M = params[12]
	global k2 = params[13]
	global tauD = params[14]

	global N = params[1]
	global k1 = params[2]
	global tau1 = params[3]
	global tau2 = params[4]
	global tauach = params[5]
	global taunor = params[6]
	global h0 = params[7]
	global Mnor = params[8]
	global Mach = params[9]
	


	#should play with these
	global tol = .1
	global tolHR = .15
	treset =0.0 #for heartbeat logic
	#nsprev = [(1-N/M)/(1+beta*N/M), N/M, 0.0]
	#bfprev = [0.0,0.0,90.0]

	n1TS = Float64[]
	n2TS =Float64[]
	nTS = Float64[]

	pbarTS = Float64[]

	CnorTS = Float64[]
	CachTS = Float64[]
	phiTS = Float64[]

	fparTS = Float64[]
	fsymTS = Float64[]
	beatsTS = Float64[]
	push!(beatsTS,0)#put in an initial value
	heartRate = Float64[]
	heartRate2012= Float64[]
	currHR = 100;
	currn = 0

	for time in t
		if(mod(counter,10000)==0)
			#println(string("at time "), time)
		end
		currP = P[counter]
		bf(tspan,y)= baroreflex(tspan,y,currP)
		tspan = collect(time-5*tstep:tstep/10:time)
		tout, res = ODE.ode78(bf, bfprev,tspan,abstol = 1E-8, reltol = 1E-8)

		y1 = [a[1] for a in res]
		y2 = [a[2] for a in res]
		y3 =[a[3] for a in res]

		push!(n1TS, y1[end])
		push!(n2TS, y2[end])
		push!(pbarTS, y3[end])

		currn= y1[end]+y2[end]+N
		push!(nTS, currn)
		fpar = calculatefpar(currn)
		
		fsym = calculatefsym(currn,time,fpar)
		push!(fparTS, fpar)
		push!(fsymTS, fsym)

		ns(tspan, y)=nervous_system(tspan, y, fsym, fpar)
		tout, nsRes = ODE.ode23(ns, nsprev, tspan, abstol = 1E-8, reltol = 1E-8)
		Cnor = [a[1] for a in nsRes]
		Cach = [a[2] for a in nsRes]
		phi = [a[3] for a in nsRes]

		if(Cnor[end]< 0)
			Cnor[end] = 0.0
		end

		if(Cach[end]<0)
			Cach[end] = 0.0
		end

		push!(CnorTS, Cnor[end])
		push!(CachTS, Cach[end])
		currHeartRate =calculateHR2012(Cnor[end], Cach[end])
		push!(heartRate2012, currHeartRate)
	
		counter = counter+1
		#use previous result as starting point for next integration
		bfprev = [y1[end],y2[end],y3[end]]

		currPhi = phi[end]

		tbuffer = tstep*1.1
		if(counter>2)
		
			if(currPhi-.8>0 && phiTS[counter-2]-.8<0)# && time-tbuffer>treset)
				##println("In this logic")
				#currPhi = 0.0
				treset = time
				push!(beatsTS, time)
				currHR = 1/(time-beatsTS[length(beatsTS)-1])*60
			end
			if(currPhi-1>0 && phiTS[counter-2]-1<0)
				currPhi = 0.0
			end
		end


		push!(phiTS, currPhi)
		push!(heartRate, currHR)
		nsprev = [Cnor[end], Cach[end], currPhi]
	end
#	savestrpretty = string(savestr[1:search(savestr, '.')-1], "Pretty", savestr[search(savestr, '.'):end])
#	plotPretty(tdata, Pdata, data[:_HR_], t, heartRate2012, pbarTS, savestrpretty)
#	PyPlot.close()
	return [heartRate2012[end], CnorTS[end], CachTS[end], currn, n1TS[end], n2TS[end], fparTS[end], fsymTS[end], pbarTS[end], phiTS[end]]
		
end


