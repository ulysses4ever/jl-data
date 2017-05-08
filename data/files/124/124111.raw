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
export 	VarianceRanking,
		VarianceRankingPatton,
		VarianceRankingBH,
		variance_ranking_dm


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
	bootstrapParam::BootstrapParam
	cutoff::Vector{Float64}
	function VarianceRankingBH(bootstrapParam::BootstrapParam, cutoff::Vector{Float64})
		length(cutoff) != 2 && error("cutoff must be vector of length 2")
		cutoff[1] >= cutoff[2] && error("lower cutoff must be less than upper cutoff")
		new(bootstrapParam, cutoff)
	end
end
VarianceRankingBH(bootstrapParam::BootstrapParam) = VarianceRankingBH(bootstrapParam, [-Inf, Inf])
VarianceRankingBH(numObs::Int) = VarianceRankingBH(BootstrapParam(numObs), [-Inf, Inf])
VarianceRankingBH(numObs::Int, cutoff::Vector{Float64}) = VarianceRankingBH(BootstrapParam(numObs), cutoff)
#Basic methods on above types
Base.string(x::VarianceRankingPatton) = "varianceRankingPatton"
Base.string(x::VarianceRankingBH) = "varianceRankingBowersHeaton"
function Base.show(io::IO, x::VarianceRankingPatton)
	println(io, "Variance ranking method = Patton (2011)")
	println(io, "    Forward weights = " * string(x.forwardWeights))
	println(io, "    Loss function = " * string(x.lossFunction))
end
function Base.show(io::IO, x::VarianceRankingBH)
	println(io, "Variance ranking method = Bowers, Heaton (2013)")
	println(io, "    Bootstrap type = " * string(x.bootstrapParam.bootstrapMethod))
	println(io, "    Cut-off = " * string(x.cutoff))
end
#variance ranking diebold-mariano methods
function variance_ranking_dm{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AbstractVector{T}, varMethod::VarianceRankingPatton ; foreEvalMethod::DMMethod=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	pProxy = variance_ranking_patton_proxy(proxy, varMethod)
	ld = lossdiff(xhat1[1:end-length(varMethod.forwardWeights)], xhat2[1:end-length(varMethod.forwardWeights)], pProxy, varMethod.lossFunction)
	return(dm(ld, foreEvalMethod, confLevel=confLevel))
end
function variance_ranking_dm{T<:Number}(estim::AbstractMatrix{T}, proxy::AbstractVector{T}, varMethod::VarianceRankingPatton ; foreEvalMethod::DMMethod=DMBootstrap(length(proxy)), confLevel::Float64=0.05)
	size(estim, 2) < 2 && error("Not enough input estimators")
	pProxy = variance_ranking_patton_proxy(proxy, varMethod)
	ld = lossdiff(estim[1:end-length(varMethod.forwardWeights), 2:end], estim[1:end-length(varMethod.forwardWeights), 1], pProxy, varMethod.lossFunction)
	return(dm(ld, foreEvalMethod, confLevel=confLevel))
end
variance_ranking_dm{T<:Number}(estim::Vector{Vector{T}}, proxy::AbstractVector{T}, varMethod::VarianceRankingPatton ; foreEvalMethod::DMMethod=DMBootstrap(length(proxy)), confLevel::Float64=0.05) = variance_ranking_dm(colArrToMat(estim), proxy, varMethod, foreEvalMethod=foreEvalMethod, confLevel=confLevel)
function variance_ranking_dm{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AbstractVector{T}, varMethod::VarianceRankingBH ; confLevel::Float64=0.05)
	if !(varMethod.cutoff[1] == -Inf && varMethod.cutoff[2] == Inf) #trim data if required
		proxymed = median(proxy)
		lb = varMethod.cutoff[1] * proxymed
		ub = varMethod.cutoff[2] * proxymed
		inds = [ (lb < proxy[n] < ub) for n = 1:length(proxy) ]
		xhat1 = xhat1[inds]
		xhat2 = xhat2[inds]
		proxy = proxy[inds]
	end
	ldAdj = variance_ranking_BH_series(xhat1, xhat2, proxy)
	update!(varMethod.bootstrapParam, numObsData=length(ldAdj), numObsResample=length(ldAdj), statistic=mean) #These elements of BootstrapParam are fixed
	sVec = dbootstrapstatistic(ldAdj, varMethod.bootstrapParam)
	sort!(sVec)
	(pVal, tailRegion) = pvalue(sVec, 0.0)
	return(pVal, tailRegion)
end
function variance_ranking_dm{T<:Number}(estim::AbstractMatrix{T}, proxy::AbstractVector{T}, varMethod::VarianceRankingBH ; confLevel::Float64=0.05)
	size(estim, 2) < 2 && error("Not enough input estimators")
	pValVec = Array(Float64, size(estim, 2)-1)
	tailRegionVec = Array(Int, size(estim, 2)-1)
	for k = 2:size(estim, 2)
		(pValVec[k-1], tailRegionVec[k-1]) = variance_ranking_dm(estim[:, k], estim[:, 1], proxy, varMethod, confLevel=confLevel)
	end
	ldAdj = Array(Vector{T}, size(estim, 2)-1)
	for k = 2:size(estim, 2)
		ldAdj[k-1] = variance_ranking_BH_series(estim[:, k], estim[:, 1], proxy)
	end
	ldAdjMean = [ mean(ldAdj[k]) for k = 1:length(ldAdj) ]
	return(pValVec, tailRegionVec, ldAdjMean)
end
variance_ranking_dm{T<:Number}(estim::Vector{Vector{T}}, proxy::AbstractVector{T}, varMethod::VarianceRankingBH ; confLevel::Float64=0.05) = variance_ranking_dm(colArrToMat(estim), proxy, varMethod, confLevel=confLevel)
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
#Non-exported function for getting the univariate series used by the BH variance ranking method
function variance_ranking_BH_series{T<:Number}(xhat1::AbstractVector{T}, xhat2::AbstractVector{T}, proxy::AbstractVector{T})
	!(length(xhat1) == length(xhat2) == length(proxy)) && error("length mismatch in inputs")
	mu1 = mean(xhat1)
	mu2 = mean(xhat2)
	mup = mean(proxy)
	return([ (xhat1[n] - proxy[n])^2 - (xhat2[n] - proxy[n])^2 + 2*(xhat1[n] - mu1)*(proxy[n] - mup) - 2*(xhat2[n] - mu2)*(proxy[n] - mup) for n = 1:length(proxy) ])
end











#Function for getting p-values from one-sided or two-sided statistical tests. Input can be eiter sorted vector of iid draws from relevant distribution, or an explicit distribution
function pvalue{T<:Number}(xVec::Vector{T}, xObs::T; twoSided::Bool=true)
	if twoSided
		i = searchsortedlast(xVec, xObs)
		NHalf = 0.5 * length(xVec)
		if i <= NHalf
			tailRegion = 1
			pv = i / NHalf
		else
			tailRegion = -1
			pv = 2 - (i / NHalf)
		end
	else
		tailRegion = 1
		pv = 1 - (searchsortedlast(xVec, xObs) / length(xVec))
	end
	return(pv, tailRegion)
end
function pvalue{T<:Number}(d::Distribution, xObs::T; twoSided::Bool=true)
	if twoSided
		if xObs < mean(d)
			tailRegion = 1
			pv = 2*cdf(d, xObs)
		else
			tailRegion = -1
			pv = 2*cdf(d, -1 * xObs)
		end
	else
		tailRegion = 1
		pv = cdf(d, xObs)
	end
	return(pv, tailRegion)
end

#Non-exported function for converting Vector{Vector} to Matrix
colArrToMat{T<:Number}(x::Vector{Vector{T}}) = [ x[n][m] for m in 1:length(x[1]), n in 1:length(x) ]
colArrToVec{T<:Number}(x::Vector{Vector{T}}, rowNum::Int) = [ x[n][rowNum] for n = 1:length(x) ]





end # module
