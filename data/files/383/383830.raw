function buildCoagulationModelDictionary(inWound)
    
	#if inWound ==1, in wound comparment
    # Initialize -
    PROBLEM_DICTIONARY = Dict()
    
    # FII     = local_state_vector[0]
    # FIIa    = local_state_vector[1]
    # PC      = local_state_vector[2]
    # APC     = local_state_vector[3]
    # ATIII   = local_state_vector[4]
    # TM      = local_state_vector[5]
    # TRIGGER = local_state_vector[6]
    
    # Initial condition -
	#from simulateFig3Butenas2002
    initial_condition_vector = Float64[]
    push!(initial_condition_vector,1400)       # 0 FII
    push!(initial_condition_vector,0.0)        # 1 FIIa
    push!(initial_condition_vector,60.0)        # 2 PC
    push!(initial_condition_vector,0.0)        # 3 APC
    push!(initial_condition_vector,3400)       # 4 ATIII
    push!(initial_condition_vector,12)         # 5 TM
	if(inWound ==1)
    		push!(initial_condition_vector,0.005)          # 6 TRIGGER
	else
		push!(initial_condition_vector,0.0)
	end
    PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"] = initial_condition_vector
    
    # Kinetic parameters -
    kinetic_parameter_vector = Float64[]
    push!(kinetic_parameter_vector,7200)       # 0 k_trigger
    push!(kinetic_parameter_vector,1400)       # 1 K_FII_trigger
    push!(kinetic_parameter_vector,4.5)        # 2 k_amplification
    push!(kinetic_parameter_vector,1200)       # 3 K_FII_amplification
    push!(kinetic_parameter_vector,0.1)        # 4 k_APC_formation
    push!(kinetic_parameter_vector,30)         # 5 K_PC_formation
    push!(kinetic_parameter_vector,0.2)        # 6 k_inhibition
    push!(kinetic_parameter_vector,1200)       # 7 K_FIIa_inhibition
    push!(kinetic_parameter_vector,0.0001)     # 8 k_inhibition_ATIII
    #push!(kinetic_parameter_vector,0.001)      # 9 K_inhibition_ATIII
    #push!(kinetic_parameter_vector,100.0)      # 10 K_inhibition_FIIa
    PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"] = kinetic_parameter_vector
    
    # Control parameters -
    control_parameter_vector =Float64[]
    # Trigger -
    push!(control_parameter_vector,140.0)      # 0 9 alpha_trigger_activation = control_parameter_vector[0]
    push!(control_parameter_vector,2.0)        # 1 10 order_trigger_activation = control_parameter_vector[1]
    push!(control_parameter_vector,1.0)        # 2 11 alpha_trigger_inhibition_APC = control_parameter_vector[2]
    push!(control_parameter_vector,2.0)        # 3 12 order_trigger_inhibition_APC = control_parameter_vector[3]
    push!(control_parameter_vector,0.1)        # 4 13 alpha_trigger_inhibition_TFPI = control_parameter_vector[4]
    push!(control_parameter_vector,2.0)        # 5 14 order_trigger_inhibition_TFPI = control_parameter_vector[5]
    
    # Amplification -
    push!(control_parameter_vector,0.1)        # 6 15 alpha_amplification_FIIa = control_parameter_vector[6]
    push!(control_parameter_vector,2.0)        # 7 16 order_amplification_FIIa = control_parameter_vector[7]
    push!(control_parameter_vector,0.4)        # 8 17 alpha_amplification_APC = control_parameter_vector[8]
    push!(control_parameter_vector,2.0)        # 9 18 order_amplification_APC = control_parameter_vector[9]
    push!(control_parameter_vector,0.01)       # 10 19 alpha_amplification_TFPI = control_parameter_vector[10]
    push!(control_parameter_vector,2.0)        # 11 20 order_amplification_TFPI = control_parameter_vector[11]
    
    # APC generation -
    push!(control_parameter_vector,2.0)        # 12 21 alpha_shutdown_APC = control_parameter_vector[12]
    push!(control_parameter_vector,2.0)        # 13 22 order_shutdown_APC = control_parameter_vector[13]
    PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"] = control_parameter_vector
    
    # Experimental output scaling -
    # Fig 5A scaling (3.20,1.0)
    # Fig 3 scaling (-1.0,1.0)
    # Fig 2 scaling (1.8)
    # Fig 1 allen scaling (4.0,1.0)
    scaling_parameter_vector =Float64[]
    push!(scaling_parameter_vector,4.0)        # 0 Time scale 
    push!(scaling_parameter_vector,1.0)        # 1 Abundance scale
    PROBLEM_DICTIONARY["SCALING_PARAMETER_VECTOR"] = scaling_parameter_vector
    
    # QFactor vector - from simulateFig3Butenas2002
    qualitative_factor_vector =Float64[]
   push!(qualitative_factor_vector,2.5)           # 0 TFPI
   push!(qualitative_factor_vector,20.0)          # 1 FV
   push!(qualitative_factor_vector,0.7)           # 2 FVIII
   push!(qualitative_factor_vector,90.0)           # 3 FIX
   push!(qualitative_factor_vector,170.0)         # 4 FX
   push!(qualitative_factor_vector,1.0)           # 5 Platelets
    PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"] = qualitative_factor_vector
    
    return PROBLEM_DICTIONARY
end
