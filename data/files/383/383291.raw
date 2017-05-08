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
	
#	@show t
	# Correct nagative x's = throws errors in control even if small - 
	idx = find(x->(x<0),x);
	x[idx] = 0.0;

	idx = find(x->(abs(x)<1E-25),x); #lets make anything less than 1E-9 zero
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
##	
	# Alias the species -
	FII	 = x[1]
	FIIa	= x[2]
	PC	  = x[3]
	APC	 = x[4]
	ATIII   = x[5]
	TM	  = x[6]
	TRIGGER = x[7]
	Eps = x[8] #frac platelets acativated
	FV = x[9]
	FVa = x[10]
	FX=x[11]
	FXa = x[12]
	PROTHOMBINASE_PLATELETS = x[13] 

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
    initiation_TFPI_term = ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
    
    # Amplification model -
    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
    inhibition_term =  ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
    inhibition_term_TFPI =  ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
    #factor_product = FIX*FVIII*FV_FX/(nominal_FIX*nominal_FVIII*nominal_FV_X)
    #factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
    
    # Shutdown phase -
    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))


    #prothominabse complex formation
    activation_FV_by_thrombin = (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation)
    activation_FX_by_trigger = (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation)
    inhibition_term_ATIII=(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition)

    control_vector = ones(1,8)
    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term)
    control_vector[2] = min(inhibition_term,inhibition_term_ATIII)
    control_vector[3] = shutdown_term
    control_vector[4] = 1
    control_vector[5] = 1
    control_vector[6] = min(inhibition_term_TFPI, inhibition_term_ATIII)
    control_vector[7] = FVIII_control
    control_vector[8] = 1.0
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
    k_FV_activation = kinetic_parameter_vector[10]
    K_FV_activation = kinetic_parameter_vector[11]
    k_complex = kinetic_parameter_vector[12]
    k_amp_prothombinase = kinetic_parameter_vector[13]
    K_FII_amp_prothombinase=kinetic_parameter_vector[14]
    k_amp_FXa= kinetic_parameter_vector[15]
    K_amp_FXa = kinetic_parameter_vector[16]
    
	#@show FIIa, FII, PROTHOMBINASE_PLATELETS, FV_FXA
    rate_vector = zeros(1,8)
	rate_vector[1] = k_trigger*TRIGGER*(FX/(K_trigger + FX))
	rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
	rate_vector[3] = k_APC_formation*TM*((PC)/(K_PC_formation + PC))
	rate_vector[4] = (k_inhibition_ATIII)*(ATIII)*((FIIa)^1.26)
	rate_vector[5] = k_FV_activation*FIIa*(FV/(K_FV_activation+FV))
	rate_vector[6] = k_complex*FVa*FXa*aida/Eps
	rate_vector[7] = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
	rate_vector[8] = k_amp_FXa*FXa*FII/(K_amp_FXa+FII)

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
	#use cybernetic control on rates 7 and 8
#	@show modified_rate_vector[7], modified_rate_vector[8]
	if(modified_rate_vector[7]!=0.0 && modified_rate_vector[7]>modified_rate_vector[8]) #preventing dividing by zero
		modified_rate_vector[7] = modified_rate_vector[7]^2/(max(modified_rate_vector[7], modified_rate_vector[8]))
		modified_rate_vector[8]= modified_rate_vector[8]^2/(max(modified_rate_vector[7], modified_rate_vector[8]))
	end
	# calculate dxdt_reaction -
	dxdt_total = zeros(size(x,1),1)
	
	dxdt_total[1] = -1*modified_rate_vector[2] -modified_rate_vector[7]-modified_rate_vector[8]	# 1 FII
	dxdt_total[2] = modified_rate_vector[2] - modified_rate_vector[4]+modified_rate_vector[7]+modified_rate_vector[8]	 # 2 FIIa
	dxdt_total[3] = -1*modified_rate_vector[3] # 3 PC
	dxdt_total[4] = 1*modified_rate_vector[3]  # 4 APC
	dxdt_total[5] = -1*modified_rate_vector[4]# 5 ATIII
	dxdt_total[6] = 0.0 # 6 TM (acts as enzyme, so no change)
	dxdt_total[7] = -0.0*TRIGGER	# 7 TRIGGER
	dxdt_total[8] = kplatelts*(EpsMax-Eps)-koffplatelets*Eps#-rate_vector[5] #frac active platelets
	dxdt_total[9] = -1*modified_rate_vector[5] #FV
	dxdt_total[10] = modified_rate_vector[5]-modified_rate_vector[6]#FVa
	dxdt_total[11] = -modified_rate_vector[1] #FX
	dxdt_total[12] = modified_rate_vector[1]-modified_rate_vector[6] #FXa
	dxdt_total[13] = modified_rate_vector[6]

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
	idx = find(dxdt_total->(abs(dxdt_total)<1E-25),dxdt_total); #lets make anything less than 1E-9 zero
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


