include("runModel.jl")

function runModelForSobol()
	allparams = readdlm("sensitivity/paramsplusorminus50percentN500.txt", ' ', Float64);
	@show size(allparams)
	numSets = size(allparams,1)
	f = open("sensitivity/AUCForSobolPM50PercentN500.txt", "a+")
	for j in collect(1:numSets)
		@printf("On set %d of %d\n", j, numSets)
		currparams = allparams[j,:]
		AUC =runModelWithParamsReturnAUC(currparams)
		write(f, string(AUC, "\n"))
	end
	close(f)
end
