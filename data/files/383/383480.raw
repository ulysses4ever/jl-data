function storeData(time, fev, fes, fcs, fsp, fsh, fv, fac,historicaldata)
	row = [time, fev, fes, fcs, fsp, fsh, fv,fac]
	newdata = [historicaldata; transpose(row)]
	return newdata
end

function lookUpValue(historicaldata, item, desiredtime)
	data = historicaldata[2:end, :] # remove row of ones used to initiate the array
	#let's linearly interpolate to find items
	#@show desiredtime
	if(desiredtime <0)
		return .1
	elseif(abs(desiredtime) > data[end,1])
		println("got here")
		return .1
	end

	item = AbstractString(item)
	upperindex = findBounds(desiredtime,data)
	#@show desiredtime, data[end,1], upperindex
	lowerindex = upperindex -1
	#@show typeof(item)
	if(contains(item, AbstractString("fev")))
		return linInerp(data[lowerindex,2], data[upperindex,2], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fes")))
		return linInerp(data[lowerindex,3], data[upperindex,3], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fcs")))
		return linInerp(data[lowerindex,4], data[upperindex,4], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fsp")))
		return linInerp(data[lowerindex,5], data[upperindex,5], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fsh")))
		return linInerp(data[lowerindex,6], data[upperindex,6], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fv")))
		return linInerp(data[lowerindex,7], data[upperindex,7], data[lowerindex,1], data[upperindex,1], desiredtime)
	elseif(contains(item, AbstractString("fac")))
		return linInerp(data[lowerindex,8], data[upperindex,8], data[lowerindex,1], data[upperindex,1], desiredtime)
	else
		println("Fell through")
		@show item
		return .1
	end

	
end

function linInerp(lowerval, upperval, tstart, tend, tdesired)
	val = lowerval +(upperval-lowerval)/(tend-tstart)*(tdesired-tstart)
	return val
end

function findBounds(time, data)
	index = 0
	for j in collect(1:length(data-1))
		if(data[j,1]>=time)
			index = j
			break
		end
	end
	return index
end
