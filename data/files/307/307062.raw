#---Latin Hypercube Design for initial sample---

function designLHC(n::Int64,m::Int64,space::Int64)

	nvec = round(linspace(1,n,n))
	nvec = nvec
	lhc = Array(Float64,m,n)

	for i = 1:m
	    lhc[i,:] = shuffle(nvec)
	end

	lhc = lhc .- drand(m,n)
	lhc= lhc./n
	
	lhc = 10.^(space*lhc.-(space/2))

	return lhc
end

#---Latin Hypercube Design for space reductions---

function designLHC(n::Int64,best_param::Matrix{Float64})
	
	(null,m) = size(best_param)
	lhc = Array(Float64,m,n)

	for i = 1:m
		min_bound = log10(minimum(best_param[:,i])-abs(0.2*minimum(best_param[:,i])))
		max_bound = log10(maximum(best_param[:,i])+abs(0.2*maximum(best_param[:,i])))
		nvec = linspace(min_bound,max_bound,n).-0.5 .+ drand(n)
		nvec = 10.^shuffle(nvec)
		lhc[i,:] = nvec
	end
	
	return(lhc)
end

#---Latin Hypercube Design with initial bounds---

function designLHC(n::Int64,m::Int64,pbounds::Matrix{Float64})
	
	lhc = Array(Float64,m,n)

	for i = 1:m
		min_bound = log10(minimum(pbounds[:,i]))
		max_bound = log10(maximum(pbounds[:,i]))
		nvec = linspace(min_bound,max_bound,n).-0.5 .+ drand(n)
		nvec = 10.^shuffle(nvec)
		lhc[i,:] = nvec
	end
	
	return(lhc)
end
