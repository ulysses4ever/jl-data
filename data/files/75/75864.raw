# Helper functions for mode-coupling analysis
# 2014 - murozturk@ku.edu.tr

# type to pass around full protein data

include("hermit.jl")
include("protein.jl")

function R2deltaR (R::Matrix{Float64})
	R .-= mean(R, 1)
end
	
# returns transformation matrices to and from modespace
# also returns covariance matrix

function modeSpaceTransform (p::protein)
	
	println ("Calculating eigen decomposition...")
	# satisfies eigVec*diagm(eigVal)*eigVec' = gamma
	eigVal, eigVec = eig(p.covariance)

	#Reverse everything to get decreasing order (ala MATLAB)
	eigVal = reverse!(eigVal)
	eigVec = -reverseColumns(eigVec)

	eigZero=0
	for ev in eigVal
		ev < 1e-7 && (eigZero += 1)
	end

	#eigZero = 6 # assume 6 zero eigenvalues (like onur)

	println ("Number of zero eigenvalues : ", eigZero)
	
	# remove zero eigenvalues and eigenvectors
	#eigVal = eigVal[eigZero+1:end]
	#eigVec = eigVec[:,eigZero+1:end]
	eigVal = eigVal[1:end-eigZero]
	eigVec = eigVec[:,1:end-eigZero]
	
	println ("Calculating R2r transformation...")
	R2r = diagm(eigVal.^(-1/2)) * eigVec'
	
	println ("Calculating r2R transformation...")
	r2R = eigVec * diagm(eigVal.^(1/2))

	return R2r, r2R

end

# returns kl distance between two samples
# it ignores all zeros
function klDist(p::Vector{Float64} , q::Vector{Float64})

	nBins = int(sqrt(minimum( [length(p), length(q)] )))
	bins  = linspace(minimum([p; q]), maximum([p; q]), nBins+1 )

	pDist = hist(p,bins)[2] / length(p)
	qDist = hist(q,bins)[2] / length(q)

	total = 0.
	for i=1:nBins
		if pDist[i] > 1e-8 && qDist[i]> 1e-8
			total += pDist[i] * log(pDist[i]/qDist[i])
		end
	end
	return total

end
function klDist(p::Matrix{Float64} , q::Matrix{Float64})
	if size(p,2) != size(q,2) 
		println("nModes not equal btw. samples")
	else 
		nModes = size(p,2)
		kl = Float64[klDist(p[:,i], q[:,i]) for i=1:nModes ]
	end
end

# returns jenson-shannon distance between two samples
function jsDist(p::Vector{Float64} , q::Vector{Float64})

	nBins = int(sqrt(minimum( [length(p), length(q)] )))
	bins  = linspace(minimum([p; q]), maximum([p; q]), nBins+1 )

	pDist = hist(p,bins)[2] / length(p)
	qDist = hist(q,bins)[2] / length(q)

	mDist = (pDist+qDist)/2

	total = 0.
	for i=1:nBins
		if pDist[i]>1e-8
			total += pDist[i] * log(pDist[i]/mDist[i])
		end
		if qDist[i]>1e-8
			total += qDist[i] * log(qDist[i]/mDist[i]) 
		end
	end
	return total/2

end
function jsDist(p::Matrix{Float64} , q::Matrix{Float64})
	if size(p,2) != size(q,2) 
		println("nModes not equal btw. samples")
	else 
		nModes = size(p,2)
		js = Float64[jsDist(p[:,i], q[:,i]) for i=1:nModes ]
	end
end

# returns rows (frames) with displacement(s) greater than threshold*std
	
function findOutliers(data::Matrix{Float64}, threshold=4.0; standard=true)
	# fast version for (mean=0, std=1)
	if standard
		find(maximum (abs(data),2) .> threshold )

	# more general version (mean=?, std=?)
	else

		artifacts=[]
		for mode=1:size(data,2)
			s = std(data[:,mode])
			m = mean(data[:,mode])
			tmp = find( abs(data[:,mode].-m)  .> threshold*s)
			artifacts= union(artifacts, tmp)
		end
	return sort(artifacts)
	end
end

# removes rows (frames) from given data

function removeRows(data::Matrix, rows::Vector)
	keep = setdiff(1:size(data,1), rows)
	return data[keep,:]
end

# returns the same matrix with column order reversed
function reverseColumns(x::Matrix)
	nColumns = size(x,2)
	xHat = similar(x)
	for i=1:nColumns 
		xHat[:,i] = x[:,nColumns+1-i] 
	end
	return xHat
end

# Returns property per residue
# using [ xyz xyz xyz] convention

function perResidue (x::Vector)
	x[1:3:end] + x[2:3:end] + x[3:3:end] 
	# Onur convention
	#x[1:nModes/3] + x[nModes/3+1:2nModes/3] + x[2nModes/3+1:end]
end

# Performs recall analysis given predictions and target set
# predictions must be in decreasing order
# returns normalized recallRate, poolsize
function recall (prediction::Vector{Int}, targetSet::Vector{Int})

	nTargets = length(targetSet)
	recallRate = Array(Float64,nTargets)
	poolSize = Array(Float64,nTargets)
	
	hits=0
	i=1

	while hits<nTargets && i<length(prediction) 
		if issubset(prediction[i],targetSet)
			hits+=1
			recallRate[hits]=length(intersect(prediction[1:i],targetSet))
			poolSize[hits] = i
		end
		i += 1
	end
	
	return recallRate/nTargets, poolSize/length(prediction)
end
