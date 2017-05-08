include("DataDictionary.jl")
include("SolveBalances.jl")

function CalcYield_KO_all(set_number)

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

# Load params
params = readdlm("Ensemble100/$set_number/params")
params[[71;72;74]] = 0 # Knock out all three M_h_e producing reactions (cyd, app, nuo)

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
#Error_new,Keys = CalcError(experiment_data_dictionary,Tsim,X)
#cost_new = sum(Error_new)

CAT_carbon_number = 1175; #CAT Carbon Number
reactant_carbon_numbers = [6;3;4;4;3;5;2;6;6;6;6;5;9;5;3;4;11;9;5] #w/o arg and glu

CAT = X[:,92]

glc = X[:,54]
ala = X[:,80]
#arg = X[:,43]
asn = X[:,76]
asp = X[:,73]
cys = X[:,77]
#glu = X[:,90]
gln = X[:,91]
gly = X[:,74]
his = X[:,79]
ile = X[:,75]
leu = X[:,89]
lys = X[:,78]
met = X[:,88]
phe = X[:,81]
pro = X[:,82]
ser = X[:,83]
thr = X[:,84]
trp = X[:,85]
tyr = X[:,86]
val = X[:,87]

Reactants = [glc[1]-glc[end];
ala[1]-ala[end];
asn[1]-asn[end];
asp[1]-asp[end];
cys[1]-cys[end];
gln[1]-gln[end];
gly[1]-gly[end];
his[1]-his[end];
ile[1]-ile[end];
leu[1]-leu[end];
lys[1]-lys[end];
met[1]-met[end];
phe[1]-phe[end];
pro[1]-pro[end];
ser[1]-ser[end];
thr[1]-thr[end];
trp[1]-trp[end];
tyr[1]-tyr[end];
val[1]-val[end]]

CarbonConsumed = sum(Reactants.*reactant_carbon_numbers)
CarbonProduced = (CAT[end]-CAT[1])*CAT_carbon_number
yield = CarbonProduced/CarbonConsumed

if ~isdir("KO_all")
    mkdir("KO_all")
end

if ~isdir("KO_all/$set_number")
    mkdir("KO_all/$set_number")
end

writedlm("KO_all/$set_number/params",params)
writedlm("KO_all/$set_number/Tsim",Tsim)
writedlm("KO_all/$set_number/X",X)
writedlm("KO_all/$set_number/yield",yield)

end

for i in 1:100
    println(i)
    CalcYield_KO_all(i)
end






