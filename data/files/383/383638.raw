using POETs
require("utilsSensitivityFiniteDifferences.jl")

function parsePoetsoutput(filename)
	f = open(filename)
	alltext = readall(f)
	close(f)

	outputname = "textparsing.txt"
	number_of_parameters = 9
  	number_of_objectives = 2
	ec_array = zeros(number_of_objectives)
  	pc_array = zeros(number_of_parameters)
	rank_array = zeros(1)	
	counter =1
	for grouping in matchall(r"\[([^]]+)\]", alltext)
		cleanedgrouping = replace(grouping, "[", "")
		nocommas = replace(cleanedgrouping, ","," ")
		allcleaned = replace(nocommas, "]", "")
		outfile = open(outputname, "w")
		write(outfile, allcleaned)
		close(outfile)
		formatted = readdlm(outputname)
		if(counter == 1)
			ec_array = [ec_array formatted]
			counter = counter +1
		elseif(counter == 2)
			pc_array = [pc_array formatted]
			counter = counter +1
		elseif(counter == 3)
			rank_array = [rank_array formatted]
			#@show formatted
			counter =1
		end
		
	end
	rerankedarray=rank_function(ec_array[:,2:end])
	return ec_array, pc_array,rerankedarray
end

function main()
	inputfilename = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputJun3parallel/poetsinfo.txt"
	ec_array, pc_array, ra_array = parsePoetsoutput(inputfilename)

	zeroRankParams = zeros(size(pc_array,1))
	zeroRankErrors = zeros(size(ec_array,1))
	#get the rank zero params and errors
	for j in collect(2:size(ec_array,2)-1)
		if(ra_array[j]==0)
			zeroRankErrors = [zeroRankErrors ec_array[:,j]]
			zeroRankParams = [zeroRankParams pc_array[:,j]]
		end
	end
	zeroRankErrors = zeroRankErrors[:,2:end]
	zeroRankParams = zeroRankParams[:, 2:end]

	
	#get the "good" parameters for cluster 1
	upperlimit = 135.2 #135.2 for 10 sets #137-for 24 sets in cluster 1
	goodparams = zeros(size(pc_array,1))
	for j in collect(1:size(zeroRankErrors,2))
		if(zeroRankErrors[1,j]<=upperlimit)
			goodparams = [goodparams zeroRankParams[:,j]]
		end
	end
#	upperlimit = 178.9 for 10 parameter sets in cluster 2
#	goodparams = zeros(size(pc_array,1))
#	for j in collect(1:size(zeroRankErrors,2))
#		if(zeroRankErrors[2,j]<=upperlimit)
#			goodparams = [goodparams zeroRankParams[:,j]]
#		end
#	end

	goodparams = goodparams[:,2:end]
	@show size(goodparams)
	#paramsetcounter = 1
	touch("cluster1bestparams.txt")
	for k in collect(1:size(goodparams,2))
		set = goodparams[:,k]
		@show set
		g = open("cluster1bestparams.txt", "a")
		write(g, string(set))
		close(g)
		println(string("On set number", k, "out of ", size(goodparams,2)))
		parallel_doSensitivitiesMakeDFs(set,k)
		#paramsetcounter=paramsetcounter+1
		
	end

end

function mainExtendedSensitivites()
	inputfilename = "/home/rachel/Documents/optimization/multiobjective/usingPOETs/outputJun3parallel/poetsinfo.txt"
	ec_array, pc_array, ra_array = parsePoetsoutput(inputfilename)

	zeroRankParams = zeros(size(pc_array,1))
	zeroRankErrors = zeros(size(ec_array,1))
	#get the rank zero params and errors
	for j in collect(2:size(ec_array,2)-1)
		if(ra_array[j]==0)
			zeroRankErrors = [zeroRankErrors ec_array[:,j]]
			zeroRankParams = [zeroRankParams pc_array[:,j]]
		end
	end
	zeroRankErrors = zeroRankErrors[:,2:end]
	zeroRankParams = zeroRankParams[:, 2:end]

	
	#get the "good" parameters for cluster 1
#	upperlimit = 135.2 135.2 for 10 sets #137-for 24 sets in cluster 1
#	goodparams = zeros(size(pc_array,1))
#	for j in collect(1:size(zeroRankErrors,2))
#		if(zeroRankErrors[1,j]<=upperlimit)
#			goodparams = [goodparams zeroRankParams[:,j]]
#		end
#	end
	upperlimit = 178.9 #for 10 parameter sets in cluster 2
	goodparams = zeros(size(pc_array,1))
	for j in collect(1:size(zeroRankErrors,2))
		if(zeroRankErrors[2,j]<=upperlimit)
			goodparams = [goodparams zeroRankParams[:,j]]
		end
	end

	goodparams = goodparams[:,2:end]
	@show size(goodparams)
	#paramsetcounter = 1
	touch("cluster2bestparams.txt")
	for k in collect(1:size(goodparams,2))
		set = goodparams[:,k]
		@show set
		g = open("cluster2bestparams.txt", "a")
		write(g, string(set))
		close(g)
		println(string("On set number", k, "out of ", size(goodparams,2)))
		MultiObjdoExtendedSensitivitiesMakeDFs_parallel(set,k)
		#paramsetcounter=paramsetcounter+1
		
	end

end


