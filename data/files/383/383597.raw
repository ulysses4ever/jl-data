using PyPlot
using LaTeXStrings
using DataFrames

function makePlot(data)
	close("all")
	name_strings = [L"\alpha", L"N", L"M", L"k_1", L"k_2", L"\tau_1", L"\tau_2", L"\tau_{ach}", L"\tau_{nor}", L"\beta", L"h_0", L"m_{nor}", L"m_{ach}"]
	figure()
	hold("on")
	j = 1
	k = 1
	while(j<=size(data,1))
		#@show string("\$", name_strings[j], "\$"), j, k
		scatter(data[j], data[j+1], s = 500,c ="k",marker = string(name_strings[k]))
		k = k+1
		j = j+2
	end
	xlabel(L"\mu*", fontsize = 20)
	ylabel(L"\sigma", fontsize = 20)
	savefig("MorrisPlotN100Cluster2.pdf")
end

function readData(path)
	cluster1path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster1subjectIDs"
	cluster2path = "/home/rachel/Documents/work/optimization/multiobjective/usingPOETs/cluster2subjectIDs"
	cluster1patients = AbstractString[]
	cluster2patients = AbstractString[]

	f = open(cluster1path)
	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster1patients, strip(ln))
		end
	end
	close(f)

	f = open(cluster2path)
	for ln in eachline(f)
		if(length(ln)>1)
			push!(cluster2patients, strip(ln))
		end
	end
	close(f)


		colnames = Vector(["alpha", "alphaStDev", "N", "NStDev", "M", "MStDev", "k1", "k1StDev", "k2", "k2StDev", "tau1", "tau1StDev", "tau2", "tau2StDev", "tauAch", "tauAchStDev", "tauNor", "tauNorStDev", "beta", "betaStDev", "h0", "h0StDev", "mNor", "mNorStDev", "mAch", "mAchStDev"])
	#@show length(colnames)
	alldata = DataFrame(transpose(ones(length(colnames))))
	allfiles = readdir(path)
	for file in allfiles
		#@show string("s",file[1:23])
		if(in(string("s",file[1:23]), cluster2patients))#only gather cluster 2 patients
			currdata = readtable(string(path,file),  header = true,  separator = ' ',makefactors = true, nrows = 13, eltypes = [UTF8String, Float64, Float64, Float64, Float64])
			row = Float64[]
			drop = false #throw out what I think are erronious data
			for k in collect(1:size(currdata,1))
				push!(row, currdata[:Mu_Star][k])
				push!(row, currdata[:Sigma][k])
				if(currdata[:Mu_Star][k]>1000)
					#@show file
					drop = true
				end
			end
			#@show row
			if(drop == false)
				push!(alldata, row)
			end
		end
	end
	deleterows!(alldata, 1) #remove filler row with ones
	return alldata
end

function main()
	path = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/MorrisOutputdata25PercentN100/"
	alldata = readData(path)
	means = colwise(mean, alldata)
	@show means
	makePlot(means)
	
end
