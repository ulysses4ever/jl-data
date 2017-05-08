
Yield = zeros(100,1)
for i in 1:100
    yield = readdlm("KO_all/$i/yield")[1]
    Yield[i] = yield
end

println(mean(Yield)," +/- ",std(Yield))

#writedlm("Yield_KO_nuo",Yield)

#Mean = zeros(815,1)
#Std = zeros(815,1)
#Max = zeros(815,1)
#Min = zeros(815,1)
#for i in 1:815
#    Mean[i] = mean(Params[i,:])
#    Std[i] = std(Params[i,:])
#    Max[i] = maximum(Params[i,:])
#    Min[i] = minimum(Params[i,:])
#end

#Ox Phos present: yield = 0.0859 +/- 0.0040
#KO_all: yield = 0.0269 +/- 0.0034
#KO_cyd: yield = 0.0277 +/- 0.0024
#KO_app: yield = 0.0881 +/- 0.0035
#KO_nuo: yield = 0.0683 +/- 0.0071

