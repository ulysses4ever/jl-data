include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")
include("CalcSat.jl")
using PyPlot

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.1

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)

# Initialize number of parameters to be varied
num_rate = 163
#num_init = 66
num_init = 0
num_sat = 455
num_cont = 34

best_params = readdlm("best_params")

# Add rate constants to data_dictionary
rate = best_params[1:num_rate]
data_dictionary["RATE_CONSTANT_ARRAY"][1:163] = rate

# Add saturation constants to data_dictionary
sat = best_params[num_rate+num_init+1:num_rate+num_init+num_sat]
sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
sat_vector[find(sat_vector.>0)] = sat
data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))

experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)

Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
cost = sum(Error)

println("cost: ",cost)

# Set saturation constants equal to average species values
saturation_constants = CalcSat(experiment_data_dictionary,X)
sat_array = data_dictionary["SATURATION_CONSTANT_ARRAY"][:,1:103]
for i in 1:size(sat_array,2)
    sat_column = sat_array[:,i]
    sat_column[find(sat_column.>0)] = saturation_constants[i]
    sat_array[:,i] = sat_column
end

#data_dictionary["SATURATION_CONSTANT_ARRAY"][:,1:103] = sat_array

# Save to disk
sat_vector = vec(sat_array)
sat = sat_vector[find(sat_vector.>0)]
best_params[num_rate+num_init+1:num_rate+num_init+num_sat] = sat
writedlm("best_params",best_params)






