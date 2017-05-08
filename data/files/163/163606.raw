num_sampling_from = 18000
num_samples = 180

list = rand(1:18000,180)

if ~isdir("Rand180")
    mkdir("Rand180")
end

for (i,j) in enumerate(list)
    cp("Ensemble18000/$j","Rand180/$i")
end
