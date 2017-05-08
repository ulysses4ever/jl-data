using DataFrames
using PyPlot

function makeBarGraph()
	close("all")
	pathCluster1MSE =  "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/MSEsAug26/cluster1MSEsUsing10BestParams.txt"
	pathCluster2MSE =  "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/MSEsAug26/cluster1MSEsUsing10BestParams.txt"
	pathOriginalParamsMSE = "/home/rachel/Documents/work/optimization/SingleObjective/testingAug24/MSEOriginalParams.txt"


	originalMSE = readtable(pathOriginalParamsMSE, header = false)
	cluster1MSE = readtable(pathCluster1MSE, header=false)
	cluster2MSE = readtable(pathCluster2MSE, header=false)
	bothClusters = vcat(cluster1MSE, cluster2MSE)
	@show head(bothClusters) 
	@show size(bothClusters)

	full = join(bothClusters, originalMSE, on =:x1) #x2_1 is original params, #x2 in best params
	sort!(full, cols=[order(:x2)])
	@show head(full)
	f =figure(figsize=(30,10))
	hold("on")
	bar(full[:x1], full[:x2], color = ".9")
	bar(full[:x1], full[:x2_1], color = ".2", alpha = .5)
	ax = gca()
	ax[:set_xticklabels](ax[:get_xticklabels](), rotation=90, fontsize = 6) #rotate xlabels
	legend(["Best parameters", "Original Parameters"])
	xlabel("Patient")
	ylabel("MSE")
	savefig("BarGraphComparsionOfPatients.pdf")

end
