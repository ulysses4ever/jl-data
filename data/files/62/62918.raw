#vowels = sample_all(2000,1); vowels = cat(1,zscore(vowels[1:6,:],2),vowels[7,:]);

sInit = Sigma(2,eye(2)*0.1,5);
mix1 = [Mix(2,10,1,[20],[],[],sInit) for i=1:10000];


for i=1:10000
    vowels = sample_all(1000,1); vowels = cat(1,zscore(vowels[1:6,:],2),vowels[7,:]);
    for j=1:10000
        update(mix1[i],vowels[3:4,j],0.1);
    end
    if i%100==0
        print(i,", ")
    end
end

n_comps = zeros(10000);

for j=1:length(mix1)
    n = 0
    for i=1:length(mix1[j].cats)
        if mix1[j].phi[i] > 0.05
            n += 1
        end
    end
    n_comps[j] += n
end


print(minimum(n_comps),'\n')
print(maximum(n_comps),'\n')
#print(mean(n_comps),'\n')
range_vals = maximum(n_comps) - minimum(n_comps);
plt.hist(n_comps,range_vals);


include("cluster_metrics.jl");

vowels_test = sample_all(91,1); vowels_test = cat(1,zscore(vowels_test[1:6,:],2),vowels_test[7,:]);

fscores = Array(Float64,1000,1)

for i=1:length(fscores)
    testlabs = categorize(mixtures_1a[i],vowels_test[3:4,:])
    fscores[i] = fscore(testlabs',vowels_test[7,:])
end

print(mean(fscores))

plt.hist(fscores)


#-----------------------------------------------------------------------------------------

sInit = Sigma(2,eye(2)*0.05,5);
mix2 = [Mix(2,10,1,[20],[],[],sInit) for i=1:10000];


for i=1:10000
    vowels = sample_all(1000,1); vowels = cat(1,zscore(vowels[1:6,:],2),vowels[7,:]);
    for j=1:10000
        update(mix2[i],vowels[3:4,j],0.1);
    end
    if i%100==0
        print(i,", ")
    end
end

n_comps = zeros(10000);

for j=1:length(mix1)
    n = 0
    for i=1:length(mix2[j].cats)
        if mix2[j].phi[i] > 0.05
            n += 1
        end
    end
    n_comps[j] += n
end


print(minimum(n_comps),'\n')
print(maximum(n_comps),'\n')
#print(mean(n_comps),'\n')
range_vals = maximum(n_comps) - minimum(n_comps);
plt.hist(n_comps,range_vals);