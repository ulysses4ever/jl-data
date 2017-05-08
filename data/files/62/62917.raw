# Load relevant packages/scripts:
using Distributions; using StatsBase;

include("/home/chirp/Dropbox/Dissertation/diss.jl")
include("/home/chirp/Documents/dissertation/GAmod.jl")
include("/home/chirp/Documents/dissertation/vowels2.jl")
include("/home/chirp/Documents/dissertation/cluster_metrics.jl")



# Generating Data:
fiveVowel_input = sample_5(6500,1.0);
spMean = cat(1,mean(fiveVowel_input,2)[1:4],0);
spSD = cat(1,std(fiveVowel_input,2)[1:4],[1]);
fiveVowel_scaled = cat(1,zscore(fiveVowel_input[1:4,:],2),fiveVowel_input[5,:]);

# Save training data
writedlm("fiveVowel.csv",fiveVowel_scaled',',');

spanish_test = sample_5(100,1.0);
spanish_test_scaled = cat(1,zscore(spanish_test[1:4,:],2),spanish_test[5,:]);

vowels_test = sample_all(100,1.0)[[1:4,7],:];
test_scaled = (vowels_test .- repmat(spMean',size(vowels_test,2))') ./ repmat(spSD',size(vowels_test,2))'

vowels_rand = sample_all(4000,1.0)[[1:4,7],:];
vowels_scaled = (vowels_rand .- repmat(spMean',size(vowels_rand,2))') ./ repmat(spSD',size(vowels_rand,2))'

# Fit initial model
N = 500;
alpha = 5.
mixBCL = simMix(N,30000,alpha,0.5,4,10,fiveVowel_scaled,1:4);
#mixBCL2 = simMix(N,30000,alpha,0.5,4,10,5,vowels_scaled,1:4);

outfile = open("sim3-bcl.csv","w");
write(outfile,"data,exposure,cats,f,pr,re\n");
# Test on Five Vowel Data:
testDat = "five vowel"
exposure = "none"
results = ""
for m in mixBCL
    labels = classify(m,spanish_test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(spanish_test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

# Test on English Data:
testDat = "english"
exposure = "none"
results = ""
for m in mixBCL
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);



# mixBCL = simMix(N,30000,alpha,0.5,4,10,fiveVowel_scaled,1:4);
for mix in mixBCL
   print(length(mix.cats[mix.phi .> 0.01]),' ')
end
sample5 = sample(pruneMix(mixBCL[3],0.01),1000)
writedlm("bcl5.csv",sample5',',')


mix500 = simMix(deepcopy(mixBCL),N,500,alpha,0.5,4,10,vowels_scaled,1:4);
# for mix in mix500
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample500 = sample(pruneMix(mix500[94],0.01),1000)
# writedlm("bcl500.csv",sample500',',')


mix1000 = simMix(deepcopy(mixBCL),N,1000,alpha,0.5,4,10,vowels_scaled,1:4);
# for mix in mix1000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample1000 = sample(pruneMix(mix1000[80],0.01),1000)
# writedlm("bcl1000.csv",sample1000',',')


mix2500 = simMix(deepcopy(mixBCL),N,2500,alpha,0.5,4,10,vowels_scaled,1:4);
# for mix in mix2500
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample2500 = sample(pruneMix(mix2500[95],0.01),1000)
# writedlm("bcl2500.csv",sample2500',',')


mix5000 = simMix(deepcopy(mixBCL),N,5000,alpha,0.5,4,10,vowels_scaled,1:4);
# for mix in mix5000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample5000 = sample(pruneMix(mix5000[94],0.01),1000)
# writedlm("bcl5000.csv",sample5000',',')


mix10000 = simMix(deepcopy(mixBCL),N,10000,alpha,0.5,4,10,vowels_scaled,1:4);
# for mix in mix10000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample10000 = sample(pruneMix(mix10000[27],0.01),1000)
# writedlm("bcl10000.csv",sample10000',',')



testDat = "english"
exposure = "500"
results = ""
for m in mix500
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "1000"
results = ""
for m in mix1000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "2500"
results = ""
for m in mix2500
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "5000"
results = ""
for m in mix5000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "10000"
results = ""
for m in mix10000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);
close(outfile);






# OME
mixOME = simMix(N,30000,4,0.005,fiveVowel_scaled,1:4);





outfile = open("sim3-ome.csv","w");
write(outfile,"data,exposure,cats,f,pr,re\n");
# Test on Spanish Data:
testDat = "spanish"
exposure = "none"
results = ""
for m in mixOME
    labels = classify(m,spanish_test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(spanish_test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

# Test on English Data:
testDat = "english"
exposure = "none"
results = ""
for m in mixOME
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);


# Re-train


# for mix in mixOME
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample5 = sample(mixOME[1],1000)
# writedlm("OME5.csv",sample5',',')

mix500 = simMix(deepcopy(mixOME),N,500,4,0.005,vowels_scaled,1:4);

# for mix in mix500
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample500 = sample(mix500[4],1000)
# writedlm("OME500.csv",sample500',',')

mix1000 = simMix(deepcopy(mixOME),N,1000,4,0.005,vowels_scaled,1:4);
# for mix in mix1000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample1000 = sample(mix1000[9],1000)
# writedlm("OME1000.csv",sample1000',',')

mix2500 = simMix(deepcopy(mixOME),N,2500,4,0.005,vowels_scaled,1:4);
# for mix in mix2500
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample2500 = sample(mix2500[10],1000)
# writedlm("OME2500.csv",sample2500',',')

mix5000 = simMix(deepcopy(mixOME),N,5000,4,0.005,vowels_scaled,1:4);
# for mix in mix5000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample5000 = sample(mix5000[11],1000)
# writedlm("OME5000.csv",sample5000',',')

mix10000 = simMix(deepcopy(mixOME),N,10000,4,0.005,vowels_scaled,1:4);
# for mix in mix10000
#    print(length(mix.cats[mix.phi .> 0.01]),' ')
# end
# sample10000 = sample(mix10000[14],1000)
# writedlm("OME10000.csv",sample10000',',')



testDat = "english"
exposure = "500"
results = ""
for m in mix500
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "1000"
results = ""
for m in mix1000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "2500"
results = ""
for m in mix2500
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "5000"
results = ""
for m in mix5000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);

testDat = "english"
exposure = "10000"
results = ""
for m in mix10000
    labels = classify(m,test_scaled,1:4)
    nCats = length(m.cats[m.phi .> 0.01])
    f,p,r = fscore(test_scaled[5,:],labels)
    results = "$results$testDat,$exposure,$nCats,$f,$p,$r\n";
end
write(outfile,results);
close(outfile);
