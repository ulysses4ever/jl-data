data_indices = [54;92;60;61;62;69;70;71;63;64;65;66;67;68;58;57;
56;72;59;73;74;75;76;77;78;79;80;91;81;82;83;84;85;86;87;88;89]

X_best = readdlm("Cluster/Best/X")
X_best = X_best[:,data_indices]

mkdir("ClusterDataOnly")
for i in 1:163
    for j in i:163
        str = "Cluster/$i"*"_$j/X"
        X = readdlm(str)
        X = X[:,data_indices]
        X_norm = norm(X-X_best)
        str2 = "ClusterDataOnly/$i"*"_$j"
        mkdir(str2)
        writedlm(str2*"/X",X_norm)
    end
end

