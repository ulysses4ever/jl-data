include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")
include("Plot.jl")
include("PlotOld.jl")
using PyPlot

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.01

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)
experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

# Initialize number of parameters to be varied
num_rate = 163
#num_init = 66
num_init = 0
num_sat = 455
num_cont = 34

# Read the relevant information
params = readdlm("Ensemble/Best/params")

# Check that params is of correct length
if ~(num_rate+num_init+num_sat+num_cont==length(params))
    throw("Wrong number of parameters")
end

# Add rate constants to data_dictionary
rate = params[1:num_rate]
data_dictionary["RATE_CONSTANT_ARRAY"][1:163] = rate

## Create array of non-experimental indices
#data_indices = Int64[]
#for (key,value) in experiment_data_dictionary
#    push!(data_indices,value.model_index)
#end
#sort!(data_indices)
##init_indices = collect(1:103)
#init_indices = collect(1:92) # Allow o2, co2, pi, nh4, so4, h, h2o to be higher
#deleteat!(init_indices,data_indices)

## ICs from BioNumbers
#IC = [
#1 3.48;
#2 0.60;
#3 0.272;
#5 0.218;
#4 0.167;
#6 0.008;
#7 2.13;
#8 0.399;
##55 2.67;
##56 2.67;
#12 0.808;
#13 0.808;
#14 0.111;
#15 0.138;
#17 0.276;
#16 0.398;
#18 0.098;
##62 0.955;
##61 0.595;
##60 4.27;
#102 0.195;
#103 0.062;
#100 1.47;
#101 0.1;
#]

## Set non-experimental initial conditions to BioNumbers mean
#data_dictionary["INITIAL_CONDITION_ARRAY"][init_indices] = mean(IC[:,2])

## Set certain non-experimental initial conditions to BioNumbers values
#for i in 1:size(IC)[1]
#    data_dictionary["INITIAL_CONDITION_ARRAY"][convert(Int64,IC[i,1])] = IC[i,2]
#end

# Add saturation constants to data_dictionary
sat = params[num_rate+num_init+1:num_rate+num_init+num_sat]
sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
sat_vector[find(sat_vector.>0)] = sat
data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))

# Add control parameters to data_dictionary
cont = params[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'
data_dictionary["CONTROL_PARAMETER_ARRAY"][13:15,1] = 0

# Solve the balance equations and calculate cost
Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
Error,Keys = CalcError(experiment_data_dictionary,Tsim,X)
cost = sum(Error)

## Read fluxes
#num_flux = convert(Int64,readdlm("flux/num_flux")[1])
#Flux = readdlm("flux/1")
#rm("flux/1")
#for i = 2:num_flux
#    flux = readdlm("flux/$i")
#    rm("flux/$i")
#    Flux = [Flux flux]
#end
#rm("flux/num_flux")
#rm("flux")
#writedlm("Flux",Flux)

Flux = 1
PlotOld(Tsim,X,Flux,data_dictionary)






