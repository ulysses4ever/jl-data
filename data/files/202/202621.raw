function pauc(idv, dv, range)
	idvfirst = range[1]
	idvlast = range[2]
	dv = dv[dv .>= idvfirst]
	idv = idv[idv .>= idvfirst]
	lengthidv = length(idv[idv .<= idvlast])
	paucvalue = zeros(0)
	for i = 1:(lengthidv - 1)
		push!(paucvalue, (dv[i] + dv[i+1])*(idv[i + 1]-idv[i])/2)
	end
	return sum(paucvalue)
end
