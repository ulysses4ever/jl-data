using DataFrames

include("sphere.jl")

function find_nugget_features(W::DataFrame, features::Array)
	amountOfDim=rand(nuggetDimensions)
	res=nothing
	nonNuggets=0
	while (nonNuggets == 0)
		res=convert(Array{ASCIIString},sort(find_rand_unique(features, amountOfDim)))
		nonNuggets=size(W[getAndQuery(res),["t_D"]], 1)
	end
	res
end

function find_nugget_diagnose(W::DataFrame, nuggetFeatures::Array)
	typesRepresentedInDims=matrix(DataFrame(unique(W[getAndQuery(nuggetFeatures), ["t_D"]])))
	typesInSystem=matrix(DataFrame(unique(W["t_D"])))
	unusedTypesInDims = setdiff(typesInSystem, typesRepresentedInDims)
	find_rand_unique(unusedTypesInDims, 1)
end

function reduceNonNuggetsByDim!(W::DataFrame, features)

	max_range_of_non_nuggets = (1-nugget_dist-(2*nugget_radius))

	for f in features
		if maximum(removeNA(W[f])) > max_range_of_non_nuggets
			W[f] = W[f].*max_range_of_non_nuggets
		end
	end
end

function injectNugget!(W::DataFrame, IDs::Array, nuggetFeatures::Array)
	fmax = [ maximum(removeNA(W[f])) for f in nuggetFeatures ]
	centroid=createCentroid(fmax, (nugget_dist+nugget_radius))

	df=DataFrame()

	for i=1:length(nuggetFeatures)
		df[nuggetFeatures[i]]=[centroid[i]]
	end

	nugget=createDots(df, min_nugget_size-1; max_r=nugget_radius)

	for i=1:minimum([length(IDs), size(nugget,1)])
		for f in nuggetFeatures
			W[IDs[i], f] = nugget[i, f]
		end
	end
end

function createNugget(W::DataFrame, features::Array)
	
	nuggetFeatures=nothing
	nuggetDiagnose=nothing

	nuggetFeatures=find_nugget_features(W, features)

	nuggetDiagnose=find_nugget_diagnose(W, nuggetFeatures)[1]

	
	reduceNonNuggetsByDim!(W, nuggetFeatures)	

	queryNugget =:( (t_D .== $(nuggetDiagnose)) & $(getAndEmptyFields(nuggetFeatures)) )

	nuggetSamplesIDs=matrix(W[queryNugget, ["id"]])

	nuggetSamplesIDs = reshape(nuggetSamplesIDs,(size(nuggetSamplesIDs,1),))

	injectNugget!(W, nuggetSamplesIDs, nuggetFeatures)
	
	(nuggetDiagnose, nuggetFeatures)
end

function createNuggets(W::DataFrame, features::Array, Amount::Int64)
	usedDims=Any[]
	for i=1:Amount
		push!(usedDims,createNugget(W, features))
		println(i)
	end
	usedDims
end
