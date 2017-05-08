function SaveData(i_range,species)
j_range = 1:size(species)[1]

# Initialize dictionary
data = Dict()

for i in i_range
    if rem(i,100)==0
        println(i)
    end
    X = readdlm("./Ensemble18000/$i/X")
    for j in j_range
        str = species[j,1]
        index = species[j,2]
        # Can handle single species or sums of three (AXP, GXP, etc.)
        if typeof(index) == Int
            tmp = X[:,index]
        elseif typeof(index) == Tuple{Int,Int,Int}
            tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]
        elseif typeof(index) == Tuple{Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int,Int}
            tmp = X[:,index[1]]+X[:,index[2]]+X[:,index[3]]+X[:,index[4]]+X[:,index[5]]+X[:,index[6]]+X[:,index[7]]+X[:,index[8]]+X[:,index[9]]+X[:,index[10]]+X[:,index[11]]+X[:,index[12]]
        else
            throw("Wrong type")
        end
        # On first iteration, create; afterwards, concatenate
        if i == 1
            data[str] = tmp
        else
            data[str] = [data[str] tmp]
        end
    end
end

# If no directory called data exists, create one
if ~isdir("./Ensemble18000/data")
    mkdir("./Ensemble18000/data")
end

# Write data to files
for (key,value) in data
    writedlm("./Ensemble18000/data/$key",value)
end

end
