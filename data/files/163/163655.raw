include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = TSTOP/300

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 326
num_sat = 455
num_cont = 34

if ~isdir("Rand100")
    mkdir("Rand100")
end

Params = readdlm("params_rand100")

num_sets = size(Params,2)

i = 1
index = 1
reached_100 = false

while reached_100 == false
    params = vec(Params[:,i])
    
    # Check that params is of correct length
    if ~(num_rate+num_sat+num_cont==length(params) || num_rate+num_sat==length(params))
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
        
    # Solve the balance equations
    tic()
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    time_elapsed = toc()
    
    if time_elapsed < 7
        # Save the relevant information
        if ~isdir("Rand100/$index")
            mkdir("Rand100/$index")
        end
        
        Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
        KE = [Keys Error]
        
        writedlm("Rand100/$index/KE",KE)
        writedlm("Rand100/$index/params",params)
        writedlm("Rand100/$index/X",X)
        writedlm("Rand100/$index/time_elapsed",time_elapsed)
        
        index += 1
    end
    if index > 100
        reached_100 = true
    end
    i += 1
end

index -= 1
writedlm("Rand100/num_sets",index)






