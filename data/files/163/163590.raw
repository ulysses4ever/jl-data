function PlotSingle(Tsim,X)

j_range = 1:size(species)[1]
for j in j_range
    str = species[j,1]
    index = species[j,2]
    
    amino_ = [1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16]
    core_ = [1 3 4 5 6 7 2 8]
    
    if j < 9
        figure("Carbon")
        subplot(2,4,core_[j])
    elseif j >= 9 && j < 25
        figure("Energy")
        subplot(4,4,amino_[j-8])
    else
        figure("Amino")
        subplot(5,4,j-8-16)
    end
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if str == "CAT"
        tmp *= 1000
    end
    
    plot(Tsim,tmp,"purple",linewidth=1.5)
    
    tight_layout()
end

end # function PlotSingle(Tsim,X)

#for i in 2000:2009
#    Tsim = readdlm("Ensemble/$i/Tsim")
#    X = readdlm("Ensemble/$i/X")
#    PlotSingle(Tsim,X)
#end

#i = 7000
#Tsim = readdlm("Ensemble/$i/Tsim")
#X = readdlm("Ensemble/$i/X")
#PlotSingle(Tsim,X)

num_dir = convert(Int64,readdlm("Ensemble/num_dir")[1])

Cost = Float64[]
for i in 1:num_dir
    cost = readdlm("Ensemble/$i/cost")[1]
    push!(Cost,cost)
end

best = find(Cost.<165)

#for i in best
#    Tsim = readdlm("Ensemble/$i/Tsim")
#    X = readdlm("Ensemble/$i/X")
#    PlotSingle(Tsim,X)
#end


include("DataDictionary.jl")
include("SolveBalances.jl")
include("CalcError.jl")

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = TSTOP/30

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)

# Initialize number of parameters to be varied
num_rate = 163
#num_init = 66
num_init = 0
num_sat = 455
num_cont = 34

for i in 185:-1:1
    println(i)
    params_best = readdlm("Ensemble/$i/params")
    
    # Add rate constants to data_dictionary
    rate = params_best[1:num_rate]
    #rate[1:154] = max(rate[1:154],70)
    #rate[156:end] = max(rate[156:end],70)
    data_dictionary["RATE_CONSTANT_ARRAY"][1:163] = rate

    # Add initial conditions to data_dictionary
    #    init = params[num_rate+1:num_rate+num_init]
    #    data_dictionary["INITIAL_CONDITION_ARRAY"][init_indices] = init

    # Add saturation constants to data_dictionary
    sat = params_best[num_rate+num_init+1:num_rate+num_init+num_sat]
    sat_vector = vec(data_dictionary["SATURATION_CONSTANT_ARRAY"])
    sat_vector[find(sat_vector.>0)] = sat
    data_dictionary["SATURATION_CONSTANT_ARRAY"] = reshape(sat_vector,size(data_dictionary["SATURATION_CONSTANT_ARRAY"]))

    # Add control parameters to data_dictionary
    #cont = params_best[num_rate+num_init+num_sat+1:num_rate+num_init+num_sat+num_cont]
    #data_dictionary["CONTROL_PARAMETER_ARRAY"] = reshape(cont,2,convert(Int64,length(cont)/2))'

    experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

    Tsim,X = SolveBalances(TSTART,TSTOP,Ts,data_dictionary)
    
end







