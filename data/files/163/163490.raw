norm_array = zeros(163,163)
for i in 1:163
    for j in i:163
        str = "Cluster/$i"*"_$j"*"/X_norm"
        X_norm = readdlm(str)[1]
        norm_array[i,j] = X_norm
        norm_array[j,i] = X_norm
    end
end
writedlm("norm_array_CAT",norm_array)

