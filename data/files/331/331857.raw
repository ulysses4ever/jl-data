module PowerLaw

using Distributions
using Compat
using Optim
import Base: scale, rand, minimum, maximum
import Base: mean, median, quantile, var
import StatsBase: kurtosis, skewness, entropy, mode, fit

export
	# distribution types
	DiscretePowerLaw,
	ContinuousPowerLaw,

	# methods
	shape,
	scale,
	params,
	mean,
	median,
	mode,
	var,
	skewness,
	kurtosis,
	entropy,
	pdf,
	logpdf,
	ccdf,
	logccdf,
	cdf,
	logcdf,
	cquantitle,
	quantitle,
	rand,
	fit_mle,
	lrt,
	eccdf,
	ks,
	findxmin,
	pvalue

include("univariates.jl")
include("utilities.jl")


end # module
