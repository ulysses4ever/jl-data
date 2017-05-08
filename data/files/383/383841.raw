function BalanceEquations(t,x,PROBLEM_DICTIONARY)
    
    #print "Time - ",str(t)
    
    # initialize -
    dxdt_total = ones(1,7)
    
    # Alias the species -
    FII     = x[1]
    FIIa    = x[2]
    PC      = x[3]
    APC     = x[4]
    ATIII   = x[5]
    TM      = x[6]
    TRIGGER = x[7]
    
    # Grab the kinetic parameetrs from the problem dictionary -
    kinetic_parameter_vector = PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"]
    control_parameter_vector = PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"]
    qualitative_factor_level_vector = PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"]

#@show kinetic_parameter_vector
#@show typeof(kinetic_parameter_vector)

    # Alias the qualitative factors -
    TFPI = qualitative_factor_level_vector[1]
    FV = qualitative_factor_level_vector[2]
    FVIII = qualitative_factor_level_vector[3]
    FIX = qualitative_factor_level_vector[4]
    FX = qualitative_factor_level_vector[5]
    PL = qualitative_factor_level_vector[6]

    # Calculate the control vector -
    # Trigger -
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
    
    # Initiation model -
    initiation_trigger_term = ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation))
    initiation_TFPI_term = 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
    
    # Amplification model -
    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
    inhibition_term = 1 - ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
    inhibition_term_TFPI = 1 - ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
    factor_product = FV*FX*FVIII*FIX
    factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
    
    # Shutdown phase -
    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))

    control_vector = ones(1,4)
    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term)
    control_vector[2] = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)
    control_vector[3] = shutdown_term
    control_vector[4] = 1

    # Calculate the kinetics -
    k_trigger = kinetic_parameter_vector[1]
    K_FII_trigger = kinetic_parameter_vector[2]
    k_amplification = kinetic_parameter_vector[3]
    K_FII_amplification = kinetic_parameter_vector[4]
    k_APC_formation = kinetic_parameter_vector[5]
    K_PC_formation = kinetic_parameter_vector[6]
    k_inhibition = kinetic_parameter_vector[7]
    K_FIIa_inhibition = kinetic_parameter_vector[8]
    k_inhibition_ATIII = kinetic_parameter_vector[9]
    #K_inhibition_ATIII = kinetic_parameter_vector[9]
    #K_inhibition_ATIII_FIIa = kinetic_parameter_vector[10]
    
#@show kinetic_parameter_vector
    rate_vector = ones(1,4)
    rate_vector[1] = k_trigger*TRIGGER*(FII/(K_FII_trigger + FII))
    rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
    rate_vector[3] = k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC))
    #rate_vector[3] = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
    rate_vector[4] = Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26)


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
			control_vector[j] = 0.0
		end
	end

    # modified rate vector -
    modified_rate_vector = (rate_vector).*(control_vector);
	#@show rate_vector
	#@show control_vector
	#@show modified_rate_vector

    # calculate dxdt_reaction -
    dxdt_total = zeros(1,7)
    dxdt_total[1] = -1*modified_rate_vector[2] - modified_rate_vector[1]                            # 0 FII
    dxdt_total[2] = modified_rate_vector[2] + modified_rate_vector[1] - modified_rate_vector[4]     # 1 FIIa
    dxdt_total[3] = -1*modified_rate_vector[3]                                                      # 2 PC
    dxdt_total[4] = 1*modified_rate_vector[3]                                                       # 3 APC
    dxdt_total[5] = -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26)                                    # 4 ATIII
    dxdt_total[6] = 0.0                                                                             # 5 TM (acts as enzyme, so no change)
    dxdt_total[7] = -0.0*TRIGGER                                                                    # 6 TRIGGER
    @show dxdt_total
    return vec(dxdt_total)


end
