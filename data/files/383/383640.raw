using PyPlot

function makeSingleSenstivityGraph()
	#from best params
	means = [4.8352005977	0.2499585633	0.5087998435	0.003324595	0.0204435404	0.5719697096	19.9293514859	1.1339045911	4.465101859]
	stdevs = [1.4016395014	0.0725167492	0.1359924827	0.0013042933	0.0055190851	0.2438977968	5.5839577142	0.4728329027	1.2637169874]
	pretty_names = [L"$\frac{dh}{dN}$", L"$\frac{dh}{dk_1}$", L"$\frac{dh}{d\tau_1}$", L"$\frac{dh}{d\tau_2}$", L"$\frac{dh}{d\tau_{ach}}$", L"$\frac{dh}{d\tau_{nor}}$", L"$\frac{dh}{dh_0}$ ", L"$\frac{dh}{dm_{nor}}$", L"$\frac{dh}{dm_{ach}}$"]
	xplot = transpose(collect(1:size(means,2)))
	@show xplot
	@show size(xplot)
	@show size(means)
	@show size(stdevs)
	fig = figure()
	hold("on")
	semilogy(xplot, means, "ko")
	#errorbar(xplot, means, yerr=stdevs, color="black")
	yscale("log")
	ax = gca()
	ax[:set_xticklabels](pretty_names)
	#fancy tricks to make it so the graph doesn't cut off at the ends and the labels stay in the right place
	xticks, xticklables = plt[:xticks]()
	xmin = (3*xticks[1] - xticks[2])/2.0
	xmax = (3*xticks[end] - xticks[end-1])/2.0
	plt[:xlim](xmin, xmax)
	plt[:xticks](xticks)

end
