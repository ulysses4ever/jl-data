function solveAndPlotSundials(pdat,p)
	p = abs(p)

	if isa(pdat.initp,Vector{Float64})
		yi = copy(pdat.initp)
	else
		yi = copy(p[pdat.initp])
	end

	nOdes = length(yi);
	cvode_mem = Sundials.CVodeCreate(Sundials.CV_BDF, Sundials.CV_NEWTON);
	flag = Sundials.CVodeInit(cvode_mem, cfunction(evaluate, Int32, (Sundials.realtype, Sundials.N_Vector, Sundials.N_Vector, Vector{Float64})), 0.0, Sundials.nvector(yi));
	flag = Sundials.CVodeSVtolerances(cvode_mem, pdat.steptol, pdat.abstol);
	flag = Sundials.CVodeSetMaxNumSteps(cvode_mem,1e12)
	flag = Sundials.CVodeSetErrFile(cvode_mem,false)
	flag = Sundials.CVDense(cvode_mem, nOdes);
	flag = Sundials.CVodeSetUserData(cvode_mem, p);
	
	max = length(pdat.tsample)

	# Solve ODE system numerically
	y = Array(Float64, max, length(pdat.obsv));

	y[1,:] = yi[pdat.obsv]

	for i = 2:max

		flag = Sundials.CVode(cvode_mem,pdat.tsample[i], yi, [0.0], Sundials.CV_NORMAL)

		if flag != Sundials.CV_SUCCESS
			println("SUNDIALS_ERROR: CVODE failed with flag = ", flag)
			break
		end
		y[i,:] = yi[pdat.obsv]
	end

	return y
end
