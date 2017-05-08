function calculateMSE(t,predictedThrobin, experimentalData)
	num_points = size(t,1)
	interpolatedExperimentalData = Float64[]
	for j in collect(1:num_points)
		currt = t[j]
		upperindex = searchsortedfirst(experimentalData[:,1], currt, by=abs)
		if(upperindex ==1)
			lowerindex = 1
		else
			lowerindex = upperindex -1
		end

		if(upperindex >= size(experimentalData,1)&& upperindex !=1)
		upperindex = size(experimentalData,1)
		lowerindex = upperindex-1
	end
		val = linearInterp(experimentalData[lowerindex,2], experimentalData[upperindex,2],experimentalData[lowerindex,1], experimentalData[upperindex,1], currt)
		push!(interpolatedExperimentalData,val)
	end
	#@show size(predictedThrobin), size(interpolatedExperimentalData)
	sum = 0.0
	for j in collect(1:size(predictedThrobin,1))
		sum = sum +(predictedThrobin[j]-interpolatedExperimentalData[j])^2
	end
	return sum/size(predictedThrobin,1), interpolatedExperimentalData#MSE
end

function linearInterp(lowerVal, upperVal, tstart, tend,tdesired)
	
	val = lowerVal + (upperVal-lowerVal)/(tend-tstart)*(tdesired-tstart)
	if(isnan(val))
		val = 0.0
	end
	return val
end

function calculateAUC(t,y)
	   local n = length(t)
    if (length(y) != n)
        error("Vectors 't', 'y' must be of same length")
    end

	sum = 0.0
	for j in collect(2:n)
		curr_rect = (t[j]-t[j-1])*(y[j]+y[j-1])/2
		@show curr_rect
		sum = sum+curr_rect
	end
	return sum
end
