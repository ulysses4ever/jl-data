function findMaxMin()
	data = readdlm("/home/rachel/Documents/work/optimization/SingleObjective/lettingk2andBetavary/outputAug30/clusterallpatientsthread1paramstolAll1E-8Take1Cleaned.txt", header = false, ',')
	paramnames = ["N", "k1", "tau1", "tau2", "tauach", "taunor", "h0", "Mnor", "Mach", "beta", "k2"]
	#@show data
	max = maximum(data,1)
	min = minimum(data,1)
	for j in collect(1:length(paramnames))
		println(string(paramnames[j], " ", min[j], " ", max[j]))
	end
end
