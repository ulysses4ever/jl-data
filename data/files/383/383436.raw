include("BalanceEquations.jl")
include("CoagulationModelFactoryDecentFit.jl")
include("utilities.jl")
#using Sundials
using ODE
using NLopt
#using PyPlot


#load data once
experimentaldata = readdlm("../data/ButenasFig1B60nMFVIIa.csv", ',')
#fig = figure(figsize = (15,15))
#hold("on")
#plot(experimentaldata[:,1], experimentaldata[:,2], ".k")
#ylabel("Thrombin Concentration, nM")
#xlabel("Time, in minutes")

pathsToData = ["../data/ButenasFig1B60nMFVIIa.csv","../data/Buentas1999Fig450PercentProthrombin.txt", "../data/Buentas1999Fig4100PercentProthrombin.txt", "../data/Buentas1999Fig4150PercentProthrombin.txt"]
#allexperimentaldata = Array[]
#for j in collect(1:size(pathsToData,1))
#	experimentaldata = readdlm(pathsToData[j], ',')	
#	push!(allexperimentaldata, experimentaldata)
#end


function objectiveForNLOpt(params::Vector, grad::Vector)
	#tic()
	dict = buildDictFromOneVector(params)
	TSTART = 0.0
	Ts = .02
	TSTOP = 20.0
	TSIM = collect(TSTART:Ts:TSTOP)
	initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
	fbalances(t,y)= BalanceEquations(t,y,dict) 
	t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-8, reltol = 1E-8)
	FIIa = [a[2] for a in X]
	MSE, interpolatedExperimentalData=calculateMSE(t, FIIa, experimentaldata)
	#hold("on")
	#plot(t, FIIa, alpha = .5)
	#write params to file
	f = open("parameterEstimation/NLopt_2017_02_02.txt", "a+")
	write(f, string(params, ",", MSE, "\n"))
	close(f)
	#toc()
	@show MSE
	return MSE
end

function objectiveForNLOptFourDataSets(params::Vector, grad::Vector)
	dict = buildDictFromOneVector(params)
	TSTART = 0.0
	Ts = .02
	TSTOP = 20.0
	TSIM = collect(TSTART:Ts:TSTOP)
	totalMSE = 0.0
	for j in collect(1:size(pathsToData,2))
		initial_condition_vector = dict["INITIAL_CONDITION_VECTOR"]
		if(j >1)
			initial_condition_vector[3] = 0.0 #no protein C pathway
			initial_condition_vector[7] = 5E-3 #5 pM trigger
		end

		if(j ==2)
			initial_condition_vector[1] = initial_condition_vector[1]*.5
		elseif(j==3)
			initial_condition_vector[1] = initial_condition_vector[1]*1.0
		elseif(j==4)
			initial_condition_vector[1] = initial_condition_vector[1]*1.5
		end
	experimentaldata = allexperimentaldata[j]
	fbalances(t,y)= BalanceEquations(t,y,dict) 
	t,X = ODE.ode23s(fbalances,(initial_condition_vector),TSIM, abstol = 1E-8, reltol = 1E-8)
	FIIa = [a[2] for a in X]
	MSE, interpolatedExperimentalData=calculateMSE(t, FIIa, experimentaldata)
	#write params to file
	f = open("parameterEstimation/NLopt_2016_12_08FourDataSets.txt", "a+")
	write(f, string(params, ",", MSE, "\n"))
	close(f)
	#toc()
	@show MSE
	totalMSE = totalMSE+MSE
	end
	return totalMSE
end

function attemptOptimizationNLOpt()
	numvars = 46
	opt = Opt(:LN_NELDERMEAD,numvars)
	lower_bounds!(opt, vec(fill(1E-9,1,numvars)))
	upperbounds = fill(1E7, 1, numvars)
	upperbounds[3] = 50.0 #bound k_amplication to be small
	upper_bounds!(opt, vec(upperbounds))
	min_objective!(opt, objectiveForNLOpt)
	#min_objective!(opt, objectiveForNLOptFourDataSets)
    
    # Kinetic parameters -
   kinetic_parameter_vector = Float64[]
    push!(kinetic_parameter_vector,7200)       #  k_trigger
    push!(kinetic_parameter_vector,450)       # 1 K_trigger
    push!(kinetic_parameter_vector,4.5)        # 2 k_amplification
    push!(kinetic_parameter_vector,1200)       # 3 K_FII_amplification
    push!(kinetic_parameter_vector,5.0)        # 4 k_APC_formation
    push!(kinetic_parameter_vector,30/100.0)         # 5 K_PC_formation
    push!(kinetic_parameter_vector,0.2*10000)        # 6 k_inhibition
    push!(kinetic_parameter_vector,1200/10.0)       # 7 K_FIIa_inhibition
    push!(kinetic_parameter_vector,0.001*1.2)     # 8 k_inhibition_ATIII
    #push!(kinetic_parameter_vector,0.001)      # 9 K_inhibition_ATIII
    #push!(kinetic_parameter_vector,100.0)      # 10 K_inhibition_FIIa
    push!(kinetic_parameter_vector, 2E7*60*10.0^-6) #9 k_FV_activation, from reaction 16 in Diamond 2010 paper
    push!(kinetic_parameter_vector, 1E8*80*10.0^-6/100) #10 K_FV_activation 
    push!(kinetic_parameter_vector, 6.0) #11 k_FX_activation from reaction 6 in Diamond 2010 paper
    push!(kinetic_parameter_vector, 2.8E-7*10.0^6) #12 K_FX_activation
    push!(kinetic_parameter_vector, 4E8*60*10.0^-7) #13 k_complex
    push!(kinetic_parameter_vector, 63.5*60*100 )#14 k_amp_prothombinase from reaction 18 in Diamond 2010
    push!(kinetic_parameter_vector, 1.6E-6*10.0^6*10000) #13 K_FII_amp_prothombinase
    push!(kinetic_parameter_vector, 5.0*10) #k_amp_active_factors
    push!(kinetic_parameter_vector, 1.0) #K_amp_active_factor

    
    # Control parameters -
    control_parameter_vector =Float64[]
    # Trigger -
    push!(control_parameter_vector,100.0)      # 0 9 alpha_trigger_activation = control_parameter_vector[0]
    push!(control_parameter_vector,2.0)        # 1 10 order_trigger_activation = control_parameter_vector[1]
    push!(control_parameter_vector,1.0)        # 2 11 alpha_trigger_inhibition_APC = control_parameter_vector[2]
    push!(control_parameter_vector,1.0)        # 3 12 order_trigger_inhibition_APC = control_parameter_vector[3]
    push!(control_parameter_vector,0.1)        # 4 13 alpha_trigger_inhibition_TFPI = control_parameter_vector[4]
    push!(control_parameter_vector,2.0)        # 5 14 order_trigger_inhibition_TFPI = control_parameter_vector[5]
    
    # Amplification -
    push!(control_parameter_vector,0.1*100)        # 6 15 alpha_amplification_FIIa = control_parameter_vector[6]
    push!(control_parameter_vector,2.0)        # 7 16 order_amplification_FIIa = control_parameter_vector[7]
    push!(control_parameter_vector,0.4)        # 8 17 alpha_amplification_APC = control_parameter_vector[8]
    push!(control_parameter_vector,2.0)        # 9 18 order_amplification_APC = control_parameter_vector[9]
    push!(control_parameter_vector,0.01)       # 10 19 alpha_amplification_TFPI = control_parameter_vector[10]
    push!(control_parameter_vector,2.0)        # 11 20 order_amplification_TFPI = control_parameter_vector[11]
    
    # APC generation -
    push!(control_parameter_vector,2.0)        # 12 21 alpha_shutdown_APC = control_parameter_vector[12]
    push!(control_parameter_vector,10.0)        # 13 22 order_shutdown_APC = control_parameter_vector[13]

    push!(control_parameter_vector,1.0) #14 alpha_FV_activation
    push!(control_parameter_vector,1.0/10) #15 order_FV_activation
    push!(control_parameter_vector,1.0) #16 alpha_FX_activation
    push!(control_parameter_vector,1.0) #17 order_FX_activation
    push!(control_parameter_vector,4.0) #14 alpha_FX_inhibition
    push!(control_parameter_vector,1.0) #15 order_FX_inhibition

   #platlet controls
	platelet_parameter_vector = Float64[]
		push!(platelet_parameter_vector, .005*400) #1 rate constant
	push!(platelet_parameter_vector, 1.6123) #2 power for control function
	push!(platelet_parameter_vector, 2.4279E-9) #3 adjustment in denominator
	push!(platelet_parameter_vector, .01) #4 Epsmax0
	push!(platelet_parameter_vector, .01*1.05)  #5 aida
	push!(platelet_parameter_vector, .001) #koffplatelets

	timing = Float64[]
	push!(timing, 4.25) #time_delay
	push!(timing, .35) #coeff
    
 
	inital_parameter_estimate = vcat(kinetic_parameter_vector, control_parameter_vector, platelet_parameter_vector, timing)	

	(minf, minx, ret) = NLopt.optimize(opt, vec(inital_parameter_estimate))
	println("got $minf at $minx after $count iterations (returned $ret)")
end

