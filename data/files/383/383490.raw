function storeData(time, fev, fes, fcs, fsp, fsh, fv, fac,historicaldata)
	row = [time fev fes fcs fsp fsh fv fac]
	newdata = [historicaldata; (row)]
	#row = [time;fev;fes;fcs;fsp;fsh;fv;fac]
#	@show size(historicaldata)
#	@show size(row)
#	@show typeof(row)
#	@show row
#	@show historicaldata
	#newdata = vcat(historicaldata, row)
	return newdata
end

function lookUpValue(data, item, desiredtime)
	#data = historicaldata[2:end, :] # remove row of ones used to initiate the array
	#let's linearly interpolate to find items
	#@show desiredtime
	defaultvalue = 20.0 #value for fesmax
	if(desiredtime <0 && contains(item, AbstractString("fsp")))
		return 16.11
	elseif(desiredtime <0 && contains(item, AbstractString("fev")))
		return 3.2 #fev0
	elseif(desiredtime <0 && contains(item, AbstractString("fes")))
		return 16.11 #fes0
	elseif(desiredtime <0 && contains(item, AbstractString("fcs")))
		return 25 #fcs0
	elseif(desiredtime <0 && contains(item, AbstractString("fsh")))
		return 16.11 #fcs0
	elseif(desiredtime <0 && contains(item, AbstractString("fv")))
		return 3.2 #fev0
	elseif(desiredtime <0 && contains(item, AbstractString("fac")))
		return 3.2 #between facmin and facmax 
	elseif( desiredtime< 0)
		return defaultvalue
	elseif(abs(desiredtime) > data[end,1])
		#println("got here")
		return defaultvalue
	end

	item = AbstractString(item)
	upperindex = findBounds(desiredtime,data)
	#@show desiredtime, data[end,1], upperindex
	lowerindex = upperindex -1
	#@show typeof(item)
	if(contains(item, AbstractString("fev")))
		return linInerp(data[lowerindex,2], data[upperindex,2], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fes")))
		return linInerp(data[lowerindex,3], data[upperindex,3], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fcs")))
		return linInerp(data[lowerindex,4], data[upperindex,4], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fsp")))
		return linInerp(data[lowerindex,5], data[upperindex,5], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fsh")))
		return linInerp(data[lowerindex,6], data[upperindex,6], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fv")))
		return linInerp(data[lowerindex,7], data[upperindex,7], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fac")))
		return linInerp(data[lowerindex,8], data[upperindex,8], data[lowerindex,1], data[upperindex,1], desiredtime)
	else
		println("Fell through")
		@show item
		return defaultvalue
	end

	
end

function linInerp(lowerval, upperval, tstart, tend, tdesired)
	val = lowerval +(upperval-lowerval)/(tend-tstart)*(tdesired-tstart)
	return val
end

function findBounds(time, data)
	index = 0
#	for j in collect(1:length(data-1))
#		if(data[j,1]>=time)
#			index = j
#			break
#		end
#	end
	index=searchsortedfirst(vec(data[:,1]),time, by=abs)
	return index
end

function calculate_dV(historicaldata, currV, currt)
	prevt = historicaldata[1]
	prevV = historicaldata[2]
	if(currt==prevt)
		currt = prevt+10^10*eps()
	end
	@show prevt, currt, prevV, currV
	dV = (currV-prevV)/(currt-prevt)
	return dV
end

function updateHistoricalData(historicaldata, currV, currt)
	historicaldata[1] = currt
	historicaldata[2] = currV
	return historicaldata
end

function plotEverything(tout, res, data_dict, outputfn)
	names=fill("", 1, size(res,2))
	names[1]="Ppa"
	names[2]="Fpa"
	names[3]="Ppp"
	names[4]="Ppv" 
	names[5]="Psa"
	names[6]="Fsa"
	names[7]="Psp"
	names[8]="Psv"
	names[9]="Pmv"
	names[10]="Pbv"
	names[11]="Phv"
	names[12]="Pla"
	names[13]="Vlv"
	names[14]="Psi"
	names[15]="Pra"
	names[16]="Vrv"
	names[17]="Psquiggle"
	names[18]="fac"
	names[19]="fap"
	names[20]="Thetasp"
	names[21]="Thetash"
	names[22]="deltaVT"
	names[23]="deltaEmaxlv"
	names[24]="deltaEmaxrv"
	names[25]="deltaRsp"
	names[26]="deltaRep"
	names[27]="deltaRmp"
	names[28]="deltaVusv"
	names[29]="deltaVuev"
	names[30]="deltaVum"
	names[31]="deltaTs"
	names[32]="deltaTv"
	names[33]="xb"
	names[34]="xh"
	names[35]="xm"
	names[36]="Wh"
	figure(figsize=(30,20))
	PyPlot.hold(true)
	#plt[:tight_layout]()
	@show size(res)
	for j in collect(1:size(res,2))
		plt[:subplot](6,6,j)
		plot(tout, res[:,j], "k", linewidth = .25)
		ylabel(names[j])
	end
	savefig(outputfn)
end

function plotPretty(tout, res,data_dict, outputfn)
	resistances = data_dict["RESISTANCE"]
	Rsa=resistances[1]
	Rsp=resistances[2]
	Rep=resistances[3]
	Rmp=resistances[4]
	Rbp=resistances[5]
	Rhp=resistances[6]
	Rsv=resistances[7]
	Rev=resistances[8]
	Rmv=resistances[9]
	Rbv=resistances[10]
	Rhv=resistances[11]
	Rpa=resistances[12]
	Rpp=resistances[13]
	Rpv=resistances[14]


	Ts = res[:, 31]
	Tv = res[:, 32]
	T = Ts+Tv+data_dict["REFLEX"][end]
	Psa = res[:, 5] #systemic pressure
	fac =res[:, 18]
	Psp = res[:, 7]

	Fsp = Psp/Rsp
	Fep = Psp/Rep
	Fmp = Psp/Rmp
	Fbp = Psp/Rbp
	Fhp = Rsp/Rhp

	figure(figsize=(30,20))
	PyPlot.hold(true)
	#plt[:tight_layout]() 	 #to prevent plots from overlapping
	plt[:subplot](2,4,1)
	plot(tout, 1./T*60, "k")
	#xlabel("Time in seconds")
	ylabel("HR, in BPM")
	plt[:subplot](2,4,2)
	plot(tout, Psa, "k", linewidth = .5)
	ylabel("Systemic Pressure, in mmHg")

	plt[:subplot](2,4,3)
	plot(tout, Fsp, "k")
	ylabel("Splanchnic peripheral flow")
	plt[:subplot](2,4,4)
	plot(tout, Fep, "k")
	ylabel("Extrasplanchnic flow")
	plt[:subplot](2,4,5)
	plot(tout, Fmp, "k")
	ylabel("Muscle flow")
	plt[:subplot](2,4,6)
	plot(tout, Fbp, "k")
	ylabel("Brain Flow")
	savefig(outputfn)
end

function plotPrettyWithOverlaidData(tout,res, data_dict, lowFdata, highFdata, outputfn)
	resistances = data_dict["RESISTANCE"]
	Rsa=resistances[1]
	Rsp=resistances[2]
	Rep=resistances[3]
	Rmp=resistances[4]
	Rbp=resistances[5]
	Rhp=resistances[6]
	Rsv=resistances[7]
	Rev=resistances[8]
	Rmv=resistances[9]
	Rbv=resistances[10]
	Rhv=resistances[11]
	Rpa=resistances[12]
	Rpp=resistances[13]
	Rpv=resistances[14]

	deltaRsp = res[:, 25]
	deltaRep = res[:, 26]
	deltaRmp = res[:,27]


	Ts = res[:, 31]
	Tv = res[:, 32]
	T = Ts+Tv+data_dict["REFLEX"][end]
	Psa = res[:, 5] #systemic pressure
	fac =res[:, 18]
	Psp = res[:, 7]

	Fsp = Psp/(Rsp+deltaRsp)
	Fep = Psp/(Rep+deltaRep)
	Fmp = Psp/(Rmp+deltaRep)
	Fbp = Psp/Rbp
	Fhp = Rsp/Rhp

	figure(figsize=(30,20))
	PyPlot.hold(true)
	#plt[:tight_layout]() 	 #to prevent plots from overlapping
	plt[:subplot](2,4,1)
	plot(tout, 1./T*60, "k")
	plot(lowFdata[:Elapsedtime], lowFdata[:HR], "r.")
	#xlabel("Time in seconds")
	ylabel("HR, in BPM")
	plt[:subplot](2,4,2)
	plot(tout, Psa, "k", linewidth = .5)
	plot(highFdata[:Elapsedtime], highFdata[:ABP], "r-",linewidth = .25)
	ylabel("Systemic Pressure, in mmHg")

	plt[:subplot](2,4,3)
	plot(tout, Fsp, "k")
	ylabel("Splanchnic peripheral flow")
	plt[:subplot](2,4,4)
	plot(tout, Fep, "k")
	ylabel("Extrasplanchnic flow")
	plt[:subplot](2,4,5)
	plot(tout, Fmp, "k")
	ylabel("Muscle flow")
#	plt[:subplot](2,4,6)
#	plot(tout, fsh, "k")
#	ylabel("Efferent activity in heart")
	savefig(outputfn)
end

function attemptToRecreateFig13(t,res, data_dict, outputfn, pathtodata)
	close("all")
	resistances = data_dict["RESISTANCE"]
	Rsa=resistances[1]
	Rsp=resistances[2]
	Rep=resistances[3]
	Rmp=resistances[4]
	Rbp=resistances[5]
	Rhp=resistances[6]
	Rsv=resistances[7]
	Rev=resistances[8]
	Rmv=resistances[9]
	Rbv=resistances[10]
	Rhv=resistances[11]
	Rpa=resistances[12]
	Rpp=resistances[13]
	Rpv=resistances[14]
	Rsp0 = data_dict["REFLEX"][33]
	Rep0 =data_dict["REFLEX"][34]
	
	fd = readdlm(pathtodata, ',')
	tflow = fd[:,1]
	Fil = fd[:,2]
	Fol = fd[:,3]
	Fsa = fd[:,4]
	Fsp =fd[:,5]
	Fep = fd[:,6]
	Fmp = fd[:,7]
	Fbp = fd[:,8]
	Fhp = fd[:,9]
	For =fd[:,10]
	Fpa = fd[:,11]

	Ts = res[:, 31]
	Tv = res[:, 32]
	Psa = res[:, 5]
	#Fsa =res[:, 6]
	Psp = res[:, 7]
	deltaRsp = res[:, 25]
	deltaRep = res[:, 26]
	Rsp = deltaRsp+Rsp
	Rep = deltaRep + Rep
	#@show Rsp
	#@show Rep

	T = Ts+Tv+data_dict["REFLEX"][end]
	figure(figsize=(30,20))
	plt[:subplot](2,2,1)
	#axis([0,100,60,160])
	@show size(t)
	@show size(Psa)
	plot(t, Psa, "k", linewidth = .5)
	ylabel("Arterial Pressure, mmHg")
	#axis([000,600,20,160])
	plt[:subplot](2,2,2)
	plot(t, 1./T*60, "k", linewidth = .5)
	ax = gca()
	#ax[:ticklabel_format](useOffset=false)
	ylabel("Heart Rate, bpm")
	#axis([00,600,40,100])
	plt[:subplot](2,2,3)
	#axis([0,100,0,40])
	@show size(Fsp)
	@show size(tflow)
	@show size(Fsa)
	startidx =size(tflow,1)-size(tflow[tflow.>=100],1)
	plot(tflow, Fsp, linewidth = .5, "k")
	#axis([00,600, 0, 40])
	ylabel("Splanchic Flow")
	plt[:subplot](2,2,4)
	#axis([00,600, 0, 40])
	plot(tflow, Fep, linewidth = .5, "k")
	ylabel("Extrasplanchic Flow")
	savefig(outputfn)

end
