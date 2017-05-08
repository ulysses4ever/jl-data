using DataFrames
using StatsBase

include("makeMorrisPlot.jl")

function doSpearmanRanking()
	cluster1local = readtable("/home/rachel/Documents/work/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsIntermediateDirCluster1n10Jun22/with10setsofparams.txt")
	cluster2local = readtable("/home/rachel/Documents/work/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsIntermediateDirCluster2/with10setsofparams.txt")
	cluster1extsens = [0.0530599843,0.0141198572,0.0001702913,3.9085363074,0.0156756212]
	cluster1extsensStDevs = [0.1700221129,0.0174122978,0.0002004598,2.102214676,0.022229131]

	cluster2extsens = [0.1902080409,0.0171401267,0.0004667665,2.9584366977,0.0031292916]
	cluster2extsensStDevs =[0.2241124061,0.0227180787,0.0004507436,1.5371694223,0.0038091545]

	names = ["alpha","beta", "M", "k2"]

	for j in collect(1:4)
		row = [names[j], cluster1extsens[j], cluster1extsensStDevs[j]]
		push!(cluster1local, row)
	end

	for j in collect(1:4)
		row = [names[j], cluster2extsens[j], cluster2extsensStDevs[j]]
		push!(cluster2local, row)
	end
	@show cluster1local
	cluster1localrank = sortperm(cluster1local[:mean])
	cluster2localrank = sortperm(cluster2local[:mean])


#	@show head(morrisData)
#	@show head(sobolData)
#	combined = DataFrame(names = morrisData[:Parameter], Mu_Star = morrisData[:Mu_Star], SobolT = sobolData[:ST], Sobol1 =sobolData[:S1])
#	morrisRank = sortperm(combined[:Mu_Star])
#	sobolRank = sortperm(combined[:SobolT])
#	sobol1Rank = sortperm(combined[:Sobol1])

#	combined[:sobolRank]=sobolRank
#	combined[:morrisRank]=morrisRank
#	@show combined
#	@show corSpearman =corspearman(sobolRank, morrisRank)
#	@show corKendall = corkendall(sobolRank, morrisRank)
#	return corSpearman
end
