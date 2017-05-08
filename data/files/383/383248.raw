using PyPlot

function makeSobolGraph()
	close("all")
	numparams = 77
	fig=figure(figsize=[25,15])
	data = readdlm("sensitivity/SobolOutput_pm50_tPA2_N100_04_19_2017.txt")
	topHalf = data[1:numparams+1, :]
	@show topHalf
	usefulData = topHalf[2:end, :]
	positions = collect(0:numparams-1)
	bar(positions, usefulData[:,4],color = "k", yerr=usefulData[:,5], align="center")
	ax = gca()
	ax[:xaxis][:set_ticks](positions)
	ax[:xaxis][:set_ticklabels](usefulData[:,1], rotation = 90, fontsize = 8)
	ylabel("Total Order Sensitivity Indicies")
	axis([0,numparams,0,1])
	savefig("sensitivity/SobolTotalOrderN100.pdf")
	
end
