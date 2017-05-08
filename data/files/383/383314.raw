function buildCoagulationModelDictionary()
    
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
    push!(initial_condition_vector,0.001)        # 1 FIIa
    push!(initial_condition_vector,60.0)        # 2 PC
    push!(initial_condition_vector,0.0)        # 3 APC
    push!(initial_condition_vector,3400)       # 4 ATIII
    push!(initial_condition_vector,12)         # 5 TM
    push!(initial_condition_vector,1.0E-3)          # 6 TRIGGER
    push!(initial_condition_vector, 0.0) #Fraction of platelets activated
    push!(initial_condition_vector,22.0)          #  FV+FX
    push!(initial_condition_vector,0.0)          #  FVa+FXa
    push!(initial_condition_vector,0.000)         #  prothombinase complex
    PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"] = initial_condition_vector
    
    # Kinetic parameters -
    kinetic_parameter_vector = Float64[]
    push!(kinetic_parameter_vector,7200*2)       #  k_trigger
    push!(kinetic_parameter_vector,1)       # 1 K_trigger
    push!(kinetic_parameter_vector,60.0)        # 2 k_amplification
    push!(kinetic_parameter_vector,12)       # 3 K_FII_amplification
    push!(kinetic_parameter_vector,.5)        # 4 k_APC_formation
    push!(kinetic_parameter_vector,.3)         # 5 K_PC_formation
    push!(kinetic_parameter_vector,40)        # 6 k_inhibition
    push!(kinetic_parameter_vector,120)       # 7 K_FIIa_inhibition
    push!(kinetic_parameter_vector,4E-4)     # 8 k_inhibition_ATIII
    #push!(kinetic_parameter_vector,0.001)      # 9 K_inhibition_ATIII
    #push!(kinetic_parameter_vector,100.0)      # 10 K_inhibition_FIIa
    push!(kinetic_parameter_vector, 2E7*60*10.0^-4) #9 k_FV_activation, from reaction 16 in Diamond 2010 paper
    push!(kinetic_parameter_vector, 1E8*80*10.0^-6/100) #10 K_FV_activation 
    push!(kinetic_parameter_vector, 600.0) #11 k_FX_activation from reaction 6 in Diamond 2010 paper
    push!(kinetic_parameter_vector, .28) #12 K_FX_activation
    push!(kinetic_parameter_vector, 24/2) #13 k_complex
    push!(kinetic_parameter_vector, 63.5*400*5 )#14 k_amp_prothombinase from reaction 18 in Diamond 2010
    push!(kinetic_parameter_vector, 10) #13 K_FII_amp_prothombinase
    push!(kinetic_parameter_vector, 6.0*10) #k_amp_active_factors
    push!(kinetic_parameter_vector, 1.0) #K_amp_active_factor


    PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"] = kinetic_parameter_vector
    
    # Control parameters -
    control_parameter_vector =Float64[]
    # Trigger -
    push!(control_parameter_vector,140.0/10)      # 0 9 alpha_trigger_activation = control_parameter_vector[0]
    push!(control_parameter_vector,2.0)        # 1 10 order_trigger_activation = control_parameter_vector[1]
    push!(control_parameter_vector,1.0)        # 2 11 alpha_trigger_inhibition_APC = control_parameter_vector[2]
    push!(control_parameter_vector,1.0)        # 3 12 order_trigger_inhibition_APC = control_parameter_vector[3]
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

    push!(control_parameter_vector,1.0) #14 alpha_FV_activation
    push!(control_parameter_vector,1.0/10) #15 order_FV_activation
    push!(control_parameter_vector,1.0) #16 alpha_FX_activation
    push!(control_parameter_vector,1.0) #17 order_FX_activation
    push!(control_parameter_vector,4.0) #14 alpha_FX_inhibition
    push!(control_parameter_vector,1.0) #15 order_FX_inhibition
    PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"] = control_parameter_vector

   #platlet controls
	platelet_parameter_vector = Float64[]
	push!(platelet_parameter_vector, .005*5) #1 rate constant
	push!(platelet_parameter_vector, 1.6123) #2 power for control function
	push!(platelet_parameter_vector, 2.4279E-9) #3 adjustment in denominator
	push!(platelet_parameter_vector, .01) #4 Epsmax0
	push!(platelet_parameter_vector, .01)  #5 aida
	push!(platelet_parameter_vector, .005) #koffplatelets
	PROBLEM_DICTIONARY["PLATELET_PARAMS"] = platelet_parameter_vector
   

   PROBLEM_DICTIONARY["ALEPH"] = initial_condition_vector[2]

	timing = Float64[]
	push!(timing, 0) #time_delay
	push!(timing, 3.5) #coeff
	PROBLEM_DICTIONARY["TIME_DELAY"]=timing
    
    # QFactor vector - from simulateFig3Butenas2002
    qualitative_factor_vector =Float64[]
   push!(qualitative_factor_vector,2.5)           # 0 TFPI
   push!(qualitative_factor_vector,20.0)          # 1 FV
   push!(qualitative_factor_vector,0.7)           # 2 FVIII
   push!(qualitative_factor_vector,90.0)           # 3 FIX
   push!(qualitative_factor_vector,170.0)         # 4 FX
   push!(qualitative_factor_vector,1.0)           # 5 Platelets
    PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"] = qualitative_factor_vector

	nominal_levels = Float64[]
   push!(nominal_levels,2.5)           # 0 TFPI
   push!(nominal_levels,0.7)           # 2 FVIII
   push!(nominal_levels,90.0)           # 3 FIX
   push!(nominal_levels,22.0)         # 4 FV_X
	PROBLEM_DICTIONARY["NOMINAL_VALUES"] = nominal_levels

	PROBLEM_DICTIONARY["FVIII_CONTROL"] = 1.0
    
    return PROBLEM_DICTIONARY
end

function buildCoagulationModelDictionary(kinetic_parameter_vector, control_parameter_vector, platelet_parameter_vector,timing)
    
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
    push!(initial_condition_vector,0.001)        # 1 FIIa
    push!(initial_condition_vector,60.0)        # 2 PC
    push!(initial_condition_vector,0.0)        # 3 APC
    push!(initial_condition_vector,3400)       # 4 ATIII
    push!(initial_condition_vector,12)         # 5 TM
    push!(initial_condition_vector,1.0E-3)          # 6 TRIGGER
    push!(initial_condition_vector, 0.0) #Fraction of platelets activated
    push!(initial_condition_vector,22.0)          #  FV+FX
    push!(initial_condition_vector,0.00)          #  FVa+FXa
    push!(initial_condition_vector,0.00)         #  prothombinase complex
    PROBLEM_DICTIONARY["INITIAL_CONDITION_VECTOR"] = initial_condition_vector

    PROBLEM_DICTIONARY["KINETIC_PARAMETER_VECTOR"] = kinetic_parameter_vector
    
    PROBLEM_DICTIONARY["CONTROL_PARAMETER_VECTOR"] = control_parameter_vector

   #platlet controls
	PROBLEM_DICTIONARY["PLATELET_PARAMS"] = platelet_parameter_vector
    
    # Experimental output scaling -
    # Fig 5A scaling (3.20,1.0)
    # Fig 3 scaling (-1.0,1.0)
    # Fig 2 scaling (1.8)
    # Fig 1 allen scaling (4.0,1.0)
    scaling_parameter_vector =Float64[]
    push!(scaling_parameter_vector,4.0)        # 0 Time scale 
    push!(scaling_parameter_vector,1.0)        # 1 Abundance scale
    PROBLEM_DICTIONARY["SCALING_PARAMETER_VECTOR"] = scaling_parameter_vector

   PROBLEM_DICTIONARY["ALEPH"] = initial_condition_vector[2]
	PROBLEM_DICTIONARY["TIME_DELAY"]=timing
     # QFactor vector - from simulateFig3Butenas2002
    qualitative_factor_vector =Float64[]
   push!(qualitative_factor_vector,2.5)           # 0 TFPI
   push!(qualitative_factor_vector,20.0)          # 1 FV
   push!(qualitative_factor_vector,0.7)           # 2 FVIII
   push!(qualitative_factor_vector,90.0)           # 3 FIX
   push!(qualitative_factor_vector,170.0)         # 4 FX
   push!(qualitative_factor_vector,1.0)           # 5 Platelets
    PROBLEM_DICTIONARY["FACTOR_LEVEL_VECTOR"] = qualitative_factor_vector

	nominal_levels = Float64[]
   push!(nominal_levels,2.5)           # 0 TFPI
   push!(nominal_levels,0.7)           # 2 FVIII
   push!(nominal_levels,90.0)           # 3 FIX
   push!(nominal_levels,22.0)         # 4 FV_X
	PROBLEM_DICTIONARY["NOMINAL_VALUES"] = nominal_levels

	PROBLEM_DICTIONARY["FVIII_CONTROL"] = 1.0
    
    return PROBLEM_DICTIONARY
end
