using DataFrames
using PyPlot

function makeBarGraph()
	close("all")
	pathBestParamsMSE =  "/home/rachel/Documents/work/optimization/SingleObjective/testingAug24/MSEBestParams.txt"
	pathOriginalParamsMSE = "/home/rachel/Documents/work/optimization/SingleObjective/testingAug24/MSEOriginalParams.txt"
	bestMSE = readtable(pathBestParamsMSE, header = false)
	originalMSE = readtable(pathOriginalParamsMSE, header = false)
	full = join(bestMSE, originalMSE, on =:x1) #x2_1 is original params, #x2 in best params
	sort!(full, cols=[order(:x2_1)])
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
