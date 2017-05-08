function BalanceEquations(t,x,PROBLEM_DICTIONARY)
	
	#@show t
	# Correct nagative x's = throws errors in control even if small - 
	idx = find(x->(x<0),x);
	x[idx] = 0.0;
#	for j = 1:length(x)
#		if(isnan(x[j]) || !isfinite(x[j]))
#			println("Found NAN at x $j")
#			x[j] = 0.0
#		end
#	end
	
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
	p = PROBLEM_DICTIONARY["p"]
	qualitative_factor_level_vector = PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"]
	p = PROBLEM_DICTIONARY["PLATELET_PARAMS"]
	timing = PROBLEM_DICTIONARY["TIME_DELAY"]

#@showp
#@show typeof(kinetic_parameter_vector)

	# Alias the qualitative factors -
	TFPI = qualitative_factor_level_vector[1]
	#FV = qualitative_factor_level_vector[2]
	FVIII = qualitative_factor_level_vector[3]
	FIX = qualitative_factor_level_vector[4]
	#FX = qualitative_factor_level_vector[5]
	PL = qualitative_factor_level_vector[6]

	# Calculate the control vector -
	# Trigger -
	alpha_trigger_activation = p[1]
	order_trigger_activation = p[2]
	alpha_trigger_inhibition_APC = p[3]
	order_trigger_inhibition_APC = p[4]
	alpha_trigger_inhibition_TFPI = p[5]
	order_trigger_inhibition_TFPI = p[6]
	
	# Amplification -
	alpha_amplification_FIIa = p[7]
	order_amplification_FIIa = p[8]
	alpha_amplification_APC = p[9]
	order_amplification_APC = p[10]
	alpha_amplification_TFPI = p[11]
	order_amplification_TFPI = p[12]
	
	# APC generation -
	alpha_shutdown_APC = p[13]
	order_shutdown_APC = p[14]

	#prothomibase complex
	alpha_FV_activation=p[15]
	order_FV_activation=p[16]
 	alpha_FX_activation=p[17]
    	order_FX_activation=p[18]
        alpha_FX_inhibition=p[19]
        order_FX_inhibition=p[20]
	
	#platelets
	kplatelts = p[1]#1 rate constant
	platelet_pwr = p[2] #2 power for control function
	platelet_denom = p[3] #3 adjustment in denominator
	EpsMax0 = p[4] #4 Epsmax0
	aida = p[5] #5 aida
	koffplatelets = p[6]

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

    control_vector = ones(1,7)
    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term, inhibition_term)
    control_vector[2] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[3] = shutdown_term
    control_vector[4] = 1
    control_vector[5] = 1
    control_vector[6] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[7] = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)
		#@show control_vector[5], activation_FV_by_thrombin, activation_FX_by_trigger, inhibition_of_FX_by_ATIII

    # Calculate the kinetics -
    k_trigger =p[1]
    K_trigger =p[2]
    k_amplification =p[3]
    K_FII_amplification =p[4]
    k_APC_formation =p[5]
    K_PC_formation =p[6]
    k_inhibition =p[7]
    K_FIIa_inhibition =p[8]
    k_inhibition_ATIII =p[9]
    k_FV_X_activation =p[10]
    K_FV_X_actiation =p[11]
    #k_FX_activation =p[12]
    #K_FX_activation =p[13]
    k_complex =p[14]
    k_amp_prothombinase =p[15]
    K_FII_amp_prothombinase=kinetic_parameter_vector[16]
    k_amp_active_factors=p[17]
    K_amp_active_factors =p[18]	
    
#@showp
    rate_vector = zeros(1,7)
	#if(t>time_delay)
	    rate_vector[1] = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
	    rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
	    rate_vector[3] = k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC))
	    #rate_vector[3] = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
	    rate_vector[4] = Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26)
	    rate_vector[5] = k_complex*FV_FXA*aida/Eps
	    rate_vector[6] = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
	    rate_vector[7] = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)
	#end
#	f = open("ratevector.txt", "a+")
#	writedlm(f, rate_vector)
#	close(f)

	#@show t, x, rate_vector, control_vector
	#remove nans
	for j = 1:length(rate_vector)
		if(isnan(rate_vector[j]) || !isfinite(rate_vector[j]))
			println("Found NAN at rate_vector $j")
			rate_vector[j] = 0.0
		end
	end

	#remove nans
	for j = 1:length(control_vector)
		if(isnan(control_vector[j])|| !isfinite(control_vector[j]))
			println("Found NAN at control_vector $j")
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
	dxdt_total[10] = modified_rate_vector[1] -rate_vector[5]#FV_FXa
	dxdt_total[11] = modified_rate_vector[5] #Prothromibase_platelets

	idx = find(x->(x<0),x);
	x[idx] = 0.0;
	dxdt_total[idx]= 0.0


	tau = time_coeff*(1-FIIa/aleph)
	time_scale =1-1*exp(-tau*(t-time_delay))
	if(t<time_delay)
		time_scale = 0.0
	end
	if(isnan(time_scale))
		time_scale = 1.0
	end
	#@show dxdt_total.*time_scale
	#@show convert(Array{Float64,2},dxdt_total.*time_scale)
	return (dxdt_total.*time_scale)
	#@show t
	#return convert(Array{Float64,2},dxdt_total.*time_scale)

end

function BalanceEquationsDE(t,x,p,dx)
	#@show t
	# Correct nagative x's = throws errors in control even if small - 
	idx = find(x->(x<0),x);
	x[idx] = 0.0;
	
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
	if(FIIa>PROBLEM_DICTIONARY["ALEPH"])
		PROBLEM_DICTIONARY["ALEPH"]=FIIa
	end

	aleph = PROBLEM_DICTIONARY["ALEPH"]
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

    control_vector = ones(1,7)
    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term, inhibition_term)
    control_vector[2] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[3] = shutdown_term
    control_vector[4] = 1
    control_vector[5] = 1
    control_vector[6] = min(inhibition_term,inhibition_term_TFPI)
    control_vector[7] = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)
		#@show control_vector[5], activation_FV_by_thrombin, activation_FX_by_trigger, inhibition_of_FX_by_ATIII

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
    #k_FX_activation =p[46]
    #K_FX_activation =p[47]
    k_complex =p[48]
    k_amp_prothombinase =p[49]
    K_FII_amp_prothombinase=kinetic_parameter_vector[50]
    k_amp_active_factors=p[51]
    K_amp_active_factors =p[52]	
    
#@showp
    rate_vector = zeros(1,7)
	#if(t>time_delay)
	    rate_vector[1] = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
	    rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
	    rate_vector[3] = k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC))
	    #rate_vector[3] = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
	    rate_vector[4] = Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26)
	    rate_vector[5] = k_complex*FV_FXA*aida/Eps
	    rate_vector[6] = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
	    rate_vector[7] = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)
	#end
#	f = open("ratevector.txt", "a+")
#	writedlm(f, rate_vector)
#	close(f)

	#@show t, x, rate_vector, control_vector
	#remove nans
	for j = 1:length(rate_vector)
		if(isnan(rate_vector[j]) || !isfinite(rate_vector[j]))
			println("Found NAN at rate_vector $j")
			rate_vector[j] = 0.0
		end
	end

	#remove nans
	for j = 1:length(control_vector)
		if(isnan(control_vector[j])|| !isfinite(control_vector[j]))
			println("Found NAN at control_vector $j")
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
	dxdt_total[10] = modified_rate_vector[1] -rate_vector[5]#FV_FXa
	dxdt_total[11] = modified_rate_vector[5] #Prothromibase_platelets

	idx = find(x->(x<0),x);
	x[idx] = 0.0;
	dxdt_total[idx]= 0.0


	tau = time_coeff*(1-FIIa/aleph)
	time_scale =1-1*exp(-tau*(t-time_delay))
	if(t<time_delay)
		time_scale = 0.0
	end
	if(isnan(time_scale))
		time_scale = 1.0
	end
	#@show dxdt_total.*time_scale
	#@show convert(Array{Float64,2},dxdt_total.*time_scale)
	dx=(dxdt_total.*time_scale)
	

end
