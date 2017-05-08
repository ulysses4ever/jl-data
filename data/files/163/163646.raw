include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.1

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 326
num_sat = 455
num_cont = 34

# Create Ensemble directory if it doesn't already exist
if ~isdir("Ensemble")
    mkdir("Ensemble")
end

for i in 1:100
    params = readdlm("Ensemble100/$i/params")
    # Check that params is of correct length
    if ~(num_rate+num_sat+num_cont==length(params))
        throw("Wrong number of parameters")
    end
    # Add rate constants to data_dictionary
    rate = params[1:num_rate]
    data_dictionary["RATE_CONSTANT_ARRAY"] = rate
    # Add saturation constants to data_dictionary
    sat = params[num_rate+1:num_rate+num_sat]
    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))
    # Add control parameters to data_dictionary
    cont = params[num_rate+num_sat+1:num_rate+num_sat+num_cont]
    data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    # Solve the balance equations and calculate cost
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
    KE = [Keys Error]
    cost = sum(Error)
    # Save the relevant information
    mkdir("Ensemble/$i")
    writedlm("Ensemble/$i/params",params)
    writedlm("Ensemble/$i/Tsim",Tsim)
    writedlm("Ensemble/$i/X",X)
    writedlm("Ensemble/$i/cost",cost)
    writedlm("Ensemble/$i/KE",KE)
end






