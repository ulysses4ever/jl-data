using Graphs
using Distributions

# Estimates the sparsity structure of the inverse covariance matrix
# using moving blocks bootstrap.
function estimatesparsity(solverFunc, data, bootstrapSize; blockSize=1)

	# Run many bootstrap samples and see how confident we are that each edge is non-zero
	densities = zerotaildensities(size(data)[2],size(data)[2])
	datac = deepcopy(data)
	for i in 1:bootstrapSize
		blocksample!(data, datac, blockSize)
		result = solverFunc(datac)
		addsample!(densities, result)
	end
	logpvalue(densities)
end

function estimatecovsparsity(data, bootstrapSize; transform=x->x, blockSize=1)

	# Run many bootstrap samples and see how confident we are that each edge is non-zero
	densities = zerotaildensities(size(data)[2],size(data)[2])
	for i in 1:bootstrapSize
		result = transform(blocksamplecov(data, blockSize))
		addsample!(densities, result)
	end
	logpvalue(densities)
end
# function estimatesparsity2(solverFunc, data, bootstrapSize; blockSize=1)
# 	positives = zeros(size(data)[2],size(data)[2])
# 	negatives = zeros(size(data)[2],size(data)[2])
	
# 	# Run many bootstrap samples and see how confident we are that each edge is non-zero
# 	prevMean = zeros(size(positives)...)
# 	currMean = zeros(size(positives)...)
# 	variance = zeros(size(positives)...)
# 	datac = deepcopy(data)
# 	for i in 1:bootstrapSize
# 		blocksample!(data, datac, blockSize)
# 		result = solverFunc(datac)
# 		currMean = prevMean .+ (result .- prevMean) ./ i
# 		variance .+= (result .- prevMean) .* (result .- currMean)
# 		positives += result .> 0
# 		negatives += result .< 0
# 		prevMean = currMean
# 	end

# 	# This is a matrix of bootstrap estimated z-score p-values
# 	zScores = currMean ./ sqrt(variance ./ (bootstrapSize-1))
# 	zPvals = logccdf(Normal(), abs(zScores))

# 	# This is a matrix of log bootstrap p-values for testing if each entry is non-zero
# 	empPvals = log((bootstrapSize .- maximum(cat(3, positives, negatives), 3)[:,:]) ./ bootstrapSize)
	
# 	maximum(cat(3, zPvals, empPvals), 3)[:,:] .+ log(2) # multiple by two for a two tailed test
# end


type ZeroTailDensity
    mean::Float64
    varSum::Float64
    dataCache::Array{Float64,1}
    threshold::Float64
    totalSamples::Int64
    savedSamples::Int64
    acrossZero::Int64
end
ZeroTailDensity() = ZeroTailDensity(0, 0, Float64[], 0, 0, 0, 0)
function zerotaildensities(dim)
	res = Array(ZeroTailDensity, dim)
	for i in 1:dim
		res[i] = ZeroTailDensity()
	end
	res
end
function zerotaildensities(dim1, dim2)
	res = Array(ZeroTailDensity, dim1, dim2)
	for i in 1:dim1, j in 1:dim2
		res[i,j] = ZeroTailDensity()
	end
	res
end

# this computes the mean and variance sum in a streaming manner
function updatemoments(prevMean, varSum, sample, sampleNumber)
    newMean = prevMean + (sample - prevMean) / sampleNumber
    varSum += (sample .- prevMean) .* (sample .- newMean)
    return newMean,varSum
end

function addsample!(state::ZeroTailDensity, value)
    state.totalSamples += 1
    halfMin = 20

    # until we have enough samples to find the middile of the data we just record all samples
    if state.totalSamples <= halfMin*2
        push!(state.dataCache, value)
        state.savedSamples += 1
        state.mean,state.varSum = updatemoments(state.mean, state.varSum, value, state.savedSamples)
        state.threshold = state.mean # so we know which side of zero to test for small sample sizes

    # once we have enough samples we set our threshold as the median and throw out all higher values
    elseif state.totalSamples == halfMin*2+1
        sort!(state.dataCache, by=abs)
        state.threshold = state.dataCache[halfMin+1]
        state.acrossZero = state.threshold > 0 ? sum(state.dataCache .<= 0) : sum(state.dataCache .>= 0)
        
        # streaming updates of the variance and mean
        state.mean = 0
        state.varSum = 0
        for i in 1:halfMin
            state.mean,state.varSum = updatemoments(state.mean, state.varSum, state.dataCache[i], 2*i-1)
            state.mean,state.varSum = updatemoments(state.mean, state.varSum, state.threshold + state.threshold-state.dataCache[i], 2*i)
        end
        state.savedSamples = halfMin*2 + 1
        state.mean,state.varSum = updatemoments(state.mean, state.varSum, state.dataCache[halfMin+1], state.savedSamples)

        # clear the cache
        state.dataCache = []
        
    # after we have determined the threshold we keep only samples that pass it
    else

        # this only matters if nothing crosses zero (so going past the threshold on the other side of zero is no big deal here)
    	if state.acrossZero == 0 && abs(value) <= abs(state.threshold)
	        state.mean,state.varSum = updatemoments(state.mean, state.varSum, value, state.savedSamples+1)
	        state.mean,state.varSum = updatemoments(state.mean, state.varSum, state.threshold + state.threshold-value, state.savedSamples+2)
	        state.savedSamples += 2
    	end
    end

    # see if this sample crosses zero
    if value == 0 || sign(value) != sign(state.threshold)
        state.acrossZero += 1
    end
end
function addsample!(state::Array{ZeroTailDensity,1}, value::Array{Float64,1})
	for i in 1:length(state)
		addsample!(state[i], value[i])
	end
end
function addsample!(state::Array{ZeroTailDensity,2}, value::Array{Float64,2})
	for i in 1:size(state)[1], j in 1:size(state)[2]
		addsample!(state[i,j], value[i,j])
	end
end

# computes the two-sided p-value of the true value being zero
function logpvalue(state::ZeroTailDensity)
    if state.acrossZero > 0
        return log(state.acrossZero/state.totalSamples)
    else
    	stdDev = sqrt(state.varSum / (state.savedSamples-1))
    	if stdDev == 0 stdDev = 10e-6 end

    	# adjust for two tails and not exactly getting 1/2 the dist
	    if state.threshold > 0
	        return logcdf(Normal(state.mean, stdDev), 0) + log(2)
	    else
	        return logccdf(Normal(state.mean, stdDev), 0) + log(2)
	    end
    end
end
function logpvalue(state::Array{ZeroTailDensity,1})
	res = zeros(length(state))
	for i in 1:length(state)
		res[i] = logpvalue(state[i])
	end
	res
end
function logpvalue(state::Array{ZeroTailDensity,2})
	res = zeros(size(state)...)
	for i in 1:size(state)[1], j in 1:size(state)[2]
		res[i,j] = logpvalue(state[i,j])
	end
	res
end
function pvalue(state::ZeroTailDensity)
	return exp(logpvalue(state))
end
function pvalue(state::Array{ZeroTailDensity,1})
	return exp(logpvalue(state))
end
function pvalue(state::Array{ZeroTailDensity,2})
	return exp(logpvalue(state))
end

# This generate the covariance matrix for a random GGM with the given sparsity
function randomcov(N, sparsity)
    I = eye(N,N)
    for i in 1:N, j in i+1:N
        if rand() < sparsity
            I[i,j] = I[j,i] = randn()
        end
    end
    
    I += eye(N)*-1.1*minimum(eig(I)[1])
    inv(I)
end


function blocksample!(source, target, blockSize=1)
	sourceSize = size(source)[1]
	targetSize = size(target)[1]
	for i in 1:blockSize:targetSize
		len = min(i+blockSize-1,targetSize)-i
		ind = rand(1:sourceSize-blockSize+1)
		target[i:i+len,:] = source[ind:ind+len,:]
	end
end

# this assume the data is mean zero and unit variance
function blocksamplecov(data, blockSize=1)
	dataSize = size(data)[1]
	res = @parallel (.+) for i in 1:blockSize:dataSize
		len = min(i+blockSize-1,dataSize)-i
		ind = rand(1:dataSize-len)
		transpose(data[ind:ind+len,:]) * data[ind:ind+len,:]
	end
	res ./ (dataSize-1)
end

# This filters out rows with too many NA values
function dropnarows(df, tolerance=0)
    validRows = Array(Bool, size(df)[1])
    for (i,row) in enumerate(eachrow(df))
        count = 0
        for j in 1:size(df)[2]
            if isna(row[j])
                count += 1
            end
        end

        validRows[i] = count <= tolerance*size(df)[2]
    end
    
    df[validRows,:]
end

 # Set all the NA's to rand data (this is a lame version of missing data interpolation...should only weaken associations though)
function imputerandom!(data, test=isna)
    for i in 1:size(data)[2]
        valid = data[:,i][filter(x->!test(data[x,i]), 1:size(data)[1])]
        for j in 1:size(data)[1]
            if test(data[j,i])
                data[j,i] = valid[rand(1:length(valid))]
            end
        end
    end
end
function imputerandom(data)
	out = deepcopy(data)
    imputerandom!(out)
    out
end



# # checks how many edges match between two graphs, where matching is
# # based on the given attribute
# function edgematches(g1, g2, matchAttr)
    
#     # For performance reasons decide who is smaller
#     if length(edges(g1)) < length(edges(g2))
#         smaller = g1
#         bigger = g2
#     else
#         smaller = g2
#         bigger = g1
#     end
    
#     # Build a hash to test membership in the smaller graph
#     edgeHash = Dict()
#     count = 0
#     for e in edges(smaller)
#         sa = source(e).attributes
#         ta = target(e).attributes
#         if haskey(sa, matchAttr) && haskey(ta, matchAttr)
            
#             # The matching attribute fields can be either values or arrays of values
#             # if they are arrays then any match in the array is considered a match for the edge
#             if typeof(sa[matchAttr]) <: Array
#                 slabels = sa[matchAttr]
#             else
#                 slabels = [sa[matchAttr]]
#             end
#             if typeof(ta[matchAttr]) <: Array
#                 tlabels = ta[matchAttr]
#             else
#                 tlabels = [ta[matchAttr]]
#             end
            
#             # We leave an edge mark that is common to all of these hashes so we only count the edge once
#             edgeMark = [false]
#             for sl in slabels, tl in tlabels
#                 edgeHash[(sl, tl)] = edgeMark
#                 edgeHash[(tl, sl)] = edgeMark
#             end
#             count += 1
#         end
#     end
    
#     # Now count how many matched pairs of edges we can make
#     # Note that an edge can only be part of a single pair, which is important
#     # if one of the graphs has duplicate edges with respect to the matchAttr
#     matches = 0
#     for e in edges(bigger)
#         sa = source(e).attributes
#         ta = target(e).attributes
#         if haskey(sa, matchAttr) && haskey(ta, matchAttr)
            
#             if typeof(sa[matchAttr]) <: Array
#                 slabels = sa[matchAttr]
#             else
#                 slabels = [sa[matchAttr]]
#             end
#             if typeof(ta[matchAttr]) <: Array
#                 tlabels = ta[matchAttr]
#             else
#                 tlabels = [ta[matchAttr]]
#             end
            
#             for sl in slabels, tl in tlabels
#                 k = (sl, tl)
#                 if haskey(edgeHash, k) && !edgeHash[k][1]
#                     edgeHash[k][1] = true
#                     matches += 1
#                 end
#             end
#         end
#     end
    
#     matches
# end