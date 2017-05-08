module FinancialEconometricsTests
#-----------------------------------------------------------
#PURPOSE
#	Colin T. Bowers module for conducting specific statistical tests from the field of financial econometrics
#NOTES
#LICENSE
#	MIT License (see github repository for more detail: https://github.com/colintbowers/FinancialEconometricsTests.jl.git)
#-----------------------------------------------------------

#Load any entire modules that are needed (use import ModuleName1, ModuleName2, etc)
using 	StatsBase,
		Distributions,
		ForecastEval,
		LossFunctions,
		KernelStat,
		DependentBootstrap

#Load any specific variables/functions that are needed (use import ModuleName1.FunctionName1, ModuleName2.FunctionName2, etc)
import 	Base.string,
		Base.show

#Specify the variables/functions to export (use export FunctionName1, FunctionName2, etc)



#******************************************************************************

#----------------------------------------------------------
#SET CONSTANTS FOR MODULE
#----------------------------------------------------------
#Currently none





#----------------------------------------------------------
#ROUTINE
#	variance_ranking
#REFERENCES
#	Patton (2011) "Data-based Ranking of Realized Volatility Estimators"
#	Bowers, Heaton (2013) "Ranking Variance Estimators Using Empirical Criteria"
#NOTES
#----------------------------------------------------------
#-------- METHOD TYPES ---------
abstract VarianceRanking #Abstract type for method types for evaluating variance estimators
#Patton (2011)
type VarianceRankingPatton <: VarianceRanking
	forwardWeights::Vector{Float64}
	lossFunction::LossFunction
	function VarianceRankingPatton(forwardWeights::Vector{Float64}, lossFunction::LossFunction)
		!(1.0 - 5*eps() <= sum(forwardWeights) <= 1.0 + 5*eps()) && error("forwardWeights must sum to unity")
		new(forwardWeights, lossFunction)
	end
end
VarianceRankingPatton(lossFunc::LossFunction) = VarianceRankingPatton([1.0], lossFunc)
VarianceRankingPatton() = VarianceRankingPatton([1.0], QLIKE())
#Bowers, Heaton (2013)
type VarianceRankingBH <: VarianceRanking
end
#variance ranking diebold-mariano methods
function variance_ranking_dm{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AstractVector{T}, varMethod::VarianceRankingPatton ; foreEvalMethod::DMMethod=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	pProxy = variance_ranking_patton_proxy(proxy, varMethod)
	ld = lossdiff(xhat1[1:end-length(varMethod.forwardWeights)], xhat2[1:end-length(varMethod.forwardWeights)], pProxy, varMethod.lossFunction)
	return(dm(ld, foreEvalMethod, confLevel=confLevel))
end
function variance_ranking_dm{T<:Number}(estim::AbstractMatrix{T}, proxy::AstractVector{T}, varMethod::VarianceRankingPatton ; foreEvalMethod::DMMethod=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	size(estim, 2) < 2 && error("Not enough input estimators")
	pProxy = variance_ranking_patton_proxy(proxy, varMethod)
	ld = lossdiff(estim[1:end-length(varMethod.forwardWeights), 2:end], estim[1:end-length(varMethod.forwardWeights), 1], pProxy, varMethod.lossFunction)
	return(dm(ld, foreEvalMethod, confLevel=confLevel))
end
function variance_ranking_dm{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AstractVector{T}, varMethod::VarianceRankingBH ; foreEvalMethod::DMBootstrap=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	#NOTE, YOU NEED TO FIX BRM ESTIMATOR SO THAT IT DOESN'T THROW AN ERROR WHEN LESS THAN 3 OBS ARE INPUT. COME UP WITH A DEFAULT
	#UP TO HERE. SAME OUTPUT AND STRUCTURE AS ABOVE TWO PATTON METHODS, BUT USE variance_ranking_BH_ELD

end
function variance_ranking_dm{T<:Number}(estim::AbstractMatrix{T}, proxy::AstractVector{T}, varMethod::VarianceRankingBH ; foreEvalMethod::DMBootstrap=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	#UP TO HERE. SAME OUTPUT AND STRUCTURE AS ABOVE TWO PATTON METHODS, BUT USE variance_ranking_BH_ELD

end


#Non-exported function for calculating proxy from Patton (2011) "Data-based Ranking of Realized Volatility Estimators"
function variance_ranking_patton_proxy{T<:Number}(proxy::AbstractVector{T}, varMethod::VarianceRankingPatton)
	wL = length(varMethod.forwardWeights)
	if wL == 1
		newProxy = proxy[2:end]
	else
		newProxy = [ dot(varMethod.forwardWeights, proxy[n:n+wL-1]) for n = 2:length(proxy)-wL+1 ]
	end
	return(newProxy)
end
#Non-exported function for calculating the estimate of the expected loss differential in Bowers, Heaton (2013) "Ranking Variance Estimators Using Empirical Criteria"
function variance_ranking_BH_ELD{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AstractVector{T})
	#UP TO HERE. NEED TO IMPLEMENT BH ESTIMATE OF ELD (WITH COVARIANCES)
end


end # module
