include("runPatient.jl")

function runAllPatients()
	cluster1path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	cluster1IDs = AbstractString[]
	cluster2IDs = AbstractString[]

	f = open(cluster1path)

	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster1IDs, strip(ln))
		end
	end
	close(f)
	g = open(cluster2path)
	for ln in eachline(g)
		if(length(ln)>1)
			push!(cluster2IDs, strip(ln))
		end
	end

	
	allIDs = Array[]
	push!(allIDs, cluster1IDs)
	push!(allIDs, cluster2IDs)
	clusterCounter = 1
	for cluster in allIDs
		for patient in cluster
			@show patient
			runPatient(patient)
		end
	end

end

runAllPatients()
