# Load relevant packages/scripts:
using Distributions; using StatsBase;

include("diss.jl")
include("GAmod.jl")
include("vowels2.jl")
include("cluster_metrics.jl")

# Dims are duration, F0, F1, F2, F3, F4 (formants measured at midpoint)
dims = Any[[3,4], [2:4], [1:4], [1:5]];
scalings = [1.0];


outfile = open("sim1-bcl.csv","w");
write(outfile,"dims,cats,f,pr,re\n");

for i in dims
    print("dims: ",i,'\n');
    d = length(i)
    for j in scalings
        results = ""
        print("\tscale: ",j,'\n')
        vowels_rand = sample_all(4000,j);
        vowels_scaled = cat(1,zscore(vowels_rand[1:6,:],2),vowels_rand[7,:]);
        vowels_test = sample_all(100,j);
        test_scaled = cat(1,zscore(vowels_test[1:6,:],2),vowels_test[7,:]);
        mix1 = simMix(500,30000,10.,0.5,length(i),10,vowels_scaled,i);
        for m in mix1
            labels = classify(pruneMix(m,0.01),test_scaled,i)
            nCats = length(m.cats[m.phi .> 0.01])
            f,p,r = fscore(test_scaled[7,:],labels)
            results = "$results$d,$nCats,$f,$p,$r\n";
        end
        write(outfile,results);
        gc()
    end
end

close(outfile);


# -------------------------------------
# OME simulations

outfile = open("sim1-ome.csv","w");
write(outfile,"dims,cats,f,pr,re\n");
for i in dims
    print("dims: ",i,'\n');
    d = length(i)
    for j in scalings
        results = ""
        print("\tscale: ",j,'\n')
        vowels_rand = sample_all(4000,j);
        vowels_scaled = cat(1,zscore(vowels_rand[1:6,:],2),vowels_rand[7,:]);
        vowels_test = sample_all(100,j);
        test_scaled = cat(1,zscore(vowels_test[1:6,:],2),vowels_test[7,:]);
        mix1 = simMix(500,30000,length(i),0.005,vowels_scaled,i);
        for m in mix1
            labels = classify(m,test_scaled,i)
            nCats = length(m.cats[m.phi .> 0.01])
            f,p,r = fscore(test_scaled[7,:],labels)
            results = "$results$d,$nCats,$f,$p,$r\n";
           # write(outfile,results)
        end
        #n_comps = catCount(mix1,500);
        #cdev = std(n_comps);
        #mu = mean(n_comps);
        #fm,fl,fu,pm,pl,pu,rm,rl,ru = fmean(mix1,test_scaled,i,7)
        #results = "\"$i\",$j,$mu,$cdev,$fm,$fl,$fu,$pm,$pl,$pu,$rm,$rl,$ru\n";
        write(outfile,results);
        gc()
    end
end

close(outfile);


# -------------------------------------



function covMean(models,d)
    meanCov = zeros(d,d);
    for model in models
        meanCov += smean(model.sigma);
    end
    meanCov /= length(models)
    return meanCov
end


dims = Any[[3,4], [2:4], [1:4], [1:5]];
scalings = [1.0];

outfile = open("/home/chirp/Dropbox/Dissertation/simulations/sim1-bcl-vars.csv","w");
#write(outfile,"dims,cats,f,pr,re\n");

for i in dims
    print("dims: ",i,'\n');
    d = length(i)
    for j in scalings
        results = ""
        print("\tscale: ",j,'\n')
        vowels_rand = sample_all(4000,j);
        vowels_scaled = cat(1,zscore(vowels_rand[1:6,:],2),vowels_rand[7,:]);
        vowels_test = sample_all(100,j);
        test_scaled = cat(1,zscore(vowels_test[1:6,:],2),vowels_test[7,:]);
        mix1 = simMix(500,30000,10.,0.5,length(i),10,vowels_scaled,i);
        vars = diag(round(covMean(mix1,length(i)),2))
        write(outfile,string(vars));
        write(outfile,'\n')
        gc()
    end
end

close(outfile);




# # sample data for plotting:
# vowels_rand = sample_all(4000,1);
# vowels_scaled = cat(1,zscore(vowels_rand[1:6,:],2),vowels_rand[7,:]);
# 
# writedlm("training.csv",vowels_scaled',',')
# 
# mix11 = simMix(50,30000,10.,0.5,2,10,vowels_scaled,[3,4]);
# for mix in mix11
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# # will need to alter index probably:
# sample11 = sample(pruneMix(mix11[6],0.01),5000)
# writedlm("bcl2d.csv",sample11',',')
# #++++++++++++++++
# mix21 = simMix(50,30000,10.,0.5,3,10,vowels_scaled,[2,3,4]);
# for mix in mix21
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# # will need to alter index probably:
# sample21 = sample(pruneMix(mix21[3],0.01),5000)
# writedlm("bcl3d.csv",sample21',',')
# #++++++++++++++++
# mix31 = simMix(50,30000,10.,0.5,4,10,vowels_scaled,[1,2,3,4]);
# for mix in mix31
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# # will need to alter index probably:
# sample31 = sample(pruneMix(mix31[6],0.01),5000)
# writedlm("bcl4d.csv",sample31',',')
# #++++++++++++++++
# mix41 = simMix(50,30000,10.,0.5,5,10,vowels_scaled,[1,2,3,4,5]);
# for mix in mix41
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# 
# # will need to alter index probably:
# sample41 = sample(pruneMix(mix41[4],0.01),5000)
# writedlm("bcl5d.csv",sample41',',')
# #++++++++++++++++
# #++++++++++++++++
# 
# mix12 = simMix(50,30000,2,0.005,vowels_scaled,[3,4]);
# for mix in mix12
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# # will need to alter index probably:
# sample12 = sample(mix12[2],5000)
# writedlm("OME2d.csv",sample12',',')
# #++++++++++++++++
# mix22 = simMix(50,30000,3,0.005,vowels_scaled,[2,3,4]);
# for mix in mix22
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# # will need to alter index probably:
# sample22 = sample(mix22[3],5000)
# writedlm("OME3d.csv",sample22',',')
# #++++++++++++++++
# mix32 = simMix(50,30000,4,0.005,vowels_scaled,[1,2,3,4]);
# for mix in mix32
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# # will need to alter index probably:
# sample32 = sample(mix32[3],5000)
# writedlm("OME4d.csv",sample32',',')

# mix42 = simMix(50,30000,5,0.005,vowels_scaled,[1,2,3,4,5]);
# for mix in mix42
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# # will need to alter index probably:
# sample42 = sample(mix42[2],5000)
# writedlm("OME5d.csv",sample42',',')