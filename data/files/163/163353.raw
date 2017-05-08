include("DataDictionary.jl")
include("SolveBalances.jl")

# Create Cluster directory if it doesn't already exist
if ~isdir("Cluster")
    mkdir("Cluster")
end

# Create Best directory if it doesn't already exist
if ~isdir("Cluster/Best")
    mkdir("Cluster/Best")
end

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = TSTOP/30

# Create dictionary of parameters
data_dictionary_best = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary_best["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 326
num_sat = 455
num_cont = 34

# Read the relevant information
params_best = readdlm("Cluster/Best/params")
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
# Save the relevant information
writedlm("Cluster/Best/Tsim",Tsim_best)
writedlm("Cluster/Best/X",X_best)

percent_variation = 1

for i in 1:163
    println(i)
    for j in i:163
        params = copy(params_best)
        params[i] *= 1+percent_variation/100
        params[j] *= 1+percent_variation/100
        # Copy data_dictionary
        data_dictionary = deepcopy(data_dictionary_best)
        # Add rate constants to data_dictionary
        rate = params[1:num_rate]
        data_dictionary["RATE_CONSTANT_ARRAY"] = rate
        # Solve the balance equations and calculate cost
        Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
        # Create string for new directory
        str = "$i"*"_$j"
        println(str)
        # Create new directory
        mkdir("Cluster/$str")
        # Save the relevant information
        writedlm("Cluster/$str/Tsim",Tsim)
        writedlm("Cluster/$str/X",X)
        # Compute norm
        X_norm = norm(X[:,92]-X_best[:,92])
        writedlm("Cluster/$str/X_norm",X_norm)
    end
end






