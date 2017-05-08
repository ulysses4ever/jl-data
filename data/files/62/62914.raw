# Load relevant packages/scripts:
using Distributions; using StatsBase;

include("/home/chirp/Dropbox/Dissertation/diss.jl")
include("/home/chirp/Documents/dissertation/GAmod.jl")
include("/home/chirp/Documents/dissertation/vowels2.jl")
include("/home/chirp/Documents/dissertation/cluster_metrics.jl")

function covMean(models)
    meanCov = zeros(4,4);
    for model in models
        meanCov += smean(model.sigma);
    end
    meanCov /= length(models)
    return meanCov
end


# Generate data:

vowels_rand = sample_all(4000,1.0);
vowelMean = cat(1,mean(vowels_rand,2)[1:4],[0]);
vowelSD = cat(1,std(vowels_rand,2)[1:4],[1]);
vowels_scaled = cat(1,zscore(vowels_rand[1:6,:],2),vowels_rand[7,:]);

# stimuli
stims_bal = readdlm("/home/chirp/Dropbox/Dissertation/bal_stims.csv",',')';
stims_f2 = readdlm("/home/chirp/Dropbox/Dissertation/f2_stims.csv",',')';
stims_f0 = readdlm("/home/chirp/Dropbox/Dissertation/f0_stims.csv",',')';
test_bal = readdlm("/home/chirp/Dropbox/Dissertation/bal_test.csv",',')'[:,randperm(600)];
test_f2 = readdlm("/home/chirp/Dropbox/Dissertation/f2_test.csv",',')'[:,randperm(600)];
test_f0 = readdlm("/home/chirp/Dropbox/Dissertation/f0_test.csv",',')'[:,randperm(600)];


# normalizing with the same parameters as vowels:
stims_bal = (stims_bal .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'
test_bal = (test_bal .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'
stims_f2 = (stims_f2 .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'
test_f2 = (test_f2 .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'
stims_f0 = (stims_f0 .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'
test_f0 = (test_f0 .- repmat(vowelMean',600)') ./ repmat(vowelSD',600)'


stims_bal = cat(2,stims_bal[:,randperm(600)],stims_bal[:,randperm(600)],stims_bal[:,randperm(600)]);
stims_f2 = cat(2,stims_f2[:,randperm(600)],stims_f2[:,randperm(600)],stims_f2[:,randperm(600)]);
stims_f0 = cat(2,stims_f0[:,randperm(600)],stims_f0[:,randperm(600)],stims_f0[:,randperm(600)]);


stims = Any[stims_bal,stims_f2,stims_f0];
test_stims = Any[test_bal,test_f2,test_f0];
group = Any["bal","f2","f0"];

# actual simulations:


mix1 = simMix(1000,30000,10.,0.5,4,10,vowels_scaled,1:4);
for model in mix1
    resetMix(model,0.75,2,true,2);
end

outfile = open("sim2-bcl.csv","w");
write(outfile,"group,cats,f,pr,re\n");
for i=1:3
    mixExp = simMix(deepcopy(mix1),1000,1800,10.,0.5,4,6,stims[i],1:4)
    results = ""
    g = group[i]
    for m in mixExp
        labels = classify(pruneMix(m,0.01),test_stims[i],1:4)
        nCats = length(m.cats[m.phi .> 0.01])
        f,p,r = fscore(test_stims[i][5,:],labels)
        results = "$results$g,$nCats,$f,$p,$r\n";
    end
    write(outfile,results);
end
close(outfile);

# # Using these to get examples of learned category systems
# # Will probably have to change the sampled model depending on results
# mix1 = simMix(100,30000,10.,0.5,4,10,5,vowels_scaled,1:4);
# for model in mix1
#     resetMix(model,0.75,2,true,2);
# end
# 
# bclBal = simMix(deepcopy(mix1),100,1800,10.,0.5,4,6,stims_bal,1:4);
# for mix in bclBal
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleBal = sample(pruneMix(bclBal[1],0.01),1000)
# writedlm("bclBal.csv",sampleBal',',')
# 
# 
# bclF2 = simMix(deepcopy(mix1),100,1800,10.,0.5,4,6,stims_f2,1:4);
# for mix in bclF2
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleF2 = sample(pruneMix(bclF2[3],0.01),1000)
# writedlm("bclF2.csv",sampleF2',',')
# 
# 
# bclF0 = simMix(deepcopy(mix1),100,1800,10.,0.5,4,6,stims_f0,1:4);
# for mix in bclF0
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleF0 = sample(pruneMix(bclF0[3],0.01),1000)
# writedlm("bclF0.csv",sampleF0',',')


# OME

mix1 = simMix(1000,30000,4,0.005,vowels_scaled,1:4);
outfile = open("sim2-ome.csv","w");
write(outfile,"group,cats,f,pr,re\n");
for i=1:3
    mixExp = simMix(deepcopy(mix1),1000,1800,4,0.005,stims[i],1:4);
    results = ""
    g = group[i]
    for m in mixExp
        labels = classify(m,test_stims[i],1:4)
        nCats = length(m.cats[m.phi .> 0.01])
        f,p,r = fscore(test_stims[i][5,:],labels)
        results = "$results$g,$nCats,$f,$p,$r\n";
    end
    write(outfile,results);
end
close(outfile);

# Not run, given that all simulations ended up 1 category
# omeBal = simMix(deepcopy(mix1),1000,1800,4,0.005,stims_bal,1:4);
# for mix in omeBal
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end

# omeF2 = simMix(deepcopy(mix1),1000,1800,4,0.005,stims_f2,1:4);
# for mix in omeF2
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end

# omeF0 = simMix(deepcopy(mix1),1000,1800,4,0.005,stims_f0,1:4);
# for mix in omeF0
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end


