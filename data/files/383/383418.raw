#estimate parameters
using POETs
include("objective_function.jl")

function test_model()
	outputfile = "parameterEstimation/POETS_2016_12_08NoPeturbation.txt"
	number_of_subdivisions = 10
	number_of_parameters = 44
	number_of_objectives = 2
	ec_array = zeros(number_of_objectives)
  	pc_array = zeros(number_of_parameters)
	kinetic_parameter_vector = Float64[]
    push!(kinetic_parameter_vector,7200*1/10)       #  k_trigger
    push!(kinetic_parameter_vector,1400)       # 1 K_FII_trigger
    push!(kinetic_parameter_vector,4.5*.8)        # 2 k_amplification
    push!(kinetic_parameter_vector,1200)       # 3 K_FII_amplification
    push!(kinetic_parameter_vector,0.1*.95)        # 4 k_APC_formation
    push!(kinetic_parameter_vector,30/10.0)         # 5 K_PC_formation
    push!(kinetic_parameter_vector,0.2*10000)        # 6 k_inhibition
    push!(kinetic_parameter_vector,1200/10.0)       # 7 K_FIIa_inhibition
    push!(kinetic_parameter_vector,0.0001*1.2)     # 8 k_inhibition_ATIII
    #push!(kinetic_parameter_vector,0.001)      # 9 K_inhibition_ATIII
    #push!(kinetic_parameter_vector,100.0)      # 10 K_inhibition_FIIa
    push!(kinetic_parameter_vector, 2E7*60*10.0^-6) #9 k_FV_activation, from reaction 16 in Diamond 2010 paper
    push!(kinetic_parameter_vector, 1E8*80*10.0^-6/100) #10 K_FV_activation 
    push!(kinetic_parameter_vector, 6.0) #11 k_FX_activation from reaction 6 in Diamond 2010 paper
    push!(kinetic_parameter_vector, 2.8E-7*10.0^6) #12 K_FX_activation
    push!(kinetic_parameter_vector, 4E8*60*10.0^-10) #13 k_complex
    push!(kinetic_parameter_vector, 63.5*60*100 )#14 k_amp_prothombinase from reaction 18 in Diamond 2010
    push!(kinetic_parameter_vector, 1.6E-6*10.0^6*10000) #13 K_FII_amp_prothombinase
	@show size(kinetic_parameter_vector)

	    # Control parameters -
    control_parameter_vector =Float64[]
    # Trigger -
    push!(control_parameter_vector,140.0/10)      # 0 9 alpha_trigger_activation = control_parameter_vector[0]
    push!(control_parameter_vector,2.0)        # 1 10 order_trigger_activation = control_parameter_vector[1]
    push!(control_parameter_vector,1.0)        # 2 11 alpha_trigger_inhibition_APC = control_parameter_vector[2]
    push!(control_parameter_vector,2.0)        # 3 12 order_trigger_inhibition_APC = control_parameter_vector[3]
    push!(control_parameter_vector,0.1)        # 4 13 alpha_trigger_inhibition_TFPI = control_parameter_vector[4]
    push!(control_parameter_vector,2.0)        # 5 14 order_trigger_inhibition_TFPI = control_parameter_vector[5]
    
    # Amplification -
    push!(control_parameter_vector,0.1*10000)        # 6 15 alpha_amplification_FIIa = control_parameter_vector[6]
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
	@show size(control_parameter_vector)
		platelet_parameter_vector = Float64[]
	push!(platelet_parameter_vector, .005*12) #1 rate constant
	push!(platelet_parameter_vector, 1.6123) #2 power for control function
	push!(platelet_parameter_vector, 2.4279E-9) #3 adjustment in denominator
	push!(platelet_parameter_vector, .01) #4 Epsmax0
	push!(platelet_parameter_vector, .01*1.05)  #5 aida
	push!(platelet_parameter_vector, .2) #koffplatelets

	timing = Float64[]
	push!(timing, 4.25) #time_delay
	push!(timing, .35) #coeff

	#@show timing, control_parameter_vector
	#@show vcat(timing, control_parameter_vector)
	inital_parameter_estimate = vcat(kinetic_parameter_vector, control_parameter_vector, platelet_parameter_vector, timing)	
for index in collect(1:number_of_subdivisions)
	initial_parameter_array = zeros(1,44)

    # Grab a starting point -
    initial_parameter_array[1:16]  = kinetic_parameter_vector
    initial_parameter_array[17:36] = control_parameter_vector
    initial_parameter_array[37:42] = platelet_parameter_vector
    initial_parameter_array[43:44] = timing

    # Run JuPOETs -
    (EC,PC,RA) = estimate_ensemble(objective_function,neighbor_function,acceptance_probability_function,cooling_function,vec(initial_parameter_array);rank_cutoff=4,maximum_number_of_iterations=10,show_trace=true)

    # Package -
    ec_array = [ec_array EC]
    pc_array = [pc_array PC]
	#write outputs to file
	@show (EC, PC, RA)
	f = open(outputfile, "a")
	write(f, string(EC, ",", PC, ",", RA, "\n"))
	close(f)
  end

  return (ec_array,pc_array)

end
