using PyPlot
using LaTeXStrings
using DataFrames

function makePlot(data,stdevs)
	close("all")
	name_strings = [L"\alpha", L"N", L"M", L"k_1", L"k_2", L"\tau_1", L"\tau_2", L"\tau_{ach}", L"\tau_{nor}", L"\beta", L"h_0", L"m_{nor}", L"m_{ach}"]
	figure(figsize=([20,20]))
	hold("on")
	j = 1
	k = 1
	while(j<=size(data,1))
		#@show string("\$", name_strings[j], "\$"), j, k
		#scatter(data[j], data[j+1], s = 500,c ="k",marker = string(name_strings[k]))
		scatter(data[j], stdevs[k], s = 50,c ="k")
		annotate(name_strings[k], xy = [data[j], stdevs[k]], fontsize = 30)
		k = k+1
		j = j+2
	end
	xlabel(L"\mu*", fontsize = 30)
	ylabel(L"\sigma", fontsize = 30)
	ax = gca()
	setp(ax[:get_yticklabels](),fontsize=20)
	setp(ax[:get_xticklabels](),fontsize=20)
	savefig("Plots/MorrisPlotN20Cluster2.pdf")
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
	variances = Float64[]
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
				#push!(variances, currdata[:Sigma][k])
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

function calculateAvgVariance(data)
	variances = Float64[]
	for j in collect(1:size(data,2))
		#only care about even columns, hold sigma
		if(mod(j,2)==0)
			currcol = data[j]
			sum = 0
			for k in collect(1:length(currcol))
				sum = sum +(currcol[k])^2
			end
			push!(variances, sum/length(currcol))
		end
	end
	return variances
end

function main()
	path = "/home/rachel/Documents/work/optimization/sensitivityanalysis/PCA/MorrisOutputdata25PercentN20/"
	alldata = readData(path)
	means = colwise(mean, alldata)
	variances = calculateAvgVariance(alldata)
	stdevs = sqrt(variances)
	@show means
	makePlot(means,stdevs)
	return alldata
end
