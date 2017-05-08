include("DataDictionary.jl")
include("SolveBalances.jl")
include("WriteFluxes.jl")
include("CalcError.jl")

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.1

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 163
num_init = 0
num_sat = 455
num_cont = 34

if ~isfile("Ensemble18000/dir")
    writedlm("Ensemble18000/dir",1)
end

i_range = 1:18000
for i in i_range
    println(i)
    # Update dir
    writedlm("Ensemble18000/dir",i)
    # Read the relevant information
    params = readdlm("Ensemble18000/$i/params")
    # Add saturation constant for cys on R_CAT
    params = [params[1:163+250];.01;params[163+251:end]]
    # Check that params is of correct length
    if ~(num_rate+num_init+num_sat+num_cont==length(params))
        throw("Wrong number of parameters")
    end
    # Add rate constants to data_dictionary
    rate = params[1:num_rate]
    data_dictionary["RATE_CONSTANT_ARRAY"][1:163] = rate
    # Add saturation constants to data_dictionary
    sat = params[num_rate+num_init+1:num_rate+num_init+num_sat]
    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))
    # Add control parameters to data_dictionary
    cont = params[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
    data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
    # Solve the balance equations
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    cost = CalcError(experiment_data_dictionary,Tsim,X)
    # Save the relevant information
    writedlm("Ensemble18000/$i/Tsim",Tsim)
    writedlm("Ensemble18000/$i/X",X)
    writedlm("Ensemble18000/$i/cost",cost)
    writedlm("Ensemble18000/$i/params",params)
    # Perform WriteFluxes
    WriteFluxes(i)
end






