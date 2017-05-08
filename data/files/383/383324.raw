function AdjBalanceEquations(t,x,parameter_index, data_dictionary)
	@show t
	number_of_states = 11
	#partition
	state_array = x[1:number_of_states]
	sensitivity_array = x[(number_of_states+1):end]
	dxdt_array = BalanceEquations(t,state_array, data_dictionary)

	#calculate sensitivity states
	local_data_dictionary = deepcopy(data_dictionary)
	JM = calculate_jacobian(t,state_array, local_data_dictionary)
	BM = calculate_bmatrix(t, state_array, local_data_dictionary)
#	@show size(JM), size(BM), size(sensitivity_array)
	dsdt_array = JM*sensitivity_array+BM[:, parameter_index]
	r_array = [dxdt_array; dsdt_array]
	return r_array

end


function BalanceEquations(t,x,PROBLEM_DICTIONARY)
	
	#@show t
	# Correct nagative x's = throws errors in control even if small - 
	idx = find(x->(x<0),x);
	x[idx] = 0.0;

	idx = find(x->(abs(x)<1E-15),x); #lets make anything less than 1E-9 zero
	#@show idx
	x[idx] = 0.0;
#	for j = 1:length(x)
#		if(isnan(x[j]) || !isfinite(x[j]))
#			println("Found NAN at x $j")
#			@show t
#			@show x
#			@show PROBLEM_DICTIONARY
#			#quit()
#			x[j] = 0.0
#		end
#	end
#	
	# Alias the species -
	FII	 = x[1]
	FIIa	= x[2]
	PC	  = x[3]
	APC	 = x[4]
	ATIII   = x[5]
	TM	  = x[6]
	TRIGGER = x[7]
	Eps = x[8] #frac platelets acativated
	FV_FX = x[9]
	FV_FXA = x[10]
	PROTHOMBINASE_PLATELETS = x[11] 

	# Grab the kinetic parameetrs from the problem dictionary -
	kinetic_parameter_vector = PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"]
	control_parameter_vector = PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"]
	qualitative_factor_level_vector = PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"]
	platelet_parameter_vector = PROBLEM_DICTIONARY["PLATELET_PARAMS"]
	timing = PROBLEM_DICTIONARY["TIME_DELAY"]

	# Alias the qualitative factors -
	TFPI = qualitative_factor_level_vector[1]
	#FV = qualitative_factor_level_vector[2]
	FVIII = qualitative_factor_level_vector[3]
	FIX = qualitative_factor_level_vector[4]
	#FX = qualitative_factor_level_vector[5]
	Platelets = qualitative_factor_level_vector[6]

	alpha_trigger_activation = control_parameter_vector[1]
	order_trigger_activation = control_parameter_vector[2]
	alpha_trigger_inhibition_APC = control_parameter_vector[3]
	order_trigger_inhibition_APC = control_parameter_vector[4]
	alpha_trigger_inhibition_TFPI = control_parameter_vector[5]
	order_trigger_inhibition_TFPI = control_parameter_vector[6]
	
	# Amplification -
	alpha_amplification_FIIa = control_parameter_vector[7]
	order_amplification_FIIa = control_parameter_vector[8]
	alpha_amplification_APC = control_parameter_vector[9]
	order_amplification_APC = control_parameter_vector[10]
	alpha_amplification_TFPI = control_parameter_vector[11]
	order_amplification_TFPI = control_parameter_vector[12]
	
	# APC generation -
	alpha_shutdown_APC = control_parameter_vector[13]
	order_shutdown_APC = control_parameter_vector[14]

	#prothomibase complex
	alpha_FV_activation=control_parameter_vector[15]
	order_FV_activation=control_parameter_vector[16]
 	alpha_FX_activation=control_parameter_vector[17]
    	order_FX_activation=control_parameter_vector[18]
        alpha_FX_inhibition=control_parameter_vector[19]
        order_FX_inhibition=control_parameter_vector[20]
	
	#platelets
	kplatelts = platelet_parameter_vector[1]#1 rate constant
	platelet_pwr = platelet_parameter_vector[2] #2 power for control function
	platelet_denom = platelet_parameter_vector[3] #3 adjustment in denominator
	EpsMax0 = platelet_parameter_vector[4] #4 Epsmax0
	aida = platelet_parameter_vector[5] #5 aida
	koffplatelets = platelet_parameter_vector[6]

#	#nominal_levels
#	nominal_TFPI = nominal_levels[1]
#	nominal_FVIII = nominal_levels[2]
#	nominal_FIX = nominal_levels[3]
#	nominal_FV_X = nominal_levels[4]

	#FVIII function
	FVIII_control = PROBLEM_DICTIONARY["FVIII_CONTROL"]

	#platelet control
	#update aleph so that it holds the maximum value of FIIa
	if(FIIa>PROBLEM_DICTIONARY["ALEPH"])
		PROBLEM_DICTIONARY["ALEPH"]=FIIa
	end

	aleph = PROBLEM_DICTIONARY["ALEPH"]
	faleph = aleph^platelet_pwr/(aleph^platelet_pwr + platelet_denom^platelet_pwr)
	EpsMax = EpsMax0+(1+EpsMax0)*faleph

	#timing
	time_delay = timing[1]
	time_coeff = timing[2]

	# Initiation model -
    initiation_trigger_term = ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation))
    initiation_TFPI_term = 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
    
    # Amplification model -
    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
    inhibition_term =  ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
    inhibition_term_TFPI =  ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
    factor_product = FIX*FVIII*FV_FX/(nominal_FIX*nominal_FVIII*nominal_FV_X)
    factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
    
    # Shutdown phase -
    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))


    #prothominabse complex formation
    activation_FV_by_thrombin = (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation)
    activation_FX_by_trigger = (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation)
    inhibition_of_FX_by_ATIII=1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition)

    control_vector = ones(1,7)
    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term)
    control_vector[2] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[3] = shutdown_term
    control_vector[4] = 1
    control_vector[5] = 1
    #control_vector[6] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[6] = FVIII_control
    control_vector[7] = min(1-max(inhibition_term,inhibition_term_TFPI))
	#@show control_vector[1], initiation_trigger_term, initiation_TFPI_term, inhibition_term

    # Calculate the kinetics -
    k_trigger = kinetic_parameter_vector[1]
    K_trigger = kinetic_parameter_vector[2]
    k_amplification = kinetic_parameter_vector[3]
    K_FII_amplification = kinetic_parameter_vector[4]
    k_APC_formation = kinetic_parameter_vector[5]
    K_PC_formation = kinetic_parameter_vector[6]
    k_inhibition = kinetic_parameter_vector[7]
    K_FIIa_inhibition = kinetic_parameter_vector[8]
    k_inhibition_ATIII = kinetic_parameter_vector[9]
    k_FV_X_activation = kinetic_parameter_vector[10]
    K_FV_X_actiation = kinetic_parameter_vector[11]
    #k_FX_activation = kinetic_parameter_vector[12]
    #K_FX_activation = kinetic_parameter_vector[13]
    k_complex = kinetic_parameter_vector[14]
    k_amp_prothombinase = kinetic_parameter_vector[15]
    K_FII_amp_prothombinase=kinetic_parameter_vector[16]
    k_amp_active_factors= kinetic_parameter_vector[17]
    K_amp_active_factors = kinetic_parameter_vector[18]
    
	#@show FIIa, FII, PROTHOMBINASE_PLATELETS, FV_FXA
    rate_vector = zeros(1,7)
	rate_vector[1] = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
	rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
	rate_vector[3] = k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC))
	rate_vector[4] = Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26)
	rate_vector[5] = k_complex*FV_FXA*aida/Eps
	rate_vector[6] = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
	rate_vector[7] = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)

	for j in collect(1:length(rate_vector))
		if(isnan(rate_vector[j]) || !isfinite(rate_vector[j]))
		#	println("Found NAN at rate_vector $j")
			rate_vector[j] = 0.0
		end
	end

	#remove nans
	for j in collect(1:length(rate_vector))
		if(isnan(control_vector[j])|| !isfinite(control_vector[j]))
		#	println("Found NAN at control_vector $j")
			control_vector[j] = 1.0
		end
	end

	 # modified rate vector -
	modified_rate_vector = (rate_vector).*(control_vector);
#	f = open("modifiedratevector.txt", "a+")
#	writedlm(f, modified_rate_vector)
#	close(f)

#	f = open("times.txt", "a+")
#	writedlm(f, t)
#	close(f)

#	f = open("ratevector.txt", "a+")
#	writedlm(f, rate_vector)
#	close(f)

	# calculate dxdt_reaction -
	dxdt_total = zeros(size(x,1),1)
	
	dxdt_total[1] = -1*modified_rate_vector[2] -modified_rate_vector[7]-modified_rate_vector[6]	# 1 FII
	dxdt_total[2] = modified_rate_vector[2] - modified_rate_vector[4]+modified_rate_vector[7]+modified_rate_vector[6]	 # 2 FIIa
	dxdt_total[3] = -1*modified_rate_vector[3] # 3 PC
	dxdt_total[4] = 1*modified_rate_vector[3]  # 4 APC
	dxdt_total[5] = -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26)# 5 ATIII
	dxdt_total[6] = 0.0 # 6 TM (acts as enzyme, so no change)
	dxdt_total[7] = -0.0*TRIGGER	# 7 TRIGGER
	dxdt_total[8] = kplatelts*(EpsMax-Eps)-koffplatelets*Eps#-rate_vector[5] #frac active platelets
	#dxdt_total[8] = 0.0 #if no platelets, they can't be activated
	dxdt_total[9] = -1*modified_rate_vector[1] #FV_FX
	dxdt_total[10] = modified_rate_vector[1] -modified_rate_vector[5]#FV_FXa
	dxdt_total[11] = modified_rate_vector[5] #Prothromibase_platelets

	idx = find(x->(x<0),x);
	x[idx] = 0.0;
	dxdt_total[idx]= 0.0


	tau = time_coeff*(1-FIIa/aleph)
	time_scale =1-1*exp(-tau*(t-time_delay))
	#@show t
	if(t<time_delay)
		time_scale = 0.0
	end
	if(isnan(time_scale))
		time_scale = 1.0
	end
	#@show dxdt_total
	idx = find(dxdt_total->(abs(dxdt_total)<1E-15),dxdt_total); #lets make anything less than 1E-9 zero
	#@show idx
	dxdt_total[idx] = 0.0;

	dxdt_total = dxdt_total.*time_scale
#	dxdt_total[1:7]=dxdt_total[1:7].*time_scale
#	dxdt_total[9:end]=dxdt_total[9:end].*time_scale
#	@show x
#	@show control_vector
#	@show rate_vector
#	@show modified_rate_vector
#	@show dxdt_total
	 return dxdt_total

end

function BalanceEquationsDE_f(t,u,p,du)
	#@show t
	# Correct nagative x's = throws errors in control even if small - 
	idx = find(u->(u<0),u);
	#u[idx] = 0.0;
	t = extractValueFromDual(t)
	
	@show t
	@show u
	@show p
	@show du
	#kludge
#	if(size(u,1)!=11)
#		u = zeros(1,11)
#	end
	FII	 = u[1]
	FIIa	= u[2]
	PC	  = u[3]
	APC	 = u[4]
	ATIII   = u[5]
	TM	  = u[6]
	TRIGGER = u[7]
	Eps = u[8] #frac platelets acativated
	FV_FX = u[9]
	FV_FXA = u[10]
	PROTHOMBINASE_PLATELETS = u[11] 

	# Alias the qualitative factors -
	TFPI = p[1]
	#FV = p[2]
	FVIII = p[3]
	FIX = p[4]
	#FX =p[5]
	PL = p[6]

	# Calculate the control vector -
	# Trigger -
	alpha_trigger_activation =p[7]
	order_trigger_activation = p[8]
	alpha_trigger_inhibition_APC = p[9]
	order_trigger_inhibition_APC = p[10]
	alpha_trigger_inhibition_TFPI = p[11]
	order_trigger_inhibition_TFPI = p[12]
	
	# Amplification -
	alpha_amplification_FIIa = p[13]
	order_amplification_FIIa = p[14]
	alpha_amplification_APC = p[15]
	order_amplification_APC = p[16]
	alpha_amplification_TFPI = p[17]
	order_amplification_TFPI = p[18]
	
	# APC generation -
	alpha_shutdown_APC = p[19]
	order_shutdown_APC = p[20]

	#prothomibase complex
	alpha_FV_activation=p[21]
	order_FV_activation=p[22]
 	alpha_FX_activation=p[23]
    	order_FX_activation=p[24]
        alpha_FX_inhibition=p[25]
        order_FX_inhibition=p[26]
	
	#platelets
	kplatelts = p[27]#1 rate constant
	platelet_pwr = p[28] #2 power for control function
	platelet_denom = p[29] #3 adjustment in denominator
	EpsMax0 = p[30] #4 Epsmax0
	aida = p[31] #5 aida
	koffplatelets = p[32]

	#platelet control
	#update aleph so that it holds the maximum value of FIIa
	#now stored in p_53
	if(FIIa>p[53])
		p[53]=FIIa
	end

	aleph = p[53]
	faleph = aleph^platelet_pwr/(aleph^platelet_pwr + platelet_denom^platelet_pwr)
	EpsMax = EpsMax0+(1+EpsMax0)*faleph

	#timing
	time_delay = p[33]
	time_coeff = p[34]

	# Initiation model -
    initiation_trigger_term = ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation))
    initiation_TFPI_term = 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
    
    # Amplification model -
    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
    inhibition_term = 1 - ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
    inhibition_term_TFPI = 1 - ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
    factor_product = FIX*FVIII*FV_FX
    factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
    
    # Shutdown phase -
    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))

    #prothominabse complex formation
    activation_FV_by_thrombin = (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation)
    activation_FX_by_trigger = (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation)
    inhibition_of_FX_by_ATIII=1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition)

    control_vector_1 = min(initiation_trigger_term,initiation_TFPI_term, inhibition_term)
    control_vector_2 = min(inhibition_term,inhibition_term_TFPI)
    control_vector_3 = shutdown_term
    control_vector_4 = 1
    control_vector_5 = 1
    control_vector_6 = min(inhibition_term,inhibition_term_TFPI)
    control_vector_7 = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)

    # Calculate the kinetics -
    k_trigger =p[35]
    K_trigger =p[36]
    k_amplification =p[37]
    K_FII_amplification =p[38]
    k_APC_formation =p[39]
    K_PC_formation =p[40]
    k_inhibition =p[41]
    K_FIIa_inhibition =p[42]
    k_inhibition_ATIII =p[43]
    k_FV_X_activation =p[44]
    K_FV_X_actiation =p[45]
    #k_FX_activation =p_46
    #K_FX_activation =p_47
    k_complex =p[48]
    k_amp_prothombinase =p[49]
    K_FII_amp_prothombinase=p[50]
    k_amp_active_factors=p[51]
    K_amp_active_factors =p[52]	
    
	rate_vector_1 = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
	rate_vector_2 = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
	rate_vector_3 = k_APC_formation*TM*((PC)/(K_PC_formation + PC))
	#rate_vector_3 = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
	rate_vector_4 = (k_inhibition_ATIII)*(ATIII)*((FIIa)^1.26)
	rate_vector_5 = k_complex*FV_FXA*aida/Eps
	rate_vector_6 = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
	rate_vector_7 = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)


	modified_rate_vector_1 = rate_vector_1*control_vector_1
	modified_rate_vector_2 = rate_vector_2*control_vector_2
	modified_rate_vector_3 = rate_vector_3*control_vector_3
	modified_rate_vector_4 = rate_vector_4*control_vector_4
	modified_rate_vector_5 = rate_vector_5*control_vector_5
	modified_rate_vector_6 = rate_vector_6*control_vector_6
	modified_rate_vector_7 = rate_vector_7*control_vector_7
	
	du[1] = -1*modified_rate_vector_2 -modified_rate_vector_7-modified_rate_vector_6	# 1 FII
	du[2] = modified_rate_vector_2 - modified_rate_vector_4+modified_rate_vector_7+modified_rate_vector_6	 # 2 FIIa
	du[3] = -1*modified_rate_vector_3 # 3 PC
	du[4] = 1*modified_rate_vector_3  # 4 APC
	du[5] = -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26)# 5 ATIII
	du[6] = 0.0 # 6 TM (acts as enzyme, so no change)
	du[7] = -0.0*TRIGGER	# 7 TRIGGER
	du[8] = kplatelts*(EpsMax-Eps)-koffplatelets*Eps#-rate_vector_5 #frac active platelets
	#temp_dx_8 = 0.0 #if no platelets, they can't be activated
	du[9] = -1*modified_rate_vector_1 #FV_FX
	du[10] = modified_rate_vector_1 -rate_vector_5#FV_FXa
	du[11] = modified_rate_vector_5 #Prothromibase_platelets
	idx = find(u->(u<0),u);
	u[idx] = 0.0;
	du[idx]=0.0

	tau = time_coeff*(1-FIIa/aleph)
	time_scale =1-1*exp(-tau*(t-time_delay))
	time_scale =1.0
	if(t<time_delay)
		time_scale = 0.0
		#println("less than start time")
	end
	if(isnan(time_scale))
		time_scale = 1.0
	end
		
	du = du*time_scale
	@show du
	du

end

function balance_equations_using_ode_macro(params)

	f= ParameterizedFunctions.ode_def_opts(:BalanceEquations_DE,Dict{Symbol,Bool}(
	    :build_tgrad => true,
	    :build_jac => true,
	    :build_expjac => false,
	    :build_invjac => true,
	    :build_invW => true,
	    :build_hes => true,
	    :build_invhes => true,
	    :build_dpfuncs => true),:(begin
		#@show t
		# Correct nagative x's = throws errors in control even if small - 
#		idx = find(u->(u<0),u);
#		u[idx] = 0.0;
		t = extractValueFromDual(t)
	
		FII	 = u[1]
		FIIa	= u[2]
		PC	  = u[3]
		APC	 = u[4]
		ATIII   = u[5]
		TM	  = u[6]
		TRIGGER = u[7]
		Eps = u[8] #frac platelets acativated
		FV_FX = u[9]
		FV_FXA = u[10]
		PROTHOMBINASE_PLATELETS = u[11] 

			# Alias the qualitative factors -
		TFPI = p_1
		#FV = p_2
		FVIII = p_3
		FIX = p_4
		#FX =p_5
		PL = p_6

		# Calculate the control vector -
		# Trigger -
		alpha_trigger_activation =p_7
		order_trigger_activation = p_8
		alpha_trigger_inhibition_APC = p_9
		order_trigger_inhibition_APC = p_10
		alpha_trigger_inhibition_TFPI = p_11
		order_trigger_inhibition_TFPI = p_12
	
		# Amplification -
		alpha_amplification_FIIa = p_13
		order_amplification_FIIa = p_14
		alpha_amplification_APC = p_15
		order_amplification_APC = p_16
		alpha_amplification_TFPI = p_17
		order_amplification_TFPI = p_18
	
		# APC generation -
		alpha_shutdown_APC = p_19
		order_shutdown_APC = p_20

		#prothomibase complex
		alpha_FV_activation=p_21
		order_FV_activation=p_22
	 	alpha_FX_activation=p_23
	    	order_FX_activation=p_24
		alpha_FX_inhibition=p_25
		order_FX_inhibition=p_26
	
		#platelets
		kplatelts = p_27#1 rate constant
		platelet_pwr = p_28 #2 power for control function
		platelet_denom = p_29 #3 adjustment in denominator
		EpsMax0 = p_30 #4 Epsmax0
		aida = p_31 #5 aida
		koffplatelets = p_32

		#platelet control
		#update aleph so that it holds the maximum value of FIIa
		#now stored in p_53
		if(FIIa>p_53)
			p_53=FIIa
		end

		aleph = p_53
		faleph = aleph^platelet_pwr/(aleph^platelet_pwr + platelet_denom^platelet_pwr)
		EpsMax = EpsMax0+(1+EpsMax0)*faleph

		#timing
		time_delay = p_33
		time_coeff = p_34
		# Initiation model -
	    initiation_trigger_term = ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation))
	    initiation_TFPI_term = 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
	    
	    # Amplification model -
	    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
	    inhibition_term = 1 - ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
	    inhibition_term_TFPI = 1 - ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
	    factor_product = FIX*FVIII*FV_FX
	    factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
	    
	    # Shutdown phase -
	    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))

	    #prothominabse complex formation
	    activation_FV_by_thrombin = (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation)
	    activation_FX_by_trigger = (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation)
	    inhibition_of_FX_by_ATIII=1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition)

	    control_vector_1 = min(initiation_trigger_term,initiation_TFPI_term, inhibition_term)
	    control_vector_2 = min(inhibition_term,inhibition_term_TFPI)
	    control_vector_3 = shutdown_term
	    control_vector_4 = 1
	    control_vector_5 = 1
	    control_vector_6 = min(inhibition_term,inhibition_term_TFPI)
	    control_vector_7 = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)

	    # Calculate the kinetics -
	    k_trigger =p_35
	    K_trigger =p_36
	    k_amplification =p_37
	    K_FII_amplification =p_38
	    k_APC_formation =p_39
	    K_PC_formation =p_40
	    k_inhibition =p_41
	    K_FIIa_inhibition =p_42
	    k_inhibition_ATIII =p_43
	    k_FV_X_activation =p_44
	    K_FV_X_actiation =p_45
	    #k_FX_activation =p_46
	    #K_FX_activation =p_47
	    k_complex =p_48
	    k_amp_prothombinase =p_49
	    K_FII_amp_prothombinase=p_50
	    k_amp_active_factors=p_51
	    K_amp_active_factors =p_52

		rate_vector_1 = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
		rate_vector_2 = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
		rate_vector_3 = k_APC_formation*TM*((PC)/(K_PC_formation + PC))
		#rate_vector_3 = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
		rate_vector_4 = (k_inhibition_ATIII)*(ATIII)*((FIIa)^1.26)
		rate_vector_5 = k_complex*FV_FXA*aida/Eps
		rate_vector_6 = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
		rate_vector_7 = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)


		modified_rate_vector_1 = rate_vector_1*control_vector_1
		modified_rate_vector_2 = rate_vector_2*control_vector_2
		modified_rate_vector_3 = rate_vector_3*control_vector_3
		modified_rate_vector_4 = rate_vector_4*control_vector_4
		modified_rate_vector_5 = rate_vector_5*control_vector_5
		modified_rate_vector_6 = rate_vector_6*control_vector_6
		modified_rate_vector_7 = rate_vector_7*control_vector_7
	
		du[1] = -1*modified_rate_vector_2 -modified_rate_vector_7-modified_rate_vector_6	# 1 FII
		du[2] = modified_rate_vector_2 - modified_rate_vector_4+modified_rate_vector_7+modified_rate_vector_6	 # 2 FIIa
		du[3] = -1*modified_rate_vector_3 # 3 PC
		du[4] = 1*modified_rate_vector_3  # 4 APC
		du[5] = -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26)# 5 ATIII
		du[6] = 0.0 # 6 TM (acts as enzyme, so no change)
		du[7] = -0.0*TRIGGER	# 7 TRIGGER
		du[8] = kplatelts*(EpsMax-Eps)-koffplatelets*Eps#-rate_vector_5 #frac active platelets
		#temp_dx_8 = 0.0 #if no platelets, they can't be activated
		du[9] = -1*modified_rate_vector_1 #FV_FX
		du[10] = modified_rate_vector_1 -rate_vector_5#FV_FXa
		du[11] = modified_rate_vector_5 #Prothromibase_platelets
		idx = find(u->(u<0),u);
		u[idx] = 0.0;
		du[idx]=0.0

		tau = time_coeff*(1-FIIa/aleph)
		time_scale =1-1*exp(-tau*(t-time_delay))
		if(t<time_delay)
			time_scale = 0.0
	#		#println("less than start time")
		end
		if(isnan(time_scale))
			time_scale = 1.0
		end
		
		du = du*time_scale
	end), params...) 
	return f
end
