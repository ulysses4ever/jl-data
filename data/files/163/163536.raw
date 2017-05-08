include("DataDictionary.jl")
using PyPlot

# Setup the timescale
TSTART = 0.0
TSTOP = 3.0
Ts = TSTOP/30

# Create dictionary of parameters
data_dictionary = DataDictionary(TSTART,TSTOP,Ts)

experiment_data_dictionary = data_dictionary["EXPERIMENT_DATA_DICTIONARY"]

glc = experiment_data_dictionary["M_glc_D_c"].raw_measurement_array
CAT = experiment_data_dictionary["CAT"].raw_measurement_array

figure("Carbon",figsize=(4,3))

#subplot(1,2,1)
#axis([0,TSTOP,0,40])
#plt[:xticks]([0:1:TSTOP])
#plt[:yticks]([0:10:40])
#ylabel("Glucose (mM)")
#xlabel("Time (h)")

#subplot(1,2,2)
axis([0,TSTOP,0,20])
plt[:xticks]([0:1:TSTOP],fontsize=10)
plt[:yticks]([0:5:20],fontsize=10)
#ylabel("CAT (μM)")
#xlabel("Time (h)")



#species = ["GLC" 54;"CAT" 92]
species = ["CAT" 92]



Tsim = readdlm("Ensemble100/1/Tsim")
Ensemble = Dict()
num_sets = 100

i = 0
while i < num_sets
    i += 1
    if isfile("Ensemble100/$i/X")
        println(i)
        X = readdlm("Ensemble100/$i/X")
        for j in 1:size(species,1)
            key = species[j,1]
            index = species[j,2]
            
            if typeof(index) == Int
                tmp = X[:,index]
            elseif typeof(index) == Tuple{Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
            elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
            else
                throw("Wrong type")
            end
            
            if get(Ensemble,key,777) == 777 # Returning the default value means the key-value pair does not yet exist
                Ensemble[key] = tmp
            else
                Ensemble[key] = [Ensemble[key] tmp]
            end
        end # for j in size(species,1)
    end # if isfile("Ensemble/$i/X")
end # while i < 10395

X = readdlm("Ensemble100/Best/X")

for j in 1:size(species,1)
    key = species[j,1]
    sim = Ensemble[key]
    index = species[j,2]
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if key == "CAT" # Convert from mM to μM
        sim *= 1000
        tmp *= 1000
    end
    
    m = Float64[]
    s = Float64[]
    for i in 1:size(sim,1)
        push!(m,mean(sim[i,:]))
        push!(s,std(sim[i,:]))
    end
    ensemble_size = size(sim,2)
    se = s/sqrt(ensemble_size)
    
#    subplot(1,2,j)
    
    fill_between(vec(Tsim),m+1.96*s,max(0,m-1.96*s),color="black",alpha=1,edgecolor="#AFAFAF")
#    plot(vec(Tsim),m+1.96*s,"blue")
#    plot(vec(Tsim),max(0,m-1.96*s),"blue")
    
    tight_layout()
end

Tsim = readdlm("KO_cyd/1/Tsim")
Ensemble = Dict()
num_sets = 100

i = 0
while i < num_sets
    i += 1
    if isfile("KO_cyd/$i/X")
        println(i)
        X = readdlm("KO_cyd/$i/X")
        for j in 1:size(species,1)
            key = species[j,1]
            index = species[j,2]
            
            if typeof(index) == Int
                tmp = X[:,index]
            elseif typeof(index) == Tuple{Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
            elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
            else
                throw("Wrong type")
            end
            
            if get(Ensemble,key,777) == 777 # Returning the default value means the key-value pair does not yet exist
                Ensemble[key] = tmp
            else
                Ensemble[key] = [Ensemble[key] tmp]
            end
        end # for j in size(species,1)
    end # if isfile("Ensemble/$i/X")
end # while i < 10395

X = readdlm("KO_cyd/Best/X")

for j in 1:size(species,1)
    key = species[j,1]
    sim = Ensemble[key]
    index = species[j,2]
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if key == "CAT" # Convert from mM to μM
        sim *= 1000
        tmp *= 1000
    end
    
    m = Float64[]
    s = Float64[]
    for i in 1:size(sim,1)
        push!(m,mean(sim[i,:]))
        push!(s,std(sim[i,:]))
    end
    ensemble_size = size(sim,2)
    se = s/sqrt(ensemble_size)
    
#    subplot(1,2,j)
    
    fill_between(vec(Tsim),m+1.96*s,max(0,m-1.96*s),color="#DDDDDD",alpha=1,edgecolor="#AFAFAF")
#    plot(vec(Tsim),m+1.96*s,"blue")
#    plot(vec(Tsim),max(0,m-1.96*s),"blue")
    
    tight_layout()
end



Tsim = readdlm("KO_nuo/1/Tsim")
Ensemble = Dict()
num_sets = 100

i = 0
while i < num_sets
    i += 1
    if isfile("KO_nuo/$i/X")
        println(i)
        X = readdlm("KO_nuo/$i/X")
        for j in 1:size(species,1)
            key = species[j,1]
            index = species[j,2]
            
            if typeof(index) == Int
                tmp = X[:,index]
            elseif typeof(index) == Tuple{Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
            elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
            else
                throw("Wrong type")
            end
            
            if get(Ensemble,key,777) == 777 # Returning the default value means the key-value pair does not yet exist
                Ensemble[key] = tmp
            else
                Ensemble[key] = [Ensemble[key] tmp]
            end
        end # for j in size(species,1)
    end # if isfile("Ensemble/$i/X")
end # while i < 10395

X = readdlm("KO_nuo/Best/X")

for j in 1:size(species,1)
    key = species[j,1]
    sim = Ensemble[key]
    index = species[j,2]
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if key == "CAT" # Convert from mM to μM
        sim *= 1000
        tmp *= 1000
    end
    
    m = Float64[]
    s = Float64[]
    for i in 1:size(sim,1)
        push!(m,mean(sim[i,:]))
        push!(s,std(sim[i,:]))
    end
    ensemble_size = size(sim,2)
    se = s/sqrt(ensemble_size)
    
#    subplot(1,2,j)
    
    fill_between(vec(Tsim),m+1.96*s,max(0,m-1.96*s),color="#AFAFAF",alpha=1,edgecolor="#AFAFAF")
#    plot(vec(Tsim),m+1.96*s,"blue")
#    plot(vec(Tsim),max(0,m-1.96*s),"blue")
    
    tight_layout()
end



Tsim = readdlm("Ensemble100/1/Tsim")
Ensemble = Dict()
num_sets = 100

i = 0
while i < num_sets
    i += 1
    if isfile("Ensemble100/$i/X")
        println(i)
        X = readdlm("Ensemble100/$i/X")
        for j in 1:size(species,1)
            key = species[j,1]
            index = species[j,2]
            
            if typeof(index) == Int
                tmp = X[:,index]
            elseif typeof(index) == Tuple{Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
            elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
                tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
            else
                throw("Wrong type")
            end
            
            if get(Ensemble,key,777) == 777 # Returning the default value means the key-value pair does not yet exist
                Ensemble[key] = tmp
            else
                Ensemble[key] = [Ensemble[key] tmp]
            end
        end # for j in size(species,1)
    end # if isfile("Ensemble/$i/X")
end # while i < 10395

X = readdlm("Ensemble100/Best/X")

for j in 1:size(species,1)
    key = species[j,1]
    sim = Ensemble[key]
    index = species[j,2]
    
    if typeof(index) == Int
        tmp = X[:,index]
    elseif typeof(index) == Tuple{Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
    elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
        tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
    else
        throw("Wrong type")
    end
    
    if key == "CAT" # Convert from mM to μM
        sim *= 1000
        tmp *= 1000
    end
    
    m = Float64[]
    s = Float64[]
    for i in 1:size(sim,1)
        push!(m,mean(sim[i,:]))
        push!(s,std(sim[i,:]))
    end
    ensemble_size = size(sim,2)
    se = s/sqrt(ensemble_size)
    
#    subplot(1,2,j)
    
#    fill_between(vec(Tsim),m+1.96*s,max(0,m-1.96*s),color="black",alpha=1,edgecolor="#AFAFAF")
    plot(vec(Tsim),m-1.96*s,"k--",linewidth=2)
#    plot(vec(Tsim),max(0,m-1.96*s),"blue")
    
    tight_layout()
end



