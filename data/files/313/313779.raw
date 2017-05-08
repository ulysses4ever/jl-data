type NormalPfModels 
	m::Int64  				# number of obligors
	d::Int64 				# dim of factors
	a::Array{Float64,2}     # factor coefficients for default
	b::Vector{Float64} 		# coefficient for random error
	sige::Float64            # sd of random error 
	invpn::Float64   		# function of n in threshold level for default
	invpa::Vector{Float64}   # constant in threshold level for default

	c::Vector{Float64}      # cost of m obligors
end

function NormalPfModels(
	AA::Array{Float64,2},
	invpn::Float64,
	invpa::Vector{Float64},
	sigeta::Float64,           
	cost::Vector{Float64})

	sum(invpa .<= 0.0) ==0 || error("threshold value must be positive")
	sum(cost .<= 0.0) ==0 || error("Cost must be positive")
    length(invpa)  == length(cost)==size(AA,1) || error("Dimension mismatch!")
    sigeta > 0.0 || error("Standard deviation must be positive")
    m=length(invpa)
    d=size(AA,2)
    b=sqrt(ones(m) - sumsq(AA,2))[:,1]

    NormalPfModels(m,d,AA,b,sigeta,invpn,invpa,cost)
end

function condefpro(mm::NormalPfModels)
	n=mm.m
	l=mm.d
	z= rand(Normal(),l)
    pz=rand(n)
    for k=1:n
           pz[k] = 1.0-cdf(Normal(),(mm.invpa[k]*mm.invpn - dot( mm.a[k,:]',z)  )/mm.b[k])[1]
    end
    return pz
end


function findparatheta(p::Vector{Float64},c::Vector{Float64},upval::Float64)

	function makeobj(x1::Vector{Float64},x2::Vector{Float64},x3::Float64)
  
  		function targetz(x::Vector{Float64},g::Vector{Float64})
    	  d1=length(x1)
    	  ans=0.0
    	  for k=1:d1
    	    # ans+=log(1.0+x1[k]*(exp(*mm.c[k]) -1.0))
    	    ans+=log(1.0+x1[k]*(exp(x[1]*x2[k]) -1.0))
    	  end
    	  return x[1]*x3-ans
    	end
	
  		return targetz
	
    end

	opt = NLopt.Opt(:LN_BOBYQA, 1)

	#opt = NLopt.Opt(:LN_NELDERMEAD, 1)

	NLopt.ftol_rel!(opt, 1e-12)   # relative criterion on deviance
	NLopt.ftol_abs!(opt, 1e-8)    # absolute criterion on deviance
	NLopt.xtol_abs!(opt, 1e-10)   # criterion on parameter value changes
	NLopt.lower_bounds!(opt, [0.0])
    

	NLopt.max_objective!(opt, makeobj(p,c,upval))
	fmin, thetaopt, ret = NLopt.optimize(opt, [1.0])
   
  
  	return thetaopt[1]
end


function importantsampling(mm::NormalPfModels, upval::Float64)
 

	n=mm.m

 	pz=condefpro(mm::NormalPfModels)


	if dot(pz,mm.c) >= upval then
	   thetaopt = 0.0
	else    
	   thetaopt = findparatheta(pz,mm.c,upval)
	end 
	
    ptheta=rand(n)
    for k=1:n
        ptheta[k] = pz[k]*exp(thetaopt*mm.c[k])
        ptheta[k] = ptheta[k]/(1.0+pz[k]*(exp(thetaopt*mm.c[k])-1.0))
    end

    psit=0.0
    for k=1:n
       	psit+=log(1.0+pz[k]*(exp(thetaopt*mm.c[k]) -1))
    end
    	
    L = dot( (rand(n) .<= ptheta)*1.0, mm.c)
	
	ans=0.0
	if L > upval then
	    ans= exp(-thetaopt*L+psit)
	end	
	return ans
end

function ordinarysampling(mm::NormalPfModels, upval::Float64)
 
 	pz=condefpro(mm::NormalPfModels)
	
    L = dot( (rand(mm.m) .<= pz)*1.0, mm.c)
	
	ans=0.0
	if L > upval then
	    ans= 1.0
	end	
	return ans
end

function ordinarysampling2(mm::NormalPfModels, upval::Float64)
    n=mm.m
    l=mm.d

    z= rand(Normal(),l)
    e=rand(Normal(0.0,mm.sige),n)
    
    L = dot( (fma(mm.a*z , mm.b, e) .> mm.invpa*mm.invpn )*1.0, mm.c)

    ans=0.0
    if L > upval then
       ans= 1.0
    end 

	return ans
end


