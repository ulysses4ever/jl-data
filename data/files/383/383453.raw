using PyPlot

function plotFlowRates(pathtodata)
	close("all")
	fd = readdlm(pathtodata, ',')
	t = fd[:,1]
	Fol = fd[:,2]
	Fsa = fd[:,3]
	Fsp =fd[:,4]
	Fep = fd[:,5]
	Fmp = fd[:,6]
	Fbp = fd[:,7]
	Fhp = fd[:,8]
	For =fd[:,9]
	Fpa = fd[:,10]
	names = ["Fol", "Fsa", "Fsp", "Fep", "Fmp", "Fbp", "Fhp", "For", "Fpa" ]
	figure(figsize=([23,13]))
	for j in collect(1:size(fd,2)-1)
		plt[:subplot](9,1,j)
		plot(t, fd[:,j+1])
		ylabel(names[j])
		if(j in collect(5:6))
			axis([0, 100, 0,20])
		end

		if(j ==7)
			axis([0, 100, 0,5])
		end
	end
	plt[:subplot](9,1,2)
	plot(t, Fsp+Fep+Fmp+Fbp+Fhp, "kx")
	
end
