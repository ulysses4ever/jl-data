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
num_rate = 326
num_sat = 455
num_cont = 34
num_params = num_rate+num_sat+num_cont

# Create or read the relevant information
if ~isfile("Ensemble/Best/params") # If the best-fit parameter set doesn't exist, create it and solve
    # Take rate constants to be varied from data dictionary
    rate = data_dictionary_best["RATE_CONSTANT_ARRAY"]
    # Take saturation constants to be varied from data dictionary
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat = sat_vector[find(sat_vector.>0)]
    # Take control parameters to be varied from data dictionary
    cont = vec(data_dictionary_best["CONTROL_PARAMETER_ARRAY"]')
    # Concatenate into params vector
    params = [rate;sat;cont]
    # Save parameter set as best-fit set
    params_best = copy(params)
    writedlm("Ensemble/Best/params",params_best)
else
    # Read the best-fit parameter set
    params = readdlm("Ensemble/Best/params")
    params_best = copy(params)
    # Check that set is of correct length
    if ~(num_rate+num_sat+num_cont==length(params_best))
        throw("Wrong number of parameters")
    end
    # Add rate constants to data dictionary
    rate = params_best[1:num_rate]
    data_dictionary_best["RATE_CONSTANT_ARRAY"] = rate
    # Add saturation constants to data dictionary
    sat = params_best[num_rate+1:num_rate+num_sat]
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary_best["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary_best["SATURATION_CONSTANT_ARRAY"]))
    # Add control parameters to data dictionary
    cont = params_best[num_rate+num_sat+1:num_rate+num_sat+num_cont]
    data_dictionary_best["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
end

# Solve the balance equations and calculate cost
Tsim_best,X_best = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_best)
Error,Keys = CalcError(experiment_data_dictionary,Tsim_best,X_best) # Keys stores the species names in the same order as in Error
cost = sum(Error)
cost_best = copy(cost)

# Save the solution and cost
writedlm("Ensemble/Best/Tsim",Tsim_best)
writedlm("Ensemble/Best/X",X_best)
writedlm("Ensemble/Best/cost",cost_best)

rate_upper_bound = 500000 # mM/hr
rate_lower_bound = 0 # mM/hr
CAT_lower_bound = 0 # mM/hr

enz_deg_upper_bound = 1 # fast degradation
enz_deg_lower_bound = 0 # no degradation

sat_upper_bound = 10 # mM
sat_lower_bound = 0.001 # mM

# If it doesn't exist already, create a file that records how many samples (directories) exist
if ~isfile("Ensemble/num_dir")
    writedlm("Ensemble/num_dir",0)
end

num_dir = convert(Int64,readdlm("Ensemble/num_dir")[1]) # Number of pre-existing directories

num_to_reset = 5 # Number of iterations before resetting to best-fit set
num_iter = 3 # Number of iterations before variance is changed
total_iter = num_iter*10000 # Total number of iterations to be performed (should be divisible by num_iter)

# Increasing alpha decreases the probability of accepting sets that are worse than the current set
alpha = log(2)/5 # alpha is currently set such that a cost function that is worse by 5 will have an acceptance probability of 0.5

for j = 1:convert(Int64,total_iter/num_iter)

variance = (rem(j,3) == 1)?0.1:((rem(j,3) == 2)?0.5:1.5) # The variance will change between 0.1, 0.5, and 1.5 in this case

for i in num_iter*(j-1)+1:num_iter*(j-1)+num_iter
    
    if rem(i,num_to_reset) == 0 # Every few iterations, reset parameters to best-fit set
        params = copy(params_best)
        cost = copy(cost_best)
    end
    
    num_indices_to_vary = (rem(i,3) == 1)?8:((rem(i,3) == 2)?4:2) # The number of indices to be varied will change between 8, 4, and 2 in this case
    
    # Copy data_dictionary
    data_dictionary = deepcopy(data_dictionary_best)
    
    # Perturb parameters
    perturb = ones(num_params)
    indices_to_vary = randperm(num_params)[1:num_indices_to_vary] # Choose parameters to vary on this iteration
    perturb[indices_to_vary] = exp(variance*randn(length(indices_to_vary))) # Use the normal distribution of random numbrs
    params_new = params.*perturb
    
    # Ensure that the rate constants are within the bounds, then add them to the data dictionary
    rate = params_new[1:num_rate]
    rate = min(rate_upper_bound,rate)
    rate[[1:154;156:163]] = max(rate_lower_bound,rate[[1:154;156:163]])
    rate[155] = max(CAT_lower_bound,rate[155]) # rate[155] is CAT synthesis rate constant
    rate[164:num_rate] = min(enz_deg_upper_bound,rate[164:num_rate])
    rate[164:num_rate] = max(enz_deg_lower_bound,rate[164:num_rate])
    params_new[1:num_rate] = rate
    data_dictionary["RATE_CONSTANT_ARRAY"] = rate
    
    # Ensure that the saturation constants are within the bounds, then add them to the data dictionary
    sat = params_new[num_rate+1:num_rate+num_sat]
    sat = min(sat_upper_bound,sat)
    sat = max(sat_lower_bound,sat)
    params_new[num_rate+1:num_rate+num_sat] = sat
    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"])) # Vector of saturation constants must be reshaped into a matrix
    
    # Add the control parameters to the data dictionary (no bounds)
    cont = params_new[num_rate+num_sat+1:num_rate+num_sat+num_cont]
    data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    
    # Solve the balance equations
    tic()
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    time_elapsed = toc() # Switch to toq() to suppress output
    
    if time_elapsed < 8 # This should prevent sets with CVODE errors from joining the ensemble
                        # It may also exclude some sets without CVODE errors
        Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
        cost_new = sum(Error)
        
        acc_prob = exp(alpha*(cost-cost_new)) # The probability of accepting the next set
        
        # Round cetain metrics for printing to output
        num_decimals = 2
        cost_round = round(cost,num_decimals)
        cost_new_round = round(cost_new,num_decimals)
        cost_best_round = round(cost_best,num_decimals)
        acc_prob_round = round(acc_prob,num_decimals)
        
        # If a new best is achieved, overwrite params_best and cost_best and save the relevant information to Best directory
        if cost_new < cost_best
            # Save to Best directory
            params_best = copy(params_new)
            cost_best = copy(cost_new)
            writedlm("Ensemble/Best/Tsim",Tsim)
            writedlm("Ensemble/Best/X",X)
            writedlm("Ensemble/Best/cost",cost_best)
            writedlm("Ensemble/Best/params",params_best)
            println("$i: cost_new = $cost_new_round, cost = $cost_round, best = $cost_best_round, acc_prob = $acc_prob_round, var = $variance, varying $num_indices_to_vary, NEW BEST") # You may print num_dir instead of i if you prefer
        else
            println("$i: cost_new = $cost_new_round, cost = $cost_round, best = $cost_best_round, acc_prob = $acc_prob_round, var = $variance, varying $num_indices_to_vary")
        end
        
        # Accept all better sets and some worse sets
        # If new set is accepted, it becomes the reference point for the next perturbation
        if rand() < acc_prob
            # If the set is accepted, increase the number of samples by one
            num_dir += 1
            # Create a directory for the next sample and save the relevant information
            mkdir("Ensemble/$num_dir")
            writedlm("Ensemble/$num_dir/Tsim",Tsim)
            writedlm("Ensemble/$num_dir/X",X)
            writedlm("Ensemble/$num_dir/cost",cost_new)
            writedlm("Ensemble/$num_dir/params",params_new)
            # Overwrite variables
            params = copy(params_new)
            cost = copy(cost_new)
        end
        
        writedlm("Ensemble/num_dir",num_dir) # Record new number of samples (directories)
        
    end
    
end

end
