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

function runModelForSobolParallel()
	allparams = readdlm("sensitivity/sobol_params_pm50_N100_04_19_2017.txt", ' ', Float64);
	#allparams = SharedArray(Float64, size(allparamslocal))
	#allparams =allparamslocal
	@show size(allparams)
	numSets = size(allparams,1)
	paramsPerThread = numSets/nworkers()
	@sync @parallel for j in collect(1:nworkers())
		f = open(string("sensitivity/tPA_2_AUCForSobolPM50PercentN100_", myid()-1, "_of_",nworkers(), ".txt"), "a+")
		 for k in collect(1:paramsPerThread)
			offset = (myid()-2)*paramsPerThread
			@printf("On set %d of %d on threads %d \n", offset+k, numSets, myid())
			if(offset+k<=numSets)
				currparams = allparams[Int((offset)+k),:]
				AUC =runModelWithParamsReturnAUC(currparams,2)
				#@show AUC
				write(f, string(AUC, "\n"))
			end
		end
		close(f)
	end
end
