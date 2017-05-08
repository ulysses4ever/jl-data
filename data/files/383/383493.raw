function DataFile()
	compliance_array = Float64[]
	Csa=0.28 
	Csp=2.05
	Cep=0.668
	Cmp=0.525
	Cbp =0.358
	Chp=0.119
	Csv=61.11
	Cev=20
	Cmv=15.71
	Cbv=10.71
	Chv=3.57
	Cpa=0.76
	Cpp=5.80
	Cpv=25.37
	push!(compliance_array, Csa)
	push!(compliance_array, Csp)
	push!(compliance_array, Cep)
	push!(compliance_array, Cmp)
	push!(compliance_array, Cbp)
	push!(compliance_array, Chp)
	push!(compliance_array, Csv)
	push!(compliance_array, Cev)
	push!(compliance_array, Cmv)
	push!(compliance_array, Cbv)
	push!(compliance_array, Chv)
	push!(compliance_array, Cpa)
	push!(compliance_array, Cpp)
	push!(compliance_array, Cpv)
	
	volume_array = Float64[]
	Vusa=0.0
	Vusp=274.4
	Vuep=134.64
	Vump=105.8
	Vubp=72.13
	Vuhp=24.0
	Vusv=1121.0
	Vuev=550.0
	Vumv=432.14
	Vubv=294.64
	Vuhv=98.21
	Vupa=0.0
	Vupp=123.0
	Vupv=120.0
	Vtot = 5300.0
	push!(volume_array, Vusa)
	push!(volume_array, Vusp)
	push!(volume_array, Vuep)
	push!(volume_array, Vump)
	push!(volume_array, Vubp)
	push!(volume_array, Vuhp)
	push!(volume_array, Vusv)
	push!(volume_array, Vuev)
	push!(volume_array, Vumv)
	push!(volume_array, Vubv)
	push!(volume_array, Vuhv)
	push!(volume_array, Vupa)
	push!(volume_array, Vupp)
	push!(volume_array, Vupv)
	push!(volume_array, Vtot)

	resistance_array = Float64[]
	Rsa =0.06
	Rsp =3.307
	Rep =3.52
	Rmp =4.48
	Rbp =6.57
	Rhp =19.71
	Rsv =0.038
	Rev =0.04
	Rmv =0.05
	Rbv =0.075
	Rhv =0.224
	Rpa =0.023
	Rpp =0.0894
	Rpv =0.0056

	push!(resistance_array, Rsa)
	push!(resistance_array, Rsp)
	push!(resistance_array, Rep)
	push!(resistance_array, Rmp)
	push!(resistance_array, Rbp)
	push!(resistance_array, Rhp)
	push!(resistance_array, Rsv)
	push!(resistance_array, Rev)
	push!(resistance_array, Rmv)
	push!(resistance_array, Rbv)
	push!(resistance_array, Rhv)
	push!(resistance_array, Rpa)
	push!(resistance_array, Rpp)
	push!(resistance_array, Rpv)

	inhertance_array = Float64[]
	Lsa = .22E-3
	Lpa = .18E-3
	push!(inhertance_array, Lsa)
	push!(inhertance_array, Lpa)

	heart_array = Float64[]
	Cla = 19.23
	Vula = 25
	Rla = 2.5E-3
	P0lv = 1.5
	kelv = .014
	Vulv = 16.77
	Emaxlv = 2.95
	krlv = 3.75E-4
	Cra = 31.25
	Vura = 25
	Rra = 2.5E-3
	P0rv = 1.5
	kerv = 0.011
	Vurv = 40.8
	Emaxrv = 1.75
	krrv = 1.4E-3
	ksys = .075
	Tsys0 = .5
	push!(heart_array, Cla)
	push!(heart_array, Vula)
	push!(heart_array, Rla)
	push!(heart_array, P0lv)
	push!(heart_array, kelv)
	push!(heart_array, Vulv)
	push!(heart_array, Emaxlv)
	push!(heart_array, krlv)
	push!(heart_array, Cra)
	push!(heart_array, Vura)
	push!(heart_array, Rra)
	push!(heart_array, P0rv)
	push!(heart_array, kerv)
	push!(heart_array, Vurv)
	push!(heart_array, Emaxrv)
	push!(heart_array, krrv)
	push!(heart_array, ksys)
	push!(heart_array, Tsys0)

	dvTerms = Float64[]
	dVusudt = 0.0
	dVumvdt = 0.0

	push!(dvTerms, dVusudt)
	push!(dvTerms, dVumvdt)

	barroreflex = Float64[]
	tauzb = 6.37
	taupb = 2.076
	fabmin = 2.52
	fabmax = 47.78
	Pn = 92
	kab = 11.76
	push!(barroreflex, tauzb)
	push!(barroreflex, taupb)
	push!(barroreflex, fabmin)
	push!(barroreflex, fabmax)
	push!(barroreflex, Pn)
	push!(barroreflex, kab)

	chemoreflex = Float64[]
	tauc = 2
	facmin = 1.16
	facmax = 17.07
	PO2n = 45
	kac = 29.27
	PaO2 = 95.0 #nominal pressure, reduce to induce hypoxia
	push!(chemoreflex, tauc)
	push!(chemoreflex, facmin)
	push!(chemoreflex, facmax)
	push!(chemoreflex, PO2n)
	push!(chemoreflex, kac)
	push!(chemoreflex, PaO2)

	pulmonaryStretch = Float64[]
	taup = 2
	Gap = 23.29
	push!(pulmonaryStretch,taup)
	push!(pulmonaryStretch, Gap)

	sympathetic = Float64[]
	fesinf = 2.1
	fes0 = 16.11
	fesmin = 2.66
	fesmax = 60
	kes = .0675
	Wbsp = 1
	Wcsp = 5
	Wpsp = .34
	Wbsh = 1
	Wcsh = 1
	push!(sympathetic, fesinf)
	push!(sympathetic, fes0)
	push!(sympathetic, fesmin)
	push!(sympathetic, fesmax)
	push!(sympathetic, kes)
	push!(sympathetic, Wbsp)
	push!(sympathetic, Wcsp)
	push!(sympathetic, Wpsp)
	push!(sympathetic, Wbsh)
	push!(sympathetic, Wcsh)

	vagal = Float64[]
	fevinf = 6.3
	fev0 = 3.2
	fab0 = 25
	kev = 7.07
	Wcv = .2
	Wpv = .103
	Thetav = -.68
	push!(vagal, fevinf)
	push!(vagal, fev0)
	push!(vagal, fab0)
	push!(vagal, kev)
	push!(vagal, Wcv)
	push!(vagal, Wpv)
	push!(vagal, Thetav)

	CNS = Float64[]
	ChiMaxsp = 13.32
	ChiMaxsh = 3.59
	tauisc = 30
	ChiMinsp = 7.33
	ChiMinsh = -49.38
	PO2nsp = 30
	PO2nsh = 45
	kiscsp = 2
	kiscsh = 6
	push!(CNS, ChiMaxsp)
	push!(CNS, ChiMaxsh)
	push!(CNS, tauisc)
	push!(CNS, ChiMinsp)
	push!(CNS, ChiMinsh)
	push!(CNS, PO2nsp)
	push!(CNS, PO2nsh)
	push!(CNS, kiscsp)
	push!(CNS, kiscsh)
	
	vetilatory=Float64[] 
	Gv = .125
	tauv = 3
	Dv =6
	VTn = .583
	facn = 3.6
	push!(vetilatory, Gv)
	push!(vetilatory, tauv)
	push!(vetilatory, Dv)
	push!(vetilatory, VTn)
	push!(vetilatory, facn)

	reflex=Float64[]
	GEmaxlv = .475
	GEmaxrv = .282
	GRsp =.695
	GRep = 1.94
	GRmp = 2.47
	GVusv= -265.4
	GVuev = -74.31
	GVumv = -58.29	
	GTs =-.13
	GTv = .09
	tauEmaxlv = 8
	tauEmaxrv = 8
	tauRsp = 6
	tauRep = 6
	tauRmp = 6
	tauVusv = 20
	tauVuev = 20
	tauVumv = 20
	tauTs = 2
	tauTv = 1.5
	DEmaxlv = 2
	DEmaxrv = 2
	DRsp = 2
	DRep = 2
	DRmp = 2
	DVusv = 5
	DVuev = 5
	DVumv = 5
	DTs = 2
	DTv = .2
	Emaxlv0 = 2.392
	Emaxrv0 = 1.412
	Rsp0 = 2.49
	Rep0 = 1.655
	Rmp0 = 2.106
	Vusv0 = 1435.4
	Vuev0 = 640.73
	Vumv0 =503.26
	T0 = .58
	push!(reflex, GEmaxlv)
	push!(reflex, GEmaxrv)
	push!(reflex, GRsp)
	push!(reflex, GRep)
	push!(reflex, GRmp)
	push!(reflex, GVusv)
	push!(reflex, GVuev)
	push!(reflex, GVumv)
	push!(reflex, GTs)
	push!(reflex, GTv)
	push!(reflex,tauEmaxlv)
	push!(reflex,tauEmaxrv)
	push!(reflex,tauRsp)
	push!(reflex,tauRep)
	push!(reflex, tauRmp)
	push!(reflex,tauVusv)
	push!(reflex,tauVuev)
	push!(reflex,tauVumv)
	push!(reflex,tauTs)
	push!(reflex,tauTv)
	push!(reflex,DEmaxlv)
	push!(reflex,DEmaxrv)
	push!(reflex,DRsp)
	push!(reflex,DRep)
	push!(reflex,DRmp)
	push!(reflex,DVusv)
	push!(reflex,DVuev)
	push!(reflex,DVumv)
	push!(reflex,DTs)
	push!(reflex,DTv)
	push!(reflex,Emaxlv0)
	push!(reflex,Emaxrv0)
	push!(reflex,Rsp0)
	push!(reflex,Rep0)
	push!(reflex,Rmp0)
	push!(reflex,Vusv0)
	push!(reflex,Vuev0)
	push!(reflex,Vumv0)
	push!(reflex,T0)	

	data_dictionary = Dict()
	data_dictionary["COMPLIANCE"] =compliance_array
	data_dictionary["UNSTRESSEDVOLUME"]= volume_array
	data_dictionary["RESISTANCE"] = resistance_array
	data_dictionary["INERTANCE"] = inhertance_array
	data_dictionary["HEART"] = heart_array
	data_dictionary["BASAL_HEART_PERIOD"] = .833
	data_dictionary["DVTERMS"] = dvTerms
	data_dictionary["BARROREFLEX"] = barroreflex
	data_dictionary["CHEMOREFLEX"] = chemoreflex
	data_dictionary["PULMONARY_STRETCH"]= pulmonaryStretch
	data_dictionary["SYMPATHETIC"]= sympathetic
	data_dictionary["VAGAL"] = vagal
	data_dictionary["CNS"] = CNS
	data_dictionary["VENTILATORY"] = vetilatory
	data_dictionary["REFLEX"] = reflex
	return data_dictionary	
end
