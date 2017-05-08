module PortfolioLoss

	using NumericExtensions, Distributions, NLopt

	export 
		NormalPfModels,
		TPfModels,
		RNormalPfModels,
		RTPfModels,

		condefpro,
		findparatheta,

		findminR,
		findparais,
		findparaisgam,

		claytoncopula,
		conddistgam,

		randomrecovery,

		# function for generating one indicator: I(L>bn) or 
		# corresponding one important sample 
		ordinarysampling,
		ordinarysampling2,
		importantsampling,
		condmc,
		condmcce,

		# function for siumation estimating P(L>bn)
		ordinarysamplingSIMval,
		ordinarysampling2SIMval,
		importantsamplingSIMval, 
		condmcSIMval,
		condmcceSIMval 

	include("normalpfmodels.jl") 
	include("tpfmodels.jl") 
	include("rnormalpfmodels.jl") 
	include("rtpfmodels.jl") 
	include("simtools.jl") 
end