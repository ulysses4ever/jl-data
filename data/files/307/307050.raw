function setCvodeMem(initp::Vector{Float64}, steptol::Float64, abstol::Vector{Float64})

	nOdes = length(initp);
	cvodemem = Sundials.CVodeCreate(Sundials.CV_BDF, Sundials.CV_NEWTON);

	flag = Sundials.CVodeInit(cvodemem, cfunction(evaluate, Int32, (Sundials.realtype, Sundials.N_Vector, Sundials.N_Vector, Vector{Float64})), 0.0, Sundials.nvector(initp));
	flag = Sundials.CVodeSVtolerances(cvodemem, steptol, abstol);
	flag = Sundials.CVDense(cvodemem, nOdes);
	flag = Sundials.CVodeSetMaxNumSteps(cvodemem,1e12)
	flag = Sundials.CVodeSetErrFile(cvodemem,false)
	return(cvodemem)
end

#----------------Parameter search main loop--------------------

function paramSearch(opt,edat,P::Vector{Float64}) 
	
	if isa(edat.initp,Vector{Int64})
		cvodemem = setCvodeMem(P[edat.initp],opt.steptol,opt.abstol)
	else
		cvodemem = setCvodeMem(edat.initp,opt.steptol,opt.abstol)
	end

	newfeval = feval = sqrerror(edat,P,cvodemem,edat.initp)
	
	if(feval > 1e15)
		return ([abs(P),feval])
	end

	#---initialize values---

	tr = opt.inittr
	const pnum = length(P)
	next = true
	count = 0;
	hinv = eye(Float64,pnum,pnum)
	h = eye(Float64,pnum,pnum)
    
	#---Finite differences based on current curvature i.e. more curatrue smaller differnce---

	dif = ones(Float64,pnum)

	#---Initialise Jacobian and Hessian. Note: Hessian is a diagonal matrix for better scaling i.e. complexity is O(n)---

	(h,g) = calcHnJ(feval,edat,P,dif,cvodemem)
	newg = g

	#---Invert Hesain pseudo inverse is more robust---

	try
		hinv = pinv(h)
	catch
		return ([abs(P),feval])
	end

    	hvec = h*ones(Float64,pnum,1)

	#---Return if undefined gradient: improves robusteness of algorithm---

	if sum(isnan(g))>0
		return([abs(P),feval])
	end

	#---Main Loop take best step out of steepest descent and newton if +def Hessian or direction of negative curvature otherwise ---

	while next

		dif = ones(Float64,pnum,1)./(1e4.*(1.+abs(hvec)))
		dif = dif[:,1]

		#---Calculate Cauchy point set on TR boundary if outside TR---
	
		tau = transpose(g)*h*g

		if isnan(tau)[1]
			return([abs(P),feval])
		elseif tau[1] <= 0
			tau =1.
		else
			tau = (norm(g)^3)./(tr*tau)
			tau = tau[1]
		end

		pS = -g*tr*tau./norm(g)

		if norm(pS)>tr
			pS = tr*pS/norm(pS)
		end

		#---Evaluate f at Cauchy point---

		pSeval::Float64 = sqrerror(edat,P.+pS[:,1],cvodemem,edat.initp)

		#---Test if Hessian is +def calculate newton point, if outside TR implement dogleg step else use newton point---
	
		if minimum(hvec) > 0

			pN::Matrix{Float64}
			pNeval::Float64

			pN = -hinv*g

			if norm(pN) > tr && norm(pS)<tr-0.1
				dN = pN.-pS
				b = transpose(dN)*pS
				DL = pS.+ dN.*(b.+0.5*sqrt((b.^2).-4*(norm(pS)^2-tr^2)))./norm(dN)      
				pN = pS .+ DL
				pNR = pN .+ DL .- 2.*(transpose(DL)*(pN./tr))
	
				pNeval = sqrerror(edat,P+pN[:,1],cvodemem,edat.initp)
				pNReval::Float64 = sqrerror(edat,P.+pNR[:,1],cvodemem,edat.initp)	
				
				if pNReval < newfeval
					d = pNR[:,1]
					newfeval = pNReval
				end
			else				
				if norm(pN)>tr
                    			pN = tr*pN./norm(pN)
               			end
				pNeval = sqrerror(edat,P.+pN[:,1],cvodemem,edat.initp)
			end

			if pNeval < newfeval
				d = pN[:,1]
				newfeval = pNeval
			end
		else
			#---Direction of negative curvature---

			pNC =  - tr*sign((hvec.<0).*g)
			pNCeval = sqrerror(edat,P.+pNC[:,1],cvodemem,edat.initp)

			if pNCeval < newfeval
				d = pNC[:,1]
				newfeval = pNCeval
			end
		end

		if pSeval < newfeval
			d = pS[:,1]
			newfeval = pSeval
		end

		if newfeval < feval
			
			#---Caculate reduction in f and predicted reduction in f---

			rdc = feval-newfeval
			fevalpred = transpose(d)*g + 0.5*transpose(d)*h*d
			fevalpred = -fevalpred[1]
			
			#---Exit if reduction is below Tol---

			if abs(fevalpred) < feval*opt.tolred
				next = false
			end

			#---If the model is a good or better than predicted expand TR else if worse reduce TR---

			if rdc > (fevalpred - abs(fevalpred)*0.1)
				tr = tr*2
			elseif rdc < (fevalpred - abs(fevalpred)*0.2)
				tr = tr*0.8
			end
			
			#---Update position, Jacobian then Hessian---

			P = P .+ d
			feval = newfeval
			newg_temp = calcJ(feval,edat,P,dif,cvodemem)

			if !(sum(isnan(newg_temp))>0)
				newg = newg_temp
			end

			gdif = newg -g

			#BFGS
			#rho = 1./transpose(gdif)*d
			#hinv = (eye(pnum)-rho.*d*transpose(gdif))*hinv*(eye(2)-rho.*gdif*transpose(d)) + rho.*d*transpose(gdif)

			#DFP
			#hinv = hinv .+ (d*transpose(d))./(transpose(gdif)*d) - (hinv*gdif*transpose(gdif)*hinv)./(transpose(gdif)*hinv*gdif)

			#SR1
			rho = d-hinv*gdif
			den = transpose(rho)*gdif

			if !(den[1] < 1e-8)
				hinv = hinv.+ ((rho)*transpose(rho))./(transpose(rho)*gdif)
			end
			
			try
				hinv = pinv(h)
			catch
				return ([abs(P),feval])
			end

			hvec = h*ones(Float64,pnum,1)

			g = newg
			feval = newfeval
		else
			#---Descent has stalled re-evaluate Hessian---

			(h,newg_temp) = calcHnJ(feval,edat,P,dif,cvodemem)
			
			#---Terminate if gradient has undefined values; improves robustness---

			if !(sum(isnan(newg_temp))>0)
				g = newg_temp
			end

			if sum(isnan(h))>0
				return ([abs(P),feval])
			end

			hvec = h*ones(Float64,pnum,1)

			try
				hinv = pinv(h)
			catch
				return ([abs(P),feval])
			end

			tr = tr*0.5			
		end

		if tr < opt.toltr || count>opt.maxiter
				next = false
		end

		count+=1;		
	end

	return([abs(P),feval])
end
