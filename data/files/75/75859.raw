# Type that keeps mode coupling analysis data
# 2014 murozturk@ku.edu.tr

include("helper.jl")

# fields are kept in the order they are used in analysis
immutable modeCouplingAnalysis
	md::protein
	R2r::Matrix{Float64}
	r::Matrix{Float64}
	coef::Matrix{Float64}
	rf1::Matrix{Float64}
	r2R::Matrix{Float64}
	Rf1::Matrix{Float64}
	kl::Vector{Float64}
	js::Vector{Float64}
end

# Constructor performs mode coupling analysis for a protein
# takes md coordinates R as input
# ith cloumn is all samples for mode i  
# nModes = 3* nResidues

function modeCouplingAnalysis(R::Matrix{Float64}, index=1:size(R,2))

	nSamples, nModes = size(R)
	println("Beginning mode coupling analysis")
	println("nSamples, nModes :", nSamples, " ", nModes)
	
	# convert R to onur's convention (for debugging purposes)
	#R= [ R[:,1:3:end] R[:,2:3:end] R[:,3:3:end] ]
	
	md = protein(R, index)
	
	R2r, r2R = modeSpaceTransform (md)
	
	println ("Transforming into modespace...")
	
	r=(R2r*md.R')'

	r=removeRows(r, findOutliers(r))
	nSamples = size(r,1)
	
	# calculating hermite coefficients
	coef = coefHermit(r)
	
	# sampling f1 distribution 
	rf1 = sampleHermit(nSamples, coef)
	
	println ("Transforming back into cartesian space...")
	
	Rf1 = (r2R*rf1')'
	
	println ("Calculating Kullback–Leibler distances...")
	kl = perResidue( klDist(md.R, Rf1))
	
	println ("Calculating Jensen-Shannon distances...")
	js = perResidue( jsDist(md.R, Rf1))

	modeCouplingAnalysis(md, R2r, r, coef, rf1, r2R, Rf1, kl, js )
end

# high level recall analysis that also handles indexing and normalizing 
function recall(mcA::modeCouplingAnalysis, targetSet::Vector{Int})
	normalizedJs= mcA.js ./ mcA.md.stdPerRes
	predictPerm = sortperm(normalizedJs, rev=true)
	recall(mcA.md.index[predictPerm], targetSet  )
end

println ("Making dummy run for JIT compiler...")
tmp = modeCouplingAnalysis(randn(9,9));
recall(tmp,[1])
println ("Ready to roll.")


