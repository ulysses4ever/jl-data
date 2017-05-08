include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError_AA.jl")
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

data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,59] = 0.001

data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,91] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,60] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,61] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,62] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,63] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,64] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,65] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,66] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,67] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,68] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,69] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,70] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,71] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,72] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,73] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,74] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,75] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,76] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,77] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,78] = 0.2
data_dictionary_best["SATURATION_CONSTANT_ARRAY"][167,79] = 0.2

# Initialize number of parameters to be varied
num_rate = 375
num_sat = 525
num_cont = 34

# Create or read the relevant information
if ~isfile("Ensemble/Best/params")
    # Take rate constants to be varied from data_dictionary_best
    rate = data_dictionary_best["RATE_CONSTANT_ARRAY"]
    # Take saturation constants to be varied from data_dictionary_best
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat = sat_vector[find(sat_vector.>0)]
    # Take control parameters to be varied from data_dictionary_best
    cont = vec(data_dictionary_best["CONTROL_PARAMETER_ARRAY"]')
    # Concatenate into params vector
    params_best = [rate;sat;cont]
    params = copy(params_best)
    # Solve the balance equations and calculate cost
    Tsim_best,X_best = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_best)
    Error_best,Keys = CalcError_AA(experiment_data_dictionary,Tsim_best,X_best)
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
    if ~(num_rate+num_sat+num_cont==length(params_best))
        throw("Wrong number of parameters")
    end
    # Add rate constants to data_dictionary_best
    rate = params_best[1:num_rate]
    data_dictionary_best["RATE_CONSTANT_ARRAY"] = rate
    # Add saturation constants to data_dictionary_best
    sat = params_best[num_rate+1:num_rate+num_sat]
    sat_vector = vec(data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary_best["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary_best["SATURATION_CONSTANT_ARRAY"]))
    # Add control parameters to data_dictionary_best
    cont = params_best[num_rate+num_sat+1:num_rate+num_sat+num_cont]
    data_dictionary_best["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    # Solve the balance equations and calculate cost
    Tsim_best,X_best = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_best)
    Error_best,Keys = CalcError_AA(experiment_data_dictionary,Tsim_best,X_best)
    cost_best = sum(Error_best)
    cost = copy(cost_best)
    # Save the relevant information
    writedlm("Ensemble/Best/Tsim",Tsim_best)
    writedlm("Ensemble/Best/X",X_best)
    writedlm("Ensemble/Best/cost",cost_best)
end

rate_upper_bound = 500000 # mM/hr
rate_lower_bound = 0 # mM/hr # essentially zero
CAT_lower_bound = 0 # mM/hr

enz_deg_upper_bound = 1 # fast degradation
enz_deg_lower_bound = 0 # no degradation

sat_upper_bound = 10 # mM
sat_lower_bound = 0.001 # mM

if ~isfile("Ensemble/num_dir")
    writedlm("Ensemble/num_dir",0)
end

num_dir = convert(Int64,readdlm("Ensemble/num_dir")[1]) # Number of pre-existing directories

num_to_reset = 5 # Number of iterations before resetting to best-fit set
num_iter = 3 # Number of iterations before variance is changed

alpha = (-log(0.5)/10)*2 # Increasing alpha decreases acceptance probability (for cost_new > cost)

for j = 1:1000000

variance = (rem(j,3) == 1)?.15:((rem(j,3) == 2)?.3:.5)

for i in num_iter*(j-1)+1+num_dir:num_iter*(j-1)+num_iter+num_dir # Changes on every iteration
    
    if rem(i,num_to_reset) == 0 # Reset to best
        params = copy(params_best)
        cost = copy(cost_best)
    end
    
    num_indices_to_vary = (rem(i,3) == 1)?6:((rem(i,3) == 2)?4:2)
    
    # Copy data_dictionary
    data_dictionary = deepcopy(data_dictionary_best)
    
    # Perturb parameters
    num_params = num_rate+num_sat+num_cont # Don't vary control parameters

    perturb = ones(num_params)
#    all_indices = collect(99:145)
    all_indices = [99 100 101 102 103 112 113 117 139 145]
    
    indices_to_vary = all_indices[randperm(length(all_indices))][1:num_indices_to_vary]
    
    perturb[indices_to_vary] = exp(variance*randn(length(indices_to_vary)))
    
#    perturb[1:num_params] = exp(variance*randn(num_params)) # Vary all parameters as defined by num_params (e.g., all 618 rate constants and saturation constants)
    
    params_new = params.*perturb
#    p_n = params_new[find(params_new.>0)]
#    p = params[find(params.>0)]
#    println(exp(mean(abs(log(p_n./p)))))

#    p = perturb[find(perturb.!=1)]
#    println(exp(mean(abs(log(p)))))
    
    # Add rate constants to data_dictionary
    rate = params_new[1:num_rate]
    
    rate = min(rate_upper_bound,rate)
    rate[[1:154;156:163]] = max(rate_lower_bound,rate[[1:154;156:163]])
    rate[155] = max(CAT_lower_bound,rate[155]) # rate[155] is CAT synthesis
    
    rate[164:num_rate] = min(enz_deg_upper_bound,rate[164:num_rate])
    rate[164:num_rate] = max(enz_deg_lower_bound,rate[164:num_rate])
    
    params_new[1:num_rate] = rate
    data_dictionary["RATE_CONSTANT_ARRAY"] = rate
    
#    # Add saturation constants to data_dictionary
#    sat = params_new[num_rate+1:num_rate+num_sat]
#    sat = min(sat_upper_bound,sat)
#    sat = max(sat_lower_bound,sat)
#    params_new[num_rate+1:num_rate+num_sat] = sat
#    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
#    sat_vector[find(sat_vector.>0)] = sat
#    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))
#    
#    # Add control parameters to data_dictionary
#    cont = params_new[num_rate+num_sat+1:num_rate+num_sat+num_cont]
#    data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    
    # Solve the balance equations
    tic()
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    time_elapsed = toc()
    
    if time_elapsed < 18 # Should prevent sets with CVODE errors from joining ensemble
                         # May also exclude some sets without CVODE errors
        Error_new,Keys = CalcError_AA(experiment_data_dictionary,Tsim,X)
        cost_new = sum(Error_new)
#        KE = [Error_new Keys]
##        println(sortrows(KE)[end,:])
#        ke = sortrows(KE)[end,:]
#        println(ke[2],": ",ke[1])
        
        acc_prob = exp(alpha*(cost-cost_new))
        
        cost_round = round(cost,3)
        cost_new_round = round(cost_new,3)
        cost_best_round = round(cost_best,3)
        acc_prob_round = round(acc_prob,3)
        
        # If a new best is achieved, overwrite params_best and cost_best and save the relevant information to Best directory
        if cost_new < cost_best
            # Save to Best directory
            params_best = copy(params_new)
            cost_best = copy(cost_new)
            writedlm("Ensemble/Best/Tsim",Tsim)
            writedlm("Ensemble/Best/X",X)
            writedlm("Ensemble/Best/cost",cost_best)
            writedlm("Ensemble/Best/params",params_best)
            println("$i: cost_new = $cost_new_round, cost = $cost_round, best = $cost_best_round, acc_prob = $acc_prob_round, var = $variance, varying $num_indices_to_vary, NEW BEST")
        else
            println("$i: cost_new = $cost_new_round, cost = $cost_round, best = $cost_best_round, acc_prob = $acc_prob_round, var = $variance, varying $num_indices_to_vary")
        end
        
        # If new cost is lower than previous cost, choose new params as reference point for perturbation
        if rand() < acc_prob # Accept all better sets and some worse sets
            # Create directory for next sample and save the relevant information
#            mkdir("Ensemble/$i")
#            writedlm("Ensemble/$i/Tsim",Tsim)
#            writedlm("Ensemble/$i/X",X)
#            writedlm("Ensemble/$i/cost",cost_new)
#            writedlm("Ensemble/$i/params",params_new)
            # Overwrite variables
            params = copy(params_new)
            cost = copy(cost_new)
        end
        
        writedlm("Ensemble/num_dir",i) # Record new number of directories
        
    end # if time_elapsed < 9
    
end # for i in num_iter*(j-1)+1+num_dir:num_iter*(j-1)+num_iter+num_dir

end # for j = 1:10000






