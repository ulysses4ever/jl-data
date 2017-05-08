Params = zeros(815,12437)
for i in 1:12437
    params = readdlm("Ensemble12437/$i/params")
    Params[:,i] = params
end
writedlm("Ensemble12437/Params",Params)


Cor = eye(12437) # Diagonal elements should be 1
for i in 1:12437
    println(i)
    for j in i+1:12437
        Cor[i,j] = cor(Params[:,i],Params[:,j])
        Cor[j,i] = Cor[i,j]
    end
end

writedlm("Ensemble12437/Cor",Cor)


Cor = readdlm("Ensemble12437/Cor")
sub_ensemble_size = 100

Index = 12431 # Best-fit set
cor_array = Cor[:,Index]
index = find(cor_array.==minimum(cor_array))
Index = [Index index]

for j in 3:sub_ensemble_size
    cor_array = Cor[:,vec(Index)]
    cor_max_array = zeros(size(cor_array,1))
    for i in 1:length(cor_max_array)
        cor_max_array[i] = maximum(cor_array[i,:])
    end
    index = find(cor_max_array.==minimum(cor_max_array))
    Index = [Index index]
end

sub_ensemble_cor = Cor[vec(Index),vec(Index)]

writedlm("Ensemble12437/Index",Index)
writedlm("Ensemble12437/sub_ensemble_cor",sub_ensemble_cor)


j = 1
for i in Index
    cp("Ensemble12437/$i","Ensemble100/$j")
    j += 1
end



