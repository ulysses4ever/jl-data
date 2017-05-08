using ParameterizedFunctions
using DifferentialEquations
using Plots
using DiffEqSensitivity
#f = @ode_def testing begin
#  dy[1] = -k1*y[1]+k3*y[2]*y[3]
#  dy[2]=  k1*y[1]-k2*y[2]^2-k3*y[2]*y[3]
#  dy[3] =  k2*y[1]^2
#end  k1=>11 k2=>2 k3=>3 

#coagulation = @ode_def coag begin
#	FII	 = x[1]
#	FIIa	= x[2]
#	PC	  = x[3]
#	APC	 = x[4]
#	ATIII   = x[5]
#	TM	  = x[6]
#	TRIGGER = x[7]
#	Eps = x[8] #frac platelets acativated
#	FV_FX = x[9]
#	FV_FXA = x[10]
#	PROTHOMBINASE_PLATELETS = x[11] 


#	aleph = PROBLEM_DICTIONARY["ALEPH"]
#	faleph = aleph^platelet_pwr/(aleph^platelet_pwr + platelet_denom^platelet_pwr)
#	EpsMax = EpsMax0+(1+EpsMax0)*faleph

#	#timing
#	time_delay = timing[1]
#	time_coeff = timing[2]

#	# Initiation model -
#    initiation_trigger_term = ((alpha_trigger_activation*TRIGGER)^order_trigger_activation)/(1 + ((alpha_trigger_activation*TRIGGER)^order_trigger_activation))
#    initiation_TFPI_term = 1 - ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI)/(1 + ((alpha_trigger_inhibition_TFPI*TFPI)^order_trigger_inhibition_TFPI))
#    
#    # Amplification model -
#    activation_term = ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa)/(1 + ((alpha_amplification_FIIa*FIIa)^order_amplification_FIIa))
#    inhibition_term = 1 - ((alpha_amplification_APC*APC)^order_amplification_APC)/(1 + ((alpha_amplification_APC*APC)^order_amplification_APC))
#    inhibition_term_TFPI = 1 - ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI)/(1 + ((alpha_amplification_TFPI*TFPI)^order_amplification_TFPI))
#    factor_product = FIX*FVIII*FV_FX
#    factor_amplification_term = ((0.1*factor_product)^2)/(1+((0.1*factor_product)^2))
#    
#    # Shutdown phase -
#    shutdown_term = ((alpha_shutdown_APC*FIIa)^order_shutdown_APC)/(1 + ((alpha_shutdown_APC*FIIa)^order_shutdown_APC))

#    #prothominabse complex formation
#    activation_FV_by_thrombin = (alpha_FV_activation*FIIa)^order_FV_activation/(1+(alpha_FV_activation*FIIa)^order_FV_activation)
#    activation_FX_by_trigger = (alpha_FX_activation*TRIGGER)^order_FX_activation/(1+(alpha_FX_activation*TRIGGER)^order_FX_activation)
#    inhibition_of_FX_by_ATIII=1-(alpha_FX_inhibition*ATIII)^order_FX_inhibition/(1+(alpha_FX_inhibition*ATIII)^order_FX_inhibition)

#    control_vector = ones(1,7)
#    control_vector[1] = min(initiation_trigger_term,initiation_TFPI_term, inhibition_term)
#    control_vector[2] = min(inhibition_term,inhibition_term_TFPI)
#    control_vector[3] = shutdown_term
#    control_vector[4] = 1
#    control_vector[5] = 1
#    control_vector[6] = min(inhibition_term,inhibition_term_TFPI)
#    control_vector[7] = min(inhibition_term,inhibition_term_TFPI,factor_amplification_term)
#		#@show control_vector[5], activation_FV_by_thrombin, activation_FX_by_trigger, inhibition_of_FX_by_ATIII

#    # Calculate the kinetics -
#    k_trigger = kinetic_parameter_vector[1]
#    K_trigger = kinetic_parameter_vector[2]
#    k_amplification = kinetic_parameter_vector[3]
#    K_FII_amplification = kinetic_parameter_vector[4]
#    k_APC_formation = kinetic_parameter_vector[5]
#    K_PC_formation = kinetic_parameter_vector[6]
#    k_inhibition = kinetic_parameter_vector[7]
#    K_FIIa_inhibition = kinetic_parameter_vector[8]
#    k_inhibition_ATIII = kinetic_parameter_vector[9]
#    k_FV_X_activation = kinetic_parameter_vector[10]
#    K_FV_X_actiation = kinetic_parameter_vector[11]
#    #k_FX_activation = kinetic_parameter_vector[12]
#    #K_FX_activation = kinetic_parameter_vector[13]
#    k_complex = kinetic_parameter_vector[14]
#    k_amp_prothombinase = kinetic_parameter_vector[15]
#    K_FII_amp_prothombinase=kinetic_parameter_vector[16]
#    k_amp_active_factors= kinetic_parameter_vector[17]
#    K_amp_active_factors = kinetic_parameter_vector[18]
#    
##@showp
#    rate_vector = zeros(1,7)
#	#if(t>time_delay)
#	    rate_vector[1] = k_trigger*TRIGGER*(FV_FX/(K_trigger + FV_FX))
#	    rate_vector[2] = k_amplification*FIIa*(FII/(K_FII_amplification + FII))
#	    rate_vector[3] = k_APC_formation*TM*(Float64(PC)/Float64(K_PC_formation + PC))
#	    #rate_vector[3] = k_inhibition*APC*(FIIa/(FIIa + K_FIIa_inhibition)) + k_inhibition_ATIII*(ATIII)*pow(FIIa,1.26)
#	    rate_vector[4] = Float64(k_inhibition_ATIII)*Float64(ATIII)*(Float64(FIIa)^1.26)
#	    rate_vector[5] = k_complex*FV_FXA*aida/Eps
#	    rate_vector[6] = k_amp_prothombinase*PROTHOMBINASE_PLATELETS*FII/(K_FII_amp_prothombinase + FII)
#	    rate_vector[7] = k_amp_active_factors*FV_FXA*FII/(K_amp_active_factors+FII)
#	#end
##	f = open("ratevector.txt", "a+")
##	writedlm(f, rate_vector)
##	close(f)

#	#@show t, x, rate_vector, control_vector
#	#remove nans
#	for j = 1:length(rate_vector)
#		if(isnan(rate_vector[j]) || !isfinite(rate_vector[j]))
#			println("Found NAN at rate_vector $j")
#			rate_vector[j] = 0.0
#		end
#	end

#	#remove nans
#	for j = 1:length(control_vector)
#		if(isnan(control_vector[j])|| !isfinite(control_vector[j]))
#			println("Found NAN at control_vector $j")
#			control_vector[j] = 1.0
#		end
#	end

#	 # modified rate vector -
#	modified_rate_vector = (rate_vector).*(control_vector);
##	f = open("modifiedratevector.txt", "a+")
##	writedlm(f, modified_rate_vector)
##	close(f)

##	f = open("times.txt", "a+")
##	writedlm(f, t)
##	close(f)


#	# calculate dxdt_reaction -
#	dxdt_total = zeros(size(x,1),1)
#	
#	dxdt_total[1] = -1*modified_rate_vector[2] -modified_rate_vector[7]-modified_rate_vector[6]	# 1 FII
#	dxdt_total[2] = modified_rate_vector[2] - modified_rate_vector[4]+modified_rate_vector[7]+modified_rate_vector[6]	 # 2 FIIa
#	dxdt_total[3] = -1*modified_rate_vector[3] # 3 PC
#	dxdt_total[4] = 1*modified_rate_vector[3]  # 4 APC
#	dxdt_total[5] = -1*k_inhibition_ATIII*(ATIII)*(FIIa^1.26)# 5 ATIII
#	dxdt_total[6] = 0.0 # 6 TM (acts as enzyme, so no change)
#	dxdt_total[7] = -0.0*TRIGGER	# 7 TRIGGER
#	dxdt_total[8] = kplatelts*(EpsMax-Eps)-koffplatelets*Eps#-rate_vector[5] #frac active platelets
#	#dxdt_total[8] = 0.0 #if no platelets, they can't be activated
#	dxdt_total[9] = -1*modified_rate_vector[1] #FV_FX
#	dxdt_total[10] = modified_rate_vector[1] -rate_vector[5]#FV_FXa
#	dxdt_total[11] = modified_rate_vector[5] #Prothromibase_platelets

#	idx = find(x->(x<0),x);
#	x[idx] = 0.0;
#	dxdt_total[idx]= 0.0


#	tau = time_coeff*(1-FIIa/aleph)
#	time_scale =1-1*exp(-tau*(t-time_delay))
#	if(t<time_delay)
#		time_scale = 0.0
#	end
#	if(isnan(time_scale))
#		time_scale = 1.0
#	end
#	(dxdt_total.*time_scale)
#end alpha_trigger_activation =>1 order_trigger_activation=>

pf_func = function (t,u,p,du)
  du[1] = p[1] * u[1] - p[2] * u[1]*u[2]
  du[2] = -3 * u[2] + u[1]*u[2]
end

pf_func2 = function (t,u,p,dx)
	a = p[1]
	b = p[2]
	x1= u[1]
	x2 = u[2]
	dx = Array(Any, size(u,1),1)
	dx[1] = a * x1 - b * x1*x2
	dx[2] = -3 * x2 + x1*x2
	return dx
end



function SampleProblem()

	pf = ParameterizedFunction(pf_func,[1.5,1.0])
	@show typeof(pf)

	#prob = ODEProblem(pf, [1.0;1.0],(0.0,10.0))
	prob = ODELocalSensitivityProblem(pf, [1.0; 1.0], (0.0, 10.0))

	sol = solve(prob,Rosenbrock23())

	plot(sol)
end

function ChrisSolution()

	v = rand(4)
	params = Expr[:(a=>$(v[1]));:(b=>$(v[2]));:(c=>$(v[3]));:(d=$(v[4]))]
	f=ParameterizedFunctions.ode_def_opts(:LVE,Dict{Symbol,Bool}(
	    :build_tgrad => true,
	    :build_jac => true,
	    :build_expjac => false,
	    :build_invjac => true,
	    :build_invW => true,
	    :build_hes => true,
	    :build_invhes => true,
	    :build_dpfuncs => true),:(begin
	      dx = a*x - b*x*y
	      dy = -c*y + d*x*y
	    end),params...)

	prob = ODELocalSensitivityProblem(f,[1.0;1.0],(0.0,10.0))
	sol = solve(prob,DP8(), dt = .02)

	plot(sol)
end

