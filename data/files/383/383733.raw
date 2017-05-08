using ODE
using DataFrames
using PyPlot

function nervous_system(t,y,FTframe)
	ff = .5
	cnor = y[1]
	cach = y[2]
	phi = y[3]
	#force positivity
	@show t, cnor, cach
	if(cnor < 0)
		cnor = 0.0
	end

	if(cach<0)
		cach = 0.0
	end


	@show t, cnor, cach
	#find correct fsyms and fpars
	tester = FTframe[FTframe[:time].==t, :]
	if(size(tester,1)==0)
		#println("Exact match not found")
		#@show t, currP
		lowerlim = t-ff
		upperlim = t+ff
		tester= FTframe[((FTframe[:, :time].<upperlim)& (FTframe[:,:time].>lowerlim)),:]
		#@show tester
		while(size(tester,1)==0)
			#@show currP
			#println("In loop")
			ff = ff+.05
			lowerlim = t-ff
			upperlim = t+ff
			tester = FTframe[((FTframe[:, :time].<=upperlim)& (FTframe[:,:time].>=lowerlim)),:]
#			@show lowerlim, upperlim, t
#			@show tester
		end
		fsym = FTframe[((FTframe[:, :time].<upperlim)& (FTframe[:,:time].>lowerlim)),:][:Fsym][1]
		fpar = FTframe[((FTframe[:, :time].<upperlim)& (FTframe[:,:time].>lowerlim)),:][:Fpar][1]

	else
		fsym = FTframe[FTframe[:time].==t, :Fsym][1]
		fpar = FTframe[FTframe[:time].==t, :Fpar][1]
	end

	dcnordt = (fsym-cnor)/taunor
	dcachdt =(fpar-cach)/tauach
	dphidt = 1/h0*(1+Mnor*cnor-Mach*cach)
	if(cnor < 0)
		dcnordt = 0.0
	end

	if(cach<0)
		println("found less than zero")
		dcachdt = 0.0
	end

	ydot = [dcnordt, dcachdt, dphidt]
	return ydot
end

function baroreflex(t,y,PTframe)
	#@show head(PTframe)
	ff = .5
	#@show PTframe[PTframe[:time].==t, :Press]
	#@show (names(PTframe))
	currP = PTframe[PTframe[:time].==t, :Press]

	if(length(currP)==0)
		#println("Exact match not found")
		#@show t, currP
		lowerlim = t-ff
		upperlim = t+ff
		tester= PTframe[((PTframe[:, :time].<upperlim)& (PTframe[:,:time].>lowerlim)),:]
		#@show tester
		while(size(tester,1)==0)
			#@show currP
			#println("In loop")
			ff = ff+.05
			lowerlim = t-ff
			upperlim = t+ff
			tester = PTframe[((PTframe[:, :time].<=upperlim)& (PTframe[:,:time].>=lowerlim)),:]
#			@show lowerlim, upperlim, t
#			@show tester
		end
		currP = PTframe[((PTframe[:, :time].<upperlim)& (PTframe[:,:time].>lowerlim)),:][:Press][1]
	else
		currP = PTframe[PTframe[:time].==t, :Press][1]
	end

	#@show currP
	n1=y[1]
	n2=y[2]
	pbar=y[3]

	if(n1<0)
		n1 = 0.0
	end

	if(n2<0)
		n2 = 0.0
	end

	dpbardt = alpha*(currP-pbar)
	n = n1+n2+N

	dn1dt = k1.*dpbardt.*n.*(M-n)./(M/2)^2-n1./tau1
	dn2dt = k2.*dpbardt.*n.*(M-n)./(M/2)^2-n2./tau2

	if(n1<0)
		dn1dt = 0.0
	end

	if(n2<0)
		dn2dt = 0.0
	end
	
	ydot = [dn1dt, dn2dt, dpbardt]
	return ydot
end

function calculatefpar(n)
	M = 120
	fpar = n/M
	return fpar
end

function calculatefsym(n,t,fpar)
	@show size(n), size(t), size(fpar)
	fsym = (1-n.*(t-tauD)/M)./(1+beta.*fpar)
	for j in collect(1:size(fsym,1))
		if(fsym[j] < 0)
			fsym[j] = 0.0
		end
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
	hconv = h0*60;
	h = hconv*(1+Mnor*cnor-Mach*cach)
	return h
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


function calculateSensitivitesUsingCDForAll(cnor, cach,fsym, fpar,n,t,params,PTframe,nsprev,bfprev)
	S = Float64[]
	delta = 1E-8;
	num_params = 9
	for j in collect(1:num_params)
		dhdthetaj = calculateCenteredFD(PTframe, params, nsprev, bfprev,delta, j)
		push!(S,dhdthetaj)
	end
	return S
end


function calculateCenteredFD(PTframe, params, nsprev, bfprev,delta, index)
	tic()
	h = delta*params[index]
	paramsforward = params+h/2.0*squeeze(eye(index,length(params))[index,:],1)
	paramsbackwards = params-h/2.0*squeeze(eye(index,length(params))[index,:],1)
	fForward = calculateModel(PTframe,nsprev, bfprev,paramsforward)[1]
	fBackwards = calculateModel(PTframe,nsprev, bfprev,paramsbackwards)[1]

	cd = (fForward-fBackwards)/h
	toc()
	return cd
end

function calculateModel(PTframe, nsprev, bfprev,params)
	println("in calculate model")
	t = Float64[]
	P = Float64[]
	tstepavg = 0.0
#	PTframe = DataFrame(Press = Float64[], time =Float64[])
#	PTframe[Press] = @data(Pdata)
#	PTframe[time] = @data(tdata)

	#@show head(PTframe)
	if(size(PTframe,1)<5)
		println("too small")
		return
	end

	colnames = (names(PTframe))
	@show colnames
	if(!in(:Press, colnames))
		println("missing name")
		return
	end
	tdata = convert(Array, PTframe[:time])

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
	#currn = 0

	#for time in t

		bf(tdata,y)= baroreflex(tdata,y,PTframe)
		println("Made it here")
		#@show tdata
		tout, res = ODE.ode78(bf, bfprev,tdata,abstol = 1E-8, reltol = 1E-8,points=:specified)
		#@show tout
		#@show size(tout), size(PTframe), size(res)

		n1TS = [a[1] for a in res]
		n2TS = [a[2] for a in res]
		pbarTS = [a[3] for a in res]

#		currn= y1[end]+y2[end]+N
#		push!(nTS, currn)
		nTS = n1TS+n2TS + N
		#@show size(nTS)
#		fpar = calculatefpar(currn)
		fpar = calculatefpar(nTS)
		#@show size(fpar)
		fsym = calculatefsym(nTS,tdata,fpar)
		FTframe = DataFrame(time=tdata, Fsym = fsym, Fpar = fpar)

		ns(tdata, y)=nervous_system(tdata, y, FTframe)
		tout, nsRes = ODE.ode78(ns, nsprev, tdata, abstol = 1E-8, reltol = 1E-8,points=:specified)
		CnorTS = [a[1] for a in nsRes]
		CachTS = [a[2] for a in nsRes]
		phiTS = [a[3] for a in nsRes]

		heartRate2012 =calculateHR2012(CnorTS, CachTS)
		#@show heartRate2012
	
		counter = counter+1

	println("got here")
	@show size(heartRate2012), size(CnorTS), size(CachTS), size(nTS), size(n1TS), size(n2TS), size(fpar), size(fsym), size(pbarTS), size(phiTS)
	figure()
	plot(tdata, heartRate2012)

	return hcat(heartRate2012, CnorTS, CachTS, nTS, n1TS, n2TS, fpar, fsym, pbarTS, phiTS)
		
end
