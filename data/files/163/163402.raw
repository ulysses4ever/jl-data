include("DataDictionary.jl")
include("SolveBalances.jl")

function CalcFluxMean.jl

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




num_flux = convert(Int64,readcsv("flux/num_flux")[1])

freq = 1
flux_array = readdlm("flux/$freq")

for i in 2*freq:freq:num_flux
    flux = readdlm("flux/$i")
    flux_array = [flux_array flux]
end

flux_array = sortrows(flux_array')' # This sorts the columns of flux_array, in case timepoints are out of order

t_stop = 1
first_index_above = find(flux_array[1,:].>t_stop)[1] #6887
FA = flux_array[:,1:first_index_above]

num_flux = size(FA,1)-1
num_tp = size(FA,2)-1

mean_flux = zeros(num_flux)
for i in 1:num_flux
    tmp = zeros(num_tp)
    for j in 1:num_tp
        tmp[j] = (FA[1,j+1]-FA[1,j])*(FA[i+1,j+1]+FA[i+1,j])/2
    end
    mean_flux[i] = sum(tmp)
end

writedlm("mean_flux",mean_flux)

end






