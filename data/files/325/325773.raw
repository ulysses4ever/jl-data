using DataFrames

function getAndQuery(ItemSet::Array{Symbol})
	q = :(!isna($(ItemSet[1])))

	for i=2:length(ItemSet)
		q = :( $q & !isna($(ItemSet[i])))
	end

	q
end

function getAndQuery(ItemSet::Array{ASCIIString})
	getAndQuery(map(symbol, ItemSet))
end

function getAndQuery(ItemSet::Array{Any})

	getAndQuery(map(symbol, convert(Array{ASCIIString}, ItemSet	)))
end

function getAndEmptyFields(ItemSet::Array{ASCIIString})
	getAndEmptyFields(map(symbol, ItemSet))
end

function getAndEmptyFields(ItemSet::Array{Symbol})
	q = :(isna($(ItemSet[1])))

	for i=2:length(ItemSet)
		q = :( $q & isna($(ItemSet[i])))
	end

	q
end



function getColSets(df::DataFrame, idcol::ASCIIString, featurerange)
	cols=colnames(df)[featurerange]

	function getNonNACols(sdf::SubDataFrame, range)
		A=DataArray(sdf.parent[sdf.rows,range])
		res=Set{ASCIIString}()
		for i=1:length(A)
			if !isna(A[i])
				push!(res, cols[i])
			end
		end
		res
	end

	res=by(df, idcol, sdf->getNonNACols(sdf, featurerange))
	res.colindex.names[2]="featuresets"
	res

end


