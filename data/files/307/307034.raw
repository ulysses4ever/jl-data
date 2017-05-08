function sqrerror(edat,p::Vector{Float64},cvode_mem::Ptr{None},initp::Vector{Int64})

	p = abs(p)
	errorvalue::Float64 = 0.
	ysamp = Array(Float64,length(edat.obsv))
	yi::Vector{Float64} = copy(p[edat.initp])

	flag::Int64 = Sundials.CVodeReInit(cvode_mem, 0.0, Sundials.nvector(yi))
	flag = Sundials.CVodeSetUserData(cvode_mem, p)

	if edat.tsample[1] == 0.

		ysamp = edat.expdat[:,1] .- yi[edat.obsv]
		errorvalue += sum((ysamp).*(ysamp))

		for i = 2:edat.tmax				

			flag = Sundials.CVode(cvode_mem,edat.tsample[i], yi, [0.0], Sundials.CV_NORMAL)

			if flag != Sundials.CV_SUCCESS
				return 1e16
			end
			ysamp = edat.expdat[:,i] .- yi[edat.obsv]	
			errorvalue += sum((ysamp).*(ysamp))
		end
	else
		for i = 1:edat.tmax

			flag = Sundials.CVode(cvode_mem,edat.tsample[i], yi, [0.0], Sundials.CV_NORMAL)

			if flag != Sundials.CV_SUCCESS
				return 1e16			
			end
			ysamp = edat.expdat[:,i] .- yi[edat.obsv]
			errorvalue += sum((ysamp).*(ysamp))
		end
	end

	return errorvalue
end
	
function sqrerror(edat,p::Vector{Float64},cvode_mem::Ptr{None},initp::Vector{Float64})

	p = abs(p)
	errorvalue::Float64 = 0.
	ysamp = Array(Float64,length(edat.obsv))
	yi::Vector{Float64} = copy(edat.initp)

	flag::Int32 = Sundials.CVodeReInit(cvode_mem, 0.0, Sundials.nvector(yi))
	flag = Sundials.CVodeSetUserData(cvode_mem, p)
	
	for i = 2:edat.tmax

		flag = Sundials.CVode(cvode_mem,edat.tsample[i], yi, [0.0], Sundials.CV_NORMAL)

		if flag != Sundials.CV_SUCCESS
			return 1e16			
		end
		ysamp = edat.expdat[:,i] .- yi[edat.obsv]
		errorvalue += sum((ysamp).*(ysamp))
	end

	return errorvalue
end
