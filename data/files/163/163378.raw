function DataDictionary(TSTART,TSTOP,Ts)
include("DataFile.jl")

# Load the data_dictionary
data_dictionary = DataFile(TSTART,TSTOP,Ts)

# Import rate constants
rate_constant_vector = vec(abs(float(open(readdlm,"rate_constant.dat"))))
data_dictionary["RATE_CONSTANT_ARRAY"] = rate_constant_vector

# Import initial conditions
initial_condition_array = vec(abs(float(open(readdlm,"initial_condition.dat"))))
data_dictionary["INITIAL_CONDITION_ARRAY"] = initial_condition_array

# Import saturation constants
saturation_constant_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
saturation_constant_vector[find(saturation_constant_vector.>0)] = readdlm("saturation_constant.dat")
data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(saturation_constant_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))

# Import control parameters
control_constant = vec(abs(float(open(readdlm,"control_constant.dat"))))
num_row = convert(Int64,length(control_constant)/2)
data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(control_constant,2,num_row)'

return data_dictionary
end
