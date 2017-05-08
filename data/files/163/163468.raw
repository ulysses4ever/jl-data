include("DataDictionary.jl")
include("SatArray.jl")
include("SolveBalances.jl")
include("CalcArea.jl")

# Create directory for sensitivity values
if ~isdir("Sens")
    mkdir("Sens")
end

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = 0.01

# Create dictionary of parameters
data_dictionary_orig = DataDictionary(TSTART,TSTOP,Ts)

# Get number of saturation constants
sat_array = SatArray()
(NREACTIONS,NSPECIES) = size(sat_array);
sat_vector = vec(sat_array)
nz_vector = find(sat_vector.>0)

# Solve the balance equations
Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary_orig)

# Calculate the area under the CAT curve (AUC)
AUC = CalcArea(Tsim,X[:,92])

# Set perturbation, equal to (p+dp)/p
perturbation = 1.001

Rate = Float64[]
rate_range = 1:163
for i in rate_range
    println(i)
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
writedlm("Sens/Rate",Rate)

Sat = Float64[]
sat_range = 1:452
for i in sat_range
    println(i)
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
writedlm("Sens/Sat",Sat)

Cont = Float64[]
cont_range = 1:34
for i in cont_range
    println(i)
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
writedlm("Sens/Cont",Cont)






