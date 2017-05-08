#using ODE
using Sundials
include("DataFile.jl")
include("buildIC.jl")
using PyPlot

#function complexHeartModel(t,y,data_dict)
function complexHeartModel(t,y,dydt,data_dict)
	Ppa = y[1]
	Fpa = y[2]
	Ppp = y[3]
	Ppv = y[4]
	Psa = y[5]
	Fsa = y[6]
	Psp = y[7]
	Psv = y[8]
	Pmv = y[9]
	Pbv = y[10]
	Phv = y[11]
	Pla = y[12]
	Vlv = y[13]
	Psi = mod(y[14],1)
	Pra = y[15]
	Vrv = y[16]
	Psquiggle = y[17]
	fac = y[18]
	fap = y[19]
	fsp = y[20]
	fsh = y[21]
	fv = y[22]
	Thetasp = y[23]
	Thetash = y[24]
	deltaVT = y[25]
	deltaEmaxlv = y[26]
	deltaEmaxrv = y[27]
	deltaRsp = y[28]
	deltaRep = y[29]
	deltaRmp = y[30]
	deltaVusv = y[31]
	deltaVuev = y[32]
	deltaVumv = y[33]
	deltaTs = y[34]
	deltaTv = y[35]
	xb = y[36]
	xh = y[37]
	xm = y[38]
	Wh = y[39]

	#unpack data dictionary
	volumes = data_dict["UNSTRESSEDVOLUME"]
	resistances = data_dict["RESISTANCE"]
	compliances = data_dict["COMPLIANCE"]
	inertances = data_dict["INERTANCE"]
	heart = data_dict["HEART"]
	#T = data_dict["BASAL_HEART_PERIOD"]
	dVterms = data_dict["DVTERMS"]
	barroreflex = data_dict["BARROREFLEX"]
	chemoreflex = data_dict["CHEMOREFLEX"]
	pulmonarystretch = data_dict["PULMONARY_STRETCH"]
	sympathetic = data_dict["SYMPATHETIC"]
	vagal = data_dict["VAGAL"]
	CNS = data_dict["CNS"]
	ventilatory = data_dict["VENTILATORY"]
	reflex = data_dict["REFLEX"]
	localmetabolic = data_dict["LOCAL_METABOLIC"]
	PaCO2 = data_dict["CO2_PRESSURE"]
	
	Csa=compliances[1]
	Csp=compliances[2]
	Cep=compliances[3]
	Cmp=compliances[4]
	Cbp=compliances[5]
	Chp=compliances[6]
	Csv=compliances[7]
	Cev=compliances[8]
	Cmv=compliances[9]
	Cbv=compliances[10]
	Chv=compliances[11]
	Cpa=compliances[12]
	Cpp=compliances[13]
	Cpv=compliances[14]
	
	Vusa=volumes[1]
	Vusp=volumes[2]
	Vuep=volumes[3]
	Vump=volumes[4]
	Vubp=volumes[5]
	Vuhp=volumes[6]
	Vusv=volumes[7]
	Vuev=volumes[8]
	Vumv=volumes[9]
	Vubv=volumes[10]
	Vuhv=volumes[11]
	Vupa=volumes[12]
	Vupp=volumes[13]
	Vupv=volumes[14]
	Vtot = volumes[15]

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

	Lsa = inertances[1]
	Lpa = inertances[2]

	Cla = heart[1]
	Vula = heart[2]
	Rla = heart[3]
	P0lv =heart[4]
	kelv = heart[5]
	Vulv = heart[6]
	Emaxlv = heart[7]
	krlv = heart[8]
	Cra = heart[9]
	Vura = heart[10]
	Rra = heart[11]
	P0rv = heart[12]
	kerv = heart[13]
	Vurv = heart[14]
	Emaxrv = heart[15]
	krrv = heart[16]
	ksys = heart[17]
	Tsys0 = heart[18]

	dVusudt = dVterms[1]
	dVumvdt = dVterms[2]

	tauzb = barroreflex[1]
	taupb = barroreflex[2]
	fabmin =barroreflex[3]
	fabmax = barroreflex[4]
	Pn = barroreflex[5]
	kab = barroreflex[6]

	tauc = chemoreflex[1]
	facmin = chemoreflex[2]
	facmax = chemoreflex[3]
	PO2n = chemoreflex[4]
	kac = chemoreflex[5]
	PaO2 = chemoreflex[6]

	taup = pulmonarystretch[1]
	Gap = pulmonarystretch[2]

	fesinf =sympathetic[1]
	fes0 = sympathetic[2]
	fesmin = sympathetic[3]
	fesmax = sympathetic[4]
	kes = sympathetic[5]
	Wbsp = sympathetic[6]
	Wcsp = sympathetic[7]
	Wpsp = sympathetic[8]
	Wbsh = sympathetic[9]
	Wcsh = sympathetic[10]

	fevinf = vagal[1]
	fev0 = vagal[2]
	fab0 = vagal[3]
	kev = vagal[4]
	Wcv = vagal[5]
	Wpv = vagal[6]
	Thetav =vagal[7]

	ChiMaxsp = CNS[1]
	ChiMaxsh = CNS[2]
	tauisc = CNS[3]
	ChiMinsp = CNS[4]
	ChiMinsh = CNS[5]
	PO2nsp = CNS[6]
	PO2nsh = CNS[7]
	kiscsp = CNS[8]
	kiscsh = CNS[9]

	Gv =  ventilatory[1]
	tauv =  ventilatory[2]
	Dv = ventilatory[3]
	VTn = ventilatory[4]
	facn = ventilatory[5]

	GEmaxlv=reflex[1]
	GEmaxrv=reflex[2]
	GRsp=reflex[3]
	GRep=reflex[4]
	GRmp=reflex[5]
	GVusv=reflex[6]
	GVuev = reflex[7]
	GVumv=reflex[8]
	GTs=reflex[9]
	GTv=reflex[10]
	tauEmaxlv=reflex[11]
	tauEmaxrv=reflex[12]
	tauRsp=reflex[13]
	tauRep=reflex[14]
	tauRmp = reflex[15]
	tauVusv=reflex[16]
	tauVuev=reflex[17]
	tauVumv=reflex[18]
	tauTs=reflex[19]
	tauTv=reflex[20]
	DEmaxlv=reflex[21]
	DEmaxrv=reflex[22]
	DRsp=reflex[23]
	DRep=reflex[24]
	DRmp=reflex[25]
	DVusv=reflex[26]
	DVuev=reflex[27]
	DVumv=reflex[28]
	DTs=reflex[29]
	DTv=reflex[30]
	Emaxlv0=reflex[31]
	Emaxrv0=reflex[32]
	Rsp0=reflex[33]
	Rep0=reflex[34]
	Rmp0=reflex[35]
	Vusv0=reflex[36]
	Vuev0=reflex[37]
	Vumv0=reflex[38]
	T0 = reflex[39]

	CvmO2n = localmetabolic[1]
	CvbO2n =localmetabolic[2]
	CvhO2n =localmetabolic[3]
	Whn = localmetabolic[4]
	Mdotm = localmetabolic[5]
	Mdotb =localmetabolic[6]
	Mdothn = localmetabolic[7]
	GmO2 =localmetabolic[8]
	GbO2 = localmetabolic[9]
	GhO2 = localmetabolic[10]
	tauw = localmetabolic[11]
	taum = localmetabolic[12]
	taub = localmetabolic[13]
	tauh = localmetabolic[14]
	C = localmetabolic[15]
	a = localmetabolic[16]
	alpha = localmetabolic[17]
	beta = localmetabolic[18]
	K = localmetabolic[19]

	#conversation of mass

	Vu = Vusa +Vusp +Vuep+Vump + Vubp+Vuhp+Vusv+Vuev+Vumv+Vubv+Vuhv+Vura+Vupa+Vupp+Vupv+Vula#eqn 13
	Pev = 1/Cev*(Vtot-Csa*Psa-(Csp+Cep+Cmp+Cbp+Chp)*Psp-Csv*Psv -Cmv*Pmv -Cbv*Pbv-Chv*Phv-Cra*Pra-Vrv-Cpa*Ppa-Cpp*Ppp-Cpv*Ppv-Cla*Pla-Vlv-Vu)#eqn 12
	#@show Vu, Pev
	#reflex regulation, cardiac elastances
	SigmaSubEmaxlv = 0.0
	SigmaSubEmaxrv = 0.0
	if(fsh>=fesmin)
		SigmaSubEmaxlv= GEmaxlv*log(abs(fsh*(t-DEmaxlv)-fesmin+1))
		SigmaSubEmaxrv= GEmaxrv*log(abs(fsh*(t-DEmaxrv)-fesmin+1))
	else
		SigmaSubEmaxlv = 0.0
		SigmaSubEmaxrv = 0.0
	end
	#@show SigmaSubEmaxlv, SigmaSubEmaxrv
	#@show deltaEmaxlv, deltaEmaxrv
	ddeltaEmaxlvdt = 1/tauEmaxlv*(-deltaEmaxlv+SigmaSubEmaxlv)
	ddeltaEmaxrvdt = 1/tauEmaxrv*(-deltaEmaxrv+SigmaSubEmaxrv)

	Emaxlv = deltaEmaxlv+Emaxlv0
	Emaxrv = deltaEmaxrv+Emaxrv0
	#@show Emaxlv, Emaxrv
	#heart period
	SigmaTs = 0.0
	if(fsh > fesmin)
		SigmaTs = GTs*log(abs(fsh*(t-DTs)-fesmin+1))
	else
		SigmaTs = 0.0
	end
	ddeltaTsdt = 1/tauTs*(-deltaTs+SigmaTs)
	SigmaTv = GTv*fv*(t-DTv)
	ddeltaTvdt = 1/tauTv*(-deltaTv+SigmaTv)
	T = deltaTs+deltaTv+T0

	#heart calculations
	
	#Psi = mod(Psi, 1)
	dPsidt = 1/T
	if(Psi>1)
		dPsidt = 0
	end
	u = mod(Psi,1) #equvalent to frac, reset when it gets to one
	@show t,T, Psi, dPsidt, deltaTs, deltaTv,u
#	if(Psi >1) #reset, equvalent to frac
#		Psi = 0.0
#	end

	Tsys = Tsys0-ksys*1/T
	phi=0.0
	if(u >= 0 && u<=Tsys/T)
		phi = sin(pi*T*u/Tsys)^2
	elseif(u>=Tsys/T && u<=1)
		phi = 0.0
	end

	Pmaxlv = phi*Emaxlv*(Vlv*Vulv)+(1-phi)*P0lv*(exp(kelv*Vlv)-1)
	Rlv = krlv*Pmaxlv
	if(Pmaxlv<=Psa)
		Fol = 0.0
	else
		Fol = (Pmaxlv-Psa)/Rlv
	end
	Plv = Pmaxlv - Rlv*Fol
	if(Plv>=Pla)
		Fil = 0.0
	else
		Fil = (Pla-Plv)/Rla
	end

	dPladt = 1/Cla*((Ppv-Pla)/Rpv-Fil)
	dVlvdt = Fil-Fol
	Pmaxrv = phi*Emaxrv*(Vrv-Vurv) + (1-phi)*P0rv*(exp(kerv*Vrv)-1)
	Rrv = krrv*Pmaxrv
	if(Pmaxrv<=Ppa)
		For=0.0
	else
		For=(Pmaxrv-Ppa)/Rrv
	end

	Prv = Pmaxrv-Rrv*For
	if(Pra<=Prv)
		Fir = 0.0
	else
		Fir = (Pra-Prv)/Rra
	end
	
	#heart as a pump, right side
	dPradt = 1/Cra*((Psv-Pra)/Rsv+(Pev-Pra)/Rev-Fir)
	dVrvdt = Fir-For

	#ventilatory response 
	VT = VTn + deltaVT
	ddeltaVTdt = 1/tauv*(-deltaVT+Gv*(fac*(t-Dv)-facn))	

	#force balances
	dPpadt = 1/Cpa*(For-Fpa) #eqn 1, conversation of mass at pulmonary arteries
	dFpadt = 1/Lpa*(Ppa-Ppp-Rpa*Fpa)# eqn 2, balance of forces at pulmonary arteries
	dPppdt = 1/Cpp*(Fpa -(Ppp-Ppv)/Rpp) #eqn 3, conversation of mass at pulmonary peripheral circulation
	dPpvdt = 1/Cpv*((Ppp-Ppv)/Rpp-(Ppv-Pla)/Rpv) #eqn 4, conversation of mass at pulmonary veins
	dPsadt = 1/Csa*(Fol-Fsa)#eqn 5, conversation of mass at system arteries
	dFsadt = 1/Lsa*(Psa-Psp-Rsa*Fsa) #eqn 6, balance of forces at system arteries
	dPspdt = 1/(Csp+Cep+Cmp+Cbp+Chp)*(Fsa-(Psp-Psv)/Rsp-(Psp-Pev)/Rep-(Psp-Pmv)/Rmp-(Psp-Pbv)/Rbp-(Psp-Phv)/Rhp)#eqn 7 conversavation of mass at systemic perhipheral circulation
	dPsvdt = 1/Csv*((Psp-Psv)/Rsp-(Psv-Pra)/Psv-dVusudt) #eqn 8 Conservation of Mass at Splanchnic Veins
	dPmvdt = 1/Cmv*((Psp-Pmv)/Rmp-(Pmv-Pra)/Rmv-dVumvdt) #eqn 9 Conservation of Mass at Skeletal Muscle Veins
	dPbvdt = 1/Cbv*((Psp-Pbv)/Rbp-(Pbv-Pra)/Rbv) #eqn 10 Conservation of Mass at Brain Veins
	dPhvdt = 1/Chv*((Psp-Phv)/Rhp-(Phv-Pra)/Rhv) #eqn 11 Conservation of Mass at Coronary Veins

	#afferent baroreflex
	Pb = Psa #for closed loop operation
	dPbdt = dPsadt
	dPsquiggledt = 1/taupb*(Pb+tauzb*dPbdt-Psquiggle)
	fab = (fabmin+fabmax*exp((Psquiggle-Pn)/kab))/(1+exp((Psquiggle-Pn)/kab))
	dfabdt = (fabmax-fabmin)*dPsquiggledt*sech((Pn-Psquiggle)/2*kab)^2/(4*kab) #from wolfram alpha
	
	#afferent chemoreflex
	Phiac = (facmax-facmin*exp((PaO2-PO2n)/kac))/(1+exp((PaO2-PO2n)/kac))
	dfacdt = 1/tauc*(-fac+Phiac)
	#pulmonarystretch
	Phiap = Gap*VT
	dfapdt = 1/taup*(-fap*Phiap)	

	#efferent neural pathways
	if(fsh < fesmax)
		fsp = fesinf +(fes0-fesinf)*exp(-Wbsp*fab+Wcsp*fac-Wpsp*fap-Thetasp)
	else
		fsp = fesmax
	end

	if(fsh < fesmax)
		fsh = fesinf +(fes0-fesinf)*exp(-Wbsh*fab+Wcsh*fac-Thetash)
	else
		fsh = fesmax
	end
	#vagal
	fv = (fev0+fevinf*exp((fab-fab0)/kev))/(1+exp((fab-fab0)/kev))
	dfvdt = (fevinf-fev0)*dfabdt*sech((fab0-fab)/2kev)^2/(4*kev)

	#CNS hypoxic response
	Chisp = (ChiMinsp+ChiMaxsp*exp((PaO2-PO2nsp)/kiscsp))/(1+exp((PaO2-PO2nsp)/kiscsp))
	dThetaspdt = 1/tauisc*(-Thetasp+Chisp)
	Chish = (ChiMinsh+ChiMaxsh*exp((PaO2-PO2nsh)/kiscsh))/(1+exp((PaO2-PO2nsh)/kiscsh))
	dThetashdt = 1/tauisc*(-Thetash+Chish)
	
	#reflex regulation
		#resistances and unstressed volumes
	if(fsp >=fesmin)
		SigmaSubRsp = GRsp*log(abs(fsp*(t-DRsp)-fesmin+1))
		SigmaSubRep = GRep*log(abs(fsp*(t-DRep)-fesmin+1))
		SigmaSubRmp = GRmp*log(abs(fsp*(t-DRmp)-fesmin+1))
		SigmaSubVusv = GVusv*log(abs(fsp*(t-DVusv)-fesmin+1))
		SigmaSubVuev = GVuev*log(abs(fsp*(t-DVuev)-fesmin+1))
		SigmaSubVumv = GVumv*log(abs(fsp*(t-DVumv)-fesmin+1))
	else
		SigmaSubRsp = 0
		SigmaSubRep = 0
		SigmaSubRmp = 0
		SigmaSubVusv = 0
		SigmaSubVuev = 0
		SigmaSubVumv = 0
	end

	ddeltaRspdt = 1/tauRsp*(-deltaRsp+SigmaSubRsp)
	ddeltaRepdt = 1/tauRep*(-deltaRep+SigmaSubRep)
	ddeltaRmpdt = 1/tauRmp*(-deltaRmp+SigmaSubRmp)
	ddeltaVusvdt = 1/tauVusv*(-deltaVusv+SigmaSubVusv)
	ddeltaVuevdt = 1/tauVuev*(-deltaVuev+SigmaSubVuev)
	ddeltaVumvdt = 1/tauVumv*(-deltaVumv+SigmaSubVumv)

	Rsp = deltaRsp+Rsp0
	Rep = deltaRep + Rep0
	Rmp = deltaRmp + Rmp0
	Vusv = deltaVusv+Vusv0
	Vuev = deltaVuev+Vuev0
	Vumv = deltaVumv+Vumv0

	#local effect of O2
	#these flows may be incorrect
	Fb = Psp/Rhp
	Fh = Psp/Rhp
	Fm = Fsa-Fb-Fh
	FO2 = PaO2*(1+beta*PaCO2)/(K*(1+alpha*(PaCO2)))
	CaO2 = C*(FO2)^(1/alpha)/(1+FO2^(1/alpha))	

	CvbO2 = CaO2-Mdotb/Fb
	CvhO2 = CaO2-Mdothn/Fh
	CvmO2 = CaO2-Mdotm/Fm


	dxbdt = 1/taub*(-xb-GbO2*(CvbO2-CvbO2n))
	dxhdt = 1/tauh*(-xh-GhO2*(CvhO2-CvhO2n))
	dxmdt = 1/taum*(-xm-GmO2*(CvmO2-CvmO2n))

#	Rbp = Rbpn/(1+xb)
#	Rhp = Rbhn/(1+xh)
#	Rmp = Rbmn/(1+xm)

	Mdoth = Wh/Whn*Mdothn
	wh = -Plv*dVlvdt-Prv*dVrvdt
	dWhdt = 1/tauw*(wh-Wh)

	#dydt = Float64[]
#	push!(dydt, dPpadt)
#	push!(dydt, dFpadt)
#	push!(dydt, dPppdt)
#	push!(dydt, dPpvdt)
#	push!(dydt, dPsadt)
#	push!(dydt, dFsadt)
#	push!(dydt, dPspdt)
#	push!(dydt, dPsvdt)
#	push!(dydt, dPmvdt)
#	push!(dydt, dPbvdt)
#	push!(dydt, dPhvdt)
#	push!(dydt, dPladt)
#	push!(dydt, dVlvdt)
#	push!(dydt, dPsidt)
#	push!(dydt, dPradt)
#	push!(dydt, dVrvdt)
#	push!(dydt, dPsquiggledt)
#	push!(dydt, dfacdt)
#	push!(dydt, dfapdt)
#	push!(dydt, 0) #fsh)
#	push!(dydt, 0) #fsh
#	push!(dydt, 0) #fv
#	push!(dydt, dThetaspdt)
#	push!(dydt, dThetashdt)
#	push!(dydt, ddeltaVTdt)
#	push!(dydt, ddeltaEmaxlvdt)
#	push!(dydt, ddeltaEmaxrvdt)
#	push!(dydt, ddeltaRspdt)
#	push!(dydt, ddeltaRepdt)
#	push!(dydt, ddeltaRmpdt)
#	push!(dydt, ddeltaVusvdt)
#	push!(dydt, ddeltaVuevdt)
#	push!(dydt, ddeltaVumvdt)
#	push!(dydt, ddeltaTsdt)
#	push!(dydt, ddeltaTvdt)
#	push!(dydt, dxbdt)
#	push!(dydt, dxhdt)
#	push!(dydt, dxmdt)
#	push!(dydt, dWhdt)
	#dydt = transpose(ones(1,39))
	dydt[1] = dPpadt
	dydt[2] = dFpadt
	dydt[3]= dPppdt
	dydt[4] = dPpvdt
	dydt[5] =dPsadt
	dydt[6]=dFsadt
	dydt[7]= dPspdt
	dydt[8] = dPsvdt
	dydt[9] = dPmvdt
	dydt[10] = dPbvdt
	dydt[11] = dPhvdt
	dydt[12]=dPladt
	dydt[13]=dVlvdt
	dydt[14] = dPsidt
	dydt[15]=dPradt
	dydt[16] = dVrvdt
	dydt[17]= dPsquiggledt
	dydt[18] = dfacdt
	dydt[19] = dfapdt
	dydt[20] = 0 #fsp
	dydt[21] = 0 #fsh
	dydt[22] = 0#dfvdt
	dydt[23] = dThetaspdt
	dydt[24] = dThetashdt
	dydt[25] = ddeltaVTdt
	dydt[26] = ddeltaEmaxlvdt
	dydt[27] = ddeltaEmaxrvdt
	dydt[28] = ddeltaRspdt
	dydt[29] = ddeltaRepdt
	dydt[30] = ddeltaRmpdt
	dydt[31] = ddeltaVusvdt
	dydt[32] = ddeltaVuevdt
	dydt[33] = ddeltaVumvdt
	dydt[34] = ddeltaTsdt
	dydt[35] = ddeltaTvdt
	dydt[36] = dxbdt
	dydt[37] = dxhdt
	dydt[38] = dxmdt
	dydt[39] = dWhdt
	#@show dydt
	return dydt

end

function main()
	t = collect(0:.01:800)
	data_dict = DataFile()
	initial_conditions = buildIC(39)
	#need to actually figure out initial conditions
	#fedeqns(t,y)= complexHeartModel(t,y,data_dict)
	#tout, res = ODE.ode23(fedeqns, initial_conditions, t, points=:specified)
	fedeqns(t,y,ydot)= complexHeartModel(t,y,ydot,data_dict)
	res = Sundials.cvode(fedeqns, vec(initial_conditions), t)
	#psi = [a[14] for a in res]
	#@show res
	psi = res[:, 14]
	#plot(t, mod(psi,1), "kx")
	plotPretty(t, res,data_dict)
	
end

function plotPretty(tout, res,data_dict)
	#Ts = [ a[34] for a in res]
	#Tv =[ a[35] for a in res] 
	Ts = res[:, 34]
	Tv = res[:, 35]
	T = Ts+Tv+data_dict["REFLEX"][end]
#	Psa = [a[5] for a in res] #systemic pressure
#	fac = [a[18] for a in res]
#	fap = [a[19] for a in res]
#	fsp= [a[20] for a in res]
#	fsh = [a[21] for a in res]
	Psa = res[:, 5] #systemic pressure
	fac =res[:, 18]
	fap = res[:, 19]
	fsp= res[:, 20]
	fsh =res[:, 21]
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
	plot(tout, fac, "k")
	ylabel("Afferent Activity from peripherial chemoreceptors")
	plt[:subplot](2,4,4)
	plot(tout, fap, "k")
	ylabel("Afferent Activity from lung stretch receptors")
	plt[:subplot](2,4,5)
	plot(tout, fsp, "k")
	ylabel("Efferent activity in vessels")
	plt[:subplot](2,4,6)
	plot(tout, fsh, "k")
	ylabel("Efferent activity in heart")
end
