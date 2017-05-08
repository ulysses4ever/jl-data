include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")
using PyPlot

# Create Ensemble directory if it doesn't already exist
if ~isdir("Ensemble")
    mkdir("Ensemble")
end

# Create Best directory if it doesn't already exist
if ~isdir("Ensemble/Best")
    mkdir("Ensemble/Best")
end

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.1

# Create dictionary of parameters
data_dictionary_best = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary_best["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 163
num_init = 0
num_sat = 455
num_cont = 34

# Create or read the relevant information
if ~isfile("Ensemble/Best/params")
    # Take rate constants to be varied from data_dictionary_best
    rate = data_dictionary_best["RATE_CONSTANT_ARRAY"][1:163]
    # Take initial conditions to be varied from data_dictionary_best
#    init = data_dictionary_best["INITIAL_CONDITION_ARRAY"][init_indices]
    # Take saturation constants to be varied from data_dictionary_best
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat = sat_vector[find(sat_vector.>0)]
    # Take control parameters to be varied from data_dictionary_best
    cont = vec(data_dictionary_best["CONTROL_PARAMETER_ARRAY"]')
    # Concatenate into params vector
#    params = [rate;init;sat;cont]
    params_best = [rate;sat;cont]
    params = copy(params_best)
    # Solve the balance equations and calculate cost
    Tsim_best,X_best = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_best)
    Error_best,Keys = CalcError(experiment_data_dictionary,Tsim_best,X_best)
    cost_best = sum(Error_best)
    cost = copy(cost_best)
    # Save the relevant information
    writedlm("Ensemble/Best/Tsim",Tsim_best)
    writedlm("Ensemble/Best/X",X_best)
    writedlm("Ensemble/Best/cost",cost_best)
    writedlm("Ensemble/Best/params",params_best)
else
    # Read the relevant information
    params_best = readdlm("Ensemble/Best/params")
    params = copy(params_best)
    # Check that params is of correct length
    if ~(num_rate+num_init+num_sat+num_cont==length(params_best))
        throw("Wrong number of parameters")
    end
    # Add rate constants to data_dictionary_best
    rate = params_best[1:num_rate]
    data_dictionary_best["RATE_CONSTANT_ARRAY"][1:163] = rate
    # Add initial conditions to data_dictionary_best
#    init = params[num_rate+1:num_rate+num_init]
#    data_dictionary_best["INITIAL_CONDITION_ARRAY"][init_indices] = init
    # Add saturation constants to data_dictionary_best
    sat = params_best[num_rate+num_init+1:num_rate+num_init+num_sat]
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary_best["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary_best["SATURATION_CONSTANT_ARRAY"]))
    # Add control parameters to data_dictionary_best
    cont = params_best[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
    data_dictionary_best["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    # Solve the balance equations and calculate cost
    Tsim_best,X_best = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_best)
    Error_best,Keys = CalcError(experiment_data_dictionary,Tsim_best,X_best)
    cost_best = sum(Error_best)
    cost = copy(cost_best)
    # Save the relevant information
    writedlm("Ensemble/Best/Tsim",Tsim_best)
    writedlm("Ensemble/Best/X",X_best)
    writedlm("Ensemble/Best/cost",cost_best)
end

#variance = .03 # Equates to average perturbation of 2.4%, "maximum" perturbation of about 3.2%
num_iter = 40

for j = 1:10000

#variance = (rem(j,3) == 1)?.005:((rem(j,3) == 2)?.02:.05)
variance = (rem(j,3) == 1)?.002:((rem(j,3) == 2)?.0063:.02)

i_range = num_iter*(j-1)+1:num_iter*(j-1)+num_iter
for i in i_range
#    # Create directory for next sample
#    mkdir("Ensemble/$i")
    
    # Copy data_dictionary
    data_dictionary = deepcopy(data_dictionary_best)
    
    # Perturb parameters
#    num_params = num_rate+num_sat # Don't vary control parameters
    num_params = num_rate # Don't vary saturation constants or control parameters
    indices_to_vary = randperm(num_params)[1:50] # Choose parameters to vary on this iteration
    perturb = ones(length(params))
    perturb[indices_to_vary] = exp(variance*randn(length(indices_to_vary)))
#    params_new = params.*perturb;
    params_new = deepcopy(params)
    # Add rate constants to data_dictionary
#    rate = params_new[1:num_rate]
    rate = params_new[1:num_rate]
#    rate = min(10000,rate)
##    rate[find(rate.>0)] = max(10,rate[find(rate.>0)])
#    rate[[1:154;156:num_rate]] = max(1,rate[[1:154;156:num_rate]]) # rate[155] is CAT synthesis
#    params_new[1:num_rate] = rate
    data_dictionary["RATE_CONSTANT_ARRAY"][1:163] = rate
    
    # Add saturation constants to data_dictionary
    sat = params_new[num_rate+num_init+1:num_rate+num_init+num_sat]
#    sat = min(1,sat)
#    sat = max(0.01,sat)
#    params_new[num_rate+num_init+1:num_rate+num_init+num_sat] = sat
    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))
    
    # Add control parameters to data_dictionary
    cont = params_new[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
    data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    
    # Switch certain enzymes on/off
    enz_indices = [106;199;207;221;230:266] # Define indices to be potentially varied
#    enz_indices = [106;196:199;257;265:266] # Define indices to be potentially varied
    num_enz = length(enz_indices)
    indices_to_vary = randperm(num_enz)[1:2] # Choose a few enzymes to vary on this iteration
    init = deepcopy(data_dictionary["INITIAL_CONDITION_ARRAY"])
    init[enz_indices[indices_to_vary]] = round(rand(length(indices_to_vary)))
    data_dictionary["INITIAL_CONDITION_ARRAY"] = deepcopy(init)
    
    # Solve the balance equations and calculate cost
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    Error_new,Keys = CalcError(experiment_data_dictionary,Tsim,X)
    cost_new = sum(Error_new)
    
    # If new cost is lower than previous cost, choose new params as reference point for perturbation
    if cost_new < cost
        params = copy(params_new)
        cost = copy(cost_new)
    end
    
    # If a new best is achieved, overwrite params_best and cost_best and save the relevant information to Best directory
    if cost_new < cost_best
        params_best = copy(params_new)
        cost_best = copy(cost_new)
        writedlm("Ensemble/Best/Tsim",Tsim)
        writedlm("Ensemble/Best/X",X)
        writedlm("Ensemble/Best/cost",cost_best)
        writedlm("Ensemble/Best/params",params_best)
        writedlm("initial_condition.dat",init)
        println("$i: cost = $cost_new, best = $cost_best, NEW BEST, var = $variance")
    else
        println("$i: cost = $cost_new, best = $cost_best, var = $variance")
    end
end

end






