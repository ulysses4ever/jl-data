using FinancialEconometricsTests, LossFunctions, DependentBootstrap




numObs = 1000
numEst = 5
function testvarranking(numObs::Int, numEst::Int)
	depFac = 0.5
	vTrue = 1 + cumsum(0.02 * randn(numObs))
	while any(vTrue .<= 0)
		vTrue = 1 + cumsum(0.01 * randn(numObs))
	end
	eCommon = randn(numObs)
	vProxy = Float64[ vTrue[n] + 0.1*vTrue[n]*(depFac*eCommon[n] + (1-depFac)*randn()) for n = 1:numObs ]
	vEst = Array(Float64, numObs, numEst)
	for k = 1:numEst
		vEst[:, k] = Float64[ vTrue[n] + k*0.01*vTrue[n]*(depFac*eCommon[n] + (1-depFac)*randn()) for n = 1:numObs ]
	end
	ldTrueQLIKE = lossdiff(vEst[:, 2:end], vec(vEst[:, 1]), vTrue, QLIKE())
	ldTrueMSE = lossdiff(vEst[:, 2:end], vec(vEst[:, 1]), vTrue, SquaredLoss())
	mean_ldTrueQLIKE = mean(ldTrueQLIKE, 1)
	mean_ldTrueMSE = mean(ldTrueMSE, 1)
	methodVec = [VarianceRankingPatton(), VarianceRankingPatton(SquaredLoss()), VarianceRankingBH(numObs), VarianceRankingBH(numObs, [0.5, 1.5])]
	pValAll = Array(Any, length(methodVec))
	tailRegionAll = Array(Any, length(methodVec))
	testStatAll = Array(Any, length(methodVec))
	for m = 1:length(methodVec)
		(pValAll[m], tailRegionAll[m], testStatAll[m]) = variance_ranking_dm(vEst, vProxy, methodVec[m])
	end
	for m = 1:length(methodVec)
		show(methodVec[m])
		println("p-value vec = " * string(pValAll[m]))
		println("tail region vec = " * string(tailRegionAll[m]))
		println("test stat vec = " * string(testStatAll[m]))
		if typeof(methodVec[m]) == VarianceRankingPatton
			if typeof(methodVec[m].lossFunction) == QLIKE
				println("true stat vec = " * string(mean_ldTrueQLIKE))
			elseif typeof(methodVec[m].lossFunction) == SquaredLoss
				println("true stat vec = " * string(mean_ldTrueMSE))
			else
				error("Comparison not enabled for this loss function")
			end
		else
			println("true stat vec = " * string(mean_ldTrueMSE))
		end
		println("")
	end
end

testvarranking(1000, 5)

