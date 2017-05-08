using DataFrames
using PyPlot

function makeMultiSensitivityGraph()
	close("all")
	cluster1 = readtable("/home/rachel/Documents/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsIntermediateDirCluster1n10Jun22/with10setsofparams.txt")
	cluster2 = readtable("/home/rachel/Documents/optimization/sensitivityanalysis/ParallelUsingFDSlowerCoolingParamsIntermediateDirCluster2/with10setsofparams.txt")
	@show sort!(cluster1, cols = [order(:mean)])
	@show sort!(cluster2, cols = [order(:mean)])

	sort!(cluster1, cols = [order(:name)])
	sort!(cluster2, cols = [order(:name)])
	@show cluster1
	@show cluster2
	#pretty_namescluster1 = [L"$\frac{dh}{d\tau_{nor}}$ ", L"$\frac{dh}{d\tau_1}$", L"$\frac{dh}{dk_1}$",L"$\frac{dh}{d\tau_2}$", L"$\frac{dh}{d\tau_{ach}}$", L"$\frac{dh}{dm_{nor}}$", L"$\frac{dh}{dm_{ach}}$",  L"$\frac{dh}{dN}$", L"$\frac{dh}{dh_0}$"] 
	#pretty_names = [L"$\frac{dh}{dN}$",L"$\frac{dh}{dh_0}$",  L"$\frac{dh}{dk_1}$", L"$\frac{dh}{dm_{ach}}$",  L"$\frac{dh}{dm_{nor}}$",L"$\frac{dh}{d\tau_1}$",L"$\frac{dh}{d\tau_2}$", L"$\frac{dh}{dm_{ach}}$", L"$\frac{dh}{dm_{nor}}$"]
	pretty_names = [L"$S_{N}$",L"$S_{h_0}$",L"$S_{k_1}$", L"$S_{m_{ach}}$",L"$S_{m_{nor}}$", L"$S_{\tau_1}$", L"$S_{\tau_2}$", L"$S_{\tau_{ach}}$", L"$S_{\tau_{nor}}$", L"$S_{\alpha}$", L"$S_{\beta}$", L"$S_M$", L"$S_{k_2}$", L"$S_{\tau_d}$"]
	@show pretty_names

	adjusterstdevc1 = .434*cluster1[:stdev]./cluster1[:mean]
	adjusterstdevc2= .434*cluster2[:stdev]./cluster2[:mean]

	cluster1extsens = [0.0530599843,0.0141198572,0.0001702913,3.9085363074,0.0156756212]
	cluster1extsensStDevs = [0.1700221129,0.0174122978,0.0002004598,2.102214676,0.022229131]

	cluster2extsens = [0.1902080409,0.0171401267,0.0004667665,2.9584366977,0.0031292916]
	cluster2extsensStDevs =[0.2241124061,0.0227180787,0.0004507436,1.5371694223,0.0038091545]

	@show adjusterstdevc1
	PyCall.PyDict(matplotlib["rcParams"])["font.sans-serif"] = ["Helvetica"]

	xplot = collect(1:size(cluster1,1))
	xplot2 = collect(size(cluster1,1)+1: size(cluster1,1)+size(cluster1extsens,1))
	@show  xplot2
	fig = figure()
	hold("on")
	semilogy(xplot,cluster1[:mean], "kD")
	#errorbar(xplot,cluster1[:mean], yerr=cluster1[:stdev], color = "black", linestyle="None") #yerr=adjusterstdevc1
	semilogy(xplot,cluster2[:mean], color = ".5", markeredgecolor =".5", "D")
	#errorbar(xplot,cluster2[:mean], yerr=cluster2[:stdev], color = ".5", linestyle="None")
	semilogy(xplot2, cluster1extsens, "kd")
	semilogy(xplot2, cluster2extsens, color = ".5", markeredgecolor =".5","d")
	yscale("log")#, nonposy = "clip")
	ax = gca()
	plt[:xticks](collect(1:15))
	ax[:set_xticklabels](pretty_names)

	#fancy tricks to make it so the graph doesn't cut off at the ends and the labels stay in the right place
#	xticks, xticklables = plt[:xticks]()
#	@show xticks, xticklables
#	xmin = (3*xticks[1] - xticks[2])/2.0
#	xmax = (3*xticks[end] - xticks[end-1])/2.0
#	@show xmin, xmax
#	plt[:xlim](xmin, xmax)
#	plt[:xticks](xticks)
	savefig("MultiobjectiveSenstivityGraph10familiesofNoErrorBarsWithExtendedSensivities.pdf")
end
