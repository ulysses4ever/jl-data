function Local_sens_fxn(dir)
include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcArea.jl")

# Create directory for sensitivity values
if ~isdir("Sens")
    mkdir("Sens")
end

# Create directory for sample
if ~isdir("Sens/$dir")
    mkdir("Sens/$dir")
end

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.01

# Create dictionary of parameters
data_dictionary_orig = DataDictionary(TSTART,TSTOP,Ts)

# Initialize number of parameters to be varied
num_rate = 163
#num_init = 66
num_init = 0
num_sat = 455
num_cont = 34

# Import params from directory
params = readdlm("Rand180/$dir/params")
rate = params[1:num_rate]
data_dictionary_orig["RATE_CONSTANT_ARRAY"][1:163] = rate
# Add initial conditions to data_dictionary_orig
#init = params[num_rate+1:num_rate+num_init]
#data_dictionary_orig["INITIAL_CONDITION_ARRAY"][init_indices] = init
# Add saturation constants to data_dictionary_orig
sat = params[num_rate+num_init+1:num_rate+num_init+num_sat]
sat_vector = vec(data_dictionary_orig["SATURATION_CONSTANT_ARRAY"])
sat_vector[find(sat_vector.>0)] = sat
data_dictionary_orig["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary_orig["SATURATION_CONSTANT_ARRAY"]))
# Add control parameters to data_dictionary_orig
cont = params[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
data_dictionary_orig["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'

# Get number of saturation constants
sat_vector = vec(data_dictionary_orig["SATURATION_CONSTANT_ARRAY"])
nz_vector = find(sat_vector.>0)

# Solve the balance equations
Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_orig)

# Calculate the area under the CAT curve (AUC)
AUC = CalcArea(Tsim,X[:,92])

# Set perturbation, equal to (p+dp)/p
perturbation = 1.001

Rate = Float64[]
rate_range = 1:num_rate
for i in rate_range
#    println("Rate constant $i")
    # Perturb the ith parameter
    data_dictionary = deepcopy(data_dictionary_orig)
    data_dictionary["RATE_CONSTANT_ARRAY"][i] *= perturbation
    # Solve the balance equations
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    # Calculate the area under the CAT curve (AUC)
    AUC_new = CalcArea(Tsim,X[:,92])
    # Calculate sensitivity value
    sens = ((AUC_new-AUC)/AUC)/(perturbation-1)
    push!(Rate,sens)
end
writedlm("Sens/$dir/Rate",Rate)

Sat = Float64[]
sat_range = 1:num_sat
for i in sat_range
#    println("Saturation constant $i")
    # Perturb the ith parameter
    data_dictionary = deepcopy(data_dictionary_orig)
    data_dictionary["SATURATION_CONSTANT_ARRAY"][nz_vector[i]] *= perturbation
    # Solve the balance equations
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    # Calculate the area under the CAT curve (AUC)
    AUC_new = CalcArea(Tsim,X[:,92])
    # Calculate sensitivity value
    sens = ((AUC_new-AUC)/AUC)/(perturbation-1)
    push!(Sat,sens)
end
writedlm("Sens/$dir/Sat",Sat)

Cont = Float64[]
cont_range = 1:num_cont
for i in cont_range
#    println("Control parameter $i")
    # Perturb the ith parameter
    data_dictionary = deepcopy(data_dictionary_orig)
    tmp = data_dictionary["CONTROL_PARAMETER_ARRAY"]'
    tmp[i] *= perturbation
    data_dictionary["CONTROL_PARAMETER_ARRAY"] = tmp'
    # Solve the balance equations
    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    # Calculate the area under the CAT curve (AUC)
    AUC_new = CalcArea(Tsim,X[:,92])
    # Calculate sensitivity value
    sens = ((AUC_new-AUC)/AUC)/(perturbation-1)
    push!(Cont,sens)
end
writedlm("Sens/$dir/Cont",Cont)
end






