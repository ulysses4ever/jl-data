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
	push!(volume_array, Vusa)
	push!(volume_array, Vusp)
	push!(volume_array, Veup)
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

	data_dictionary = Dict()
	data_dictionary["COMPLIANCE"] =compliance_array
	data_dictionary["UNSTRESSEDVOLUME"]= volume_array
	data_dictionary["RESISTANCE"] = resistance_array
	data_dictionary["INERTANCE"] = inhertance_array
	data_dictionary["HEART"] = heart_array
	data_dictionary["BASAL_HEART_PERIOD"] = .833
	return data_dictionary	
end
