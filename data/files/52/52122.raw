module SimMixedModels

	using DataFrames, Distributions, RDatasets  

	export 
	  MixedData,
	  CrossedData,
	  NestedData,
	  CrossedDataBAL,
	  NestedDataBAL,
	  ReplinearOnegroup, 
	  makedata2waylinear,
	  newdata2waylinear

	abstract MixedData

	abstract CrossedData <: MixedData
	abstract NestedData  <: MixedData

	include("cross.jl");
	include("nested.jl");
	include("twowaylinear.jl");
end 
