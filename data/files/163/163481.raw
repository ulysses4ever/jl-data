include("DataDictionary.jl")
include("SatArray.jl")
include("SolveBalances.jl")
include("CalcError.jl")
using PyPlot

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.1

# Create dictionary of parameters
data_dictionary_orig = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary_orig["EXPERIMENT_DATA_DICTIONARY"]

data_indices = Int64[]
for (key,value) in experiment_data_dictionary
    push!(data_indices,value.model_index)
end
sort!(data_indices)

init_indices = collect(1:103)
deleteat!(init_indices,data_indices)

# Create best directory if it doesn't already exist
if ~isdir("Best")
    mkdir("Best")
else
    data_dictionary_orig["RATE_CONSTANT_ARRAY"][1:163] = readdlm("Best/rate")
    data_dictionary_orig["INITIAL_CONDITION_ARRAY"][init_indices] = readdlm("Best/init")
    data_dictionary_orig["CONTROL_PARAMETER_ARRAY"] = readdlm("Best/cont")
    data_dictionary_orig["SATURATION_CONSTANT_ARRAY"] = readdlm("Best/sat")
end

# Get number of saturation constants
sat_array = SatArray()
(NREACTIONS,NSPECIES) = size(sat_array);
sat_vector = vec(sat_array)
nz_vector = find(sat_vector.>0)

# Get the number of parameters of each type
rate_range = 1:length(data_dictionary_orig["RATE_CONSTANT_ARRAY"][1:163])
init_range = 1:length(data_dictionary_orig["INITIAL_CONDITION_ARRAY"][init_indices])
cont_range = 1:length(data_dictionary_orig["CONTROL_PARAMETER_ARRAY"])
sat_range = 1:length(nz_vector)

# Solve the balance equations and calculate cost
Tsim_orig,X_orig = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_orig)
cost_orig = CalcError(experiment_data_dictionary,Tsim_orig,X_orig)

# Create best dictionary and best cost
data_dictionary_best = deepcopy(data_dictionary_orig)
cost_best = copy(cost_orig)

i_range = 1:1000
k_range = 1:3 # Number of attempts at improving fit by varying one parameter
for i in i_range
    println("i = ",i)
    # Set perturbation bound
    bound = (rem(i,3)==1)?3:((rem(i,3)==2)?1.5:1.1)
    println("bound = ",bound)
    # Vary rate constants
    println("Perturbing rate constants...")
    for j in rate_range
        println("j = ",j)
        for k in k_range
            # Perturb parameters
            data_dictionary = deepcopy(data_dictionary_best)
            data_dictionary["RATE_CONSTANT_ARRAY"][j] *= exp(log(1/bound)+rand()*(log(bound)-log(1/bound)))
            # Solve the balance equations and calculate cost
            Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
            cost = CalcError(experiment_data_dictionary,Tsim,X)
            # If cost is lower, replace best
            if cost < cost_best
                data_dictionary_best = deepcopy(data_dictionary)
                cost_best = copy(cost)
                writedlm("Best/rate",data_dictionary_best["RATE_CONSTANT_ARRAY"][1:163])
                writedlm("Best/Tsim",Tsim)
                writedlm("Best/X",X)
                writedlm("Best/cost",cost_best)
                println("Cost: ",cost," Best: ",cost_best," NEW BEST")
            else
                println("Cost: ",cost," Best: ",cost_best)
            end
        end
    end
    # Vary initial conditions
    println("Perturbing initial conditions...")
    for j in init_range
        println("j = ",j)
        for k in k_range
            # Perturb parameters
            data_dictionary = deepcopy(data_dictionary_best)
            data_dictionary["INITIAL_CONDITION_ARRAY"][j] *= exp(log(1/bound)+rand()*(log(bound)-log(1/bound)))
            # Solve the balance equations and calculate cost
            Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
            cost = CalcError(experiment_data_dictionary,Tsim,X)
            # If cost is lower, replace best
            if cost < cost_best
                data_dictionary_best = deepcopy(data_dictionary)
                cost_best = copy(cost)
                writedlm("Best/init",data_dictionary_best["INITIAL_CONDITION_ARRAY"][init_indices])
                writedlm("Best/Tsim",Tsim)
                writedlm("Best/X",X)
                writedlm("Best/cost",cost_best)
                println("Cost: ",cost," Best: ",cost_best," NEW BEST")
            else
                println("Cost: ",cost," Best: ",cost_best)
            end
        end
    end
    # Vary control parameters
    println("Perturbing control parameters...")
    for j in cont_range
        println("j = ",j)
        for k in k_range
            # Perturb parameters
            data_dictionary = deepcopy(data_dictionary_best)
            data_dictionary["CONTROL_PARAMETER_ARRAY"][j] *= exp(log(1/bound)+rand()*(log(bound)-log(1/bound)))
            # Solve the balance equations and calculate cost
            Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
            cost = CalcError(experiment_data_dictionary,Tsim,X)
            # If cost is lower, replace best
            if cost < cost_best
                data_dictionary_best = deepcopy(data_dictionary)
                cost_best = copy(cost)
                writedlm("Best/cont",data_dictionary_best["CONTROL_PARAMETER_ARRAY"])
                writedlm("Best/Tsim",Tsim)
                writedlm("Best/X",X)
                writedlm("Best/cost",cost_best)
                println("Cost: ",cost," Best: ",cost_best," NEW BEST")
            else
                println("Cost: ",cost," Best: ",cost_best)
            end
        end
    end
    # Vary saturation constants
    println("Perturbing saturation constants...")
    for j in sat_range
        println("j = ",j)
        for k in k_range
            # Perturb parameters
            data_dictionary = deepcopy(data_dictionary_best)
            sat_vector_tmp = copy(sat_vector)
            sat_vector_tmp[nz_vector[j]] *= exp(log(1/bound)+rand()*(log(bound)-log(1/bound)))
            sat_vector_tmp = reshape(sat_vector_tmp,NREACTIONS,NSPECIES)
            data_dictionary["SATURATION_CONSTANT_ARRAY"] = sat_vector_tmp
            # Solve the balance equations and calculate cost
            Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
            cost = CalcError(experiment_data_dictionary,Tsim,X)
            # If cost is lower, replace best
            if cost < cost_best
                data_dictionary_best = deepcopy(data_dictionary)
                cost_best = copy(cost)
                writedlm("Best/sat",data_dictionary_best["SATURATION_CONSTANT_ARRAY"])
                writedlm("Best/Tsim",Tsim)
                writedlm("Best/X",X)
                writedlm("Best/cost",cost_best)
                println("Cost: ",cost," Best: ",cost_best," NEW BEST")
            else
                println("Cost: ",cost," Best: ",cost_best)
            end
        end
    end
end






