include("DataFile.jl")

function complexHeartModel(t,y,data_dict)
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
	Psi = y[14]
	Pra = y[15]
	Vrv = y[16]

	#unpack data dictionary
	volumes = data_dict["UNSTRESSEDVOLUME"]
	resistances = data_dict["RESISTANCE"]
	compliances = data_dict["COMPLIANCE"]
	inertances = data_dict["INERTANCE"]
	heart = data_dict["HEART"]
	T = data_dictionary["BASAL_HEART_PERIOD"]
	
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

	#conversation of mass

	Vu = Vusa +Vusp +Vuep+Vump + Vubp+Vuhp+Vusv+Vuev+Vumv+Vubv+Vuhv+Vura+Vupa+Vupp+Vupv+Vula#eqn 13
	Pev = 1/Cev*(Vtot-Csa*Psa-(Csp+Cep+Cmp+Cbp+Chp)*Psp-Csv*Psc -Cmv*Pmv -Cbv*Pbv-Chv*Phv-Cra*Pra-Vrv-Cpa*Vpa-Cpp*Vpp-Cpv*Ppv-Cla*Pla-Vlv-Vu)#eqn 12


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

	#heart as a pump, left side
	if(Plv>=Pla)
		Fil = 0.0
	else
		Fil = (Pla-Plv)/Rla
	end

	Rlv = krlv*Pmaxlv
	if(Pmaxlv<=Psa)
		Fol = 0.0
	else
		Fol = (Pmaxlv-Psa)/Rlv
	end

	dPladt = 1/Cla*((Ppv-Pla)/Rpv-Fil)
	dVlvdt = Fil-Fol
	Plv = Pmaxlv - Rlv*Fol

	Tsys = Tsys0-ksys*1/T
	dPsidt = 1/T
	if(Psi >1) #reset, equvalent to frac
		Psi = 0.0
	end
	
	if(u >= 0 && u<=Tsys/T)
		phi = sin(pi*T*u/Tsys)^2
	elseif(u>=Tsys/T && and u<=1)
		phi = 0.0
	end

	Pmaxlv = phi*Emaxlv*(Vlv*Vulv)+(1-phi)*P0lv*(exp(kelv*Vlv)-1)
	#heart as a pump, right side
	if(Pra<=Prv)
		Fir = 0.0
	else
		Fir = (Pra-Prv)/Rra
	end

	if(Pmaxrv<=Ppa)
		For=0.0
	else
		For=(Pmaxrv-Ppa)/Rrv
	end
	dPradt = 1/Cra*((Psv-Pra)/Rsv+(Pev-Pra)/Rev-Fir)
	dVrvdt = Fir-For
	Rrv = krrv*Pmaxrv
	Pmaxrv = phi*Emaxrv*(Vrv-Vurv) + (1-phi)*P0rv*exp(kerv*Vrv)-1)

	Rrv = Pmaxrv-Rrv*For

end

function main()
	t = collect(0:1:60)
	data_dict = DataFile()
	fedeqns(t,y)= complexHeartModel(t,y,data_dict)
	tout, res = ODE.ode45(fedeqns, initial_conditions, t, reltol = 6E-4, abstol =1E-4, points=:specified)
end
