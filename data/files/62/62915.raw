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

# stimuli
stims_bal = readdlm("/home/chirp/Dropbox/Dissertation/bal_stims.csv",',')';
stims_f2 = readdlm("/home/chirp/Dropbox/Dissertation/f2_stims.csv",',')';
stims_f0 = readdlm("/home/chirp/Dropbox/Dissertation/f0_stims.csv",',')';
test_bal = readdlm("/home/chirp/Dropbox/Dissertation/bal_test.csv",',')'[:,randperm(600)];
test_f2 = readdlm("/home/chirp/Dropbox/Dissertation/f2_test.csv",',')'[:,randperm(600)];
test_f0 = readdlm("/home/chirp/Dropbox/Dissertation/f0_test.csv",',')'[:,randperm(600)];

stims_combined = cat(2,stims_bal,stims_f2,stims_f0);
vowelMean = cat(1,mean(stims_combined,2)[1:4],[0]);
vowelSD = cat(1,std(stims_combined,2)[1:4],[1]);

# # normalizing with the same parameters for all three groups:
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



outfile = open("sim2b-bcl.csv","w");
write(outfile,"group,cats,f,pr,re\n");
for i=1:3
    mixExp = simMix(1000,1800,2.,0.5,4,6,stims[i],1:4)
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

# # Sampling. Will need to adjust depending on outcomes:
# bclBal = simMix(100,1800,2.,0.5,4,6,5,stims_bal,1:4);
# for mix in bclBal
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleBal = sample(pruneMix(bclBal[1],0.01),1000)
# writedlm("bclBal2a.csv",sampleBal',',')
# 
# 
# bclF2 = simMix(100,1800,2.,0.5,4,6,5,stims_f2,1:4);
# for mix in bclF2
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleF2 = sample(pruneMix(bclF2[12],0.01),1000)
# writedlm("bclF22a.csv",sampleF2',',')
# 
# 
# bclF0 = simMix(100,1800,2.,0.5,4,6,5,stims_f0,1:4);
# for mix in bclF0
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleF0 = sample(pruneMix(bclF0[12],0.01),1000)
# writedlm("bclF02a.csv",sampleF0',',')





# OME
outfile = open("sim2b-ome.csv","w");
write(outfile,"group,cats,f,pr,re\n");
for i=1:3
    mixExp = simMix(1000,1800,4,0.01,stims[i],1:4); # note changed learning rate here
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




outfile = open("sim2b-bcl-var.txt","w");
balmix = simMix(1000,1800,5.,0.5,4,10,5,stims_bal,1:4);
dur,f0,f1,f2 = diag(round(covMean(balmix),4));
results = "bal,$dur,$f0,$f1,$f2\n";
write(outfile,results);
f2mix = simMix(1000,1800,5.,0.5,4,10,5,stims_f2,1:4);
dur,f0,f1,f2 = diag(round(covMean(f2mix),4));
results = "f2,$dur,$f0,$f1,$f2\n";
write(outfile,results);
f0mix = simMix(1000,1800,5.,0.5,4,10,5,stims_f0,1:4);
dur,f0,f1,f2 = diag(round(covMean(f0mix),4));
results = "f0,$dur,$f0,$f1,$f2\n";
write(outfile,results);
close(outfile);



# # Sampling. Will need to adjust depending on outcomes:
# omeBal = simMix(100,1800,4,0.01,stims_bal,1:4);
# for mix in omeBal
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# sampleBal = sample(omeBal[7],1000)
# writedlm("omeBal.csv",sampleBal',',')
# 
# 
# omeF2 = simMix(100,1800,4,0.01,stims_f2,1:4);
# for mix in omeF2
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sampleF2 = sample(omeF2[3],1000)
# writedlm("omeF2.csv",sampleF2',',')
# 
# omeF0 = simMix(100,1800,4,0.01,stims_f0,1:4);
# for mix in omeF0
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sampleF0 = sample(omeF0[1],1000)
# writedlm("omeF0.csv",sampleF0',',')
