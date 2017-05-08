type RNormalPfModels 
	m::Int64  				# number of obligors
	d::Int64 				# dim of factors
	a::Array{Float64,2}     # factor coefficients for default
	b::Vector{Float64} 		# coefficient for random error
	sige::Float64            # sd of random error 
	invpn::Float64   		# function of n in threshold level for default
	invpa::Vector{Float64}   # constant in threshold level for default

	c::Vector{Float64}      # cost of m obligors
	ar::Array{Float64,2}    # factor coefficients for recovery
	br::Vector{Float64} 	# coefficient for random error for recovery
	sigr::Float64           # sd of random error (recovery)
	mur::Vector{Float64}    # mu for recovery distribution

end

function RNormalPfModels(	
	AA::Array{Float64,2},
	invpn::Float64,
	invpa::Vector{Float64},
	sigeta::Float64,           
	cost::Vector{Float64}, 
	AAR::Array{Float64,2}, 
	sigzeta::Float64, 
	mu::Vector{Float64})

	sum(invpa .<= 0.0) ==0 || error("threshold value must be positive")
	sum(cost .<= 0.0) ==0 || error("Cost must be positive")
    length(invpa)  == length(cost)==size(AA,1) || error("Dimension mismatch!")
    sigeta > 0.0 || error("Standard deviation must be positive")
    sigzeta > 0.0 || error("Standard deviation must be positive")
    m=length(invpa)
    d=size(AA,2)
    b=sqrt(ones(m) - sumsq(AA,2))[:,1]
    br=sqrt(ones(m) - sumsq(AAR,2))[:,1]
    RNormalPfModels(m,d,AA,b,sigeta,invpn,invpa,cost,
    	 AAR,br,sigzeta, mu )
end

function condefpro(mm::RNormalPfModels)
	n=mm.m
	l=mm.d
	z= rand(Normal(),l)
    pz=rand(n)
    
    for k=1:n
        pz[k] = 1.0-cdf(Normal(),(mm.invpa[k]*mm.invpn - dot( mm.a[k,:]',z)  )/mm.b[k])[1]
    end

    pc=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,rand(Normal(0.0,mm.sigr),n) ) )
 		
    return pz,pc
end

function importantsampling(mm::RNormalPfModels, upval::Float64)
 
 	n=mm.m

 	pz,pc=condefpro(mm::RNormalPfModels)

    rc=ones(n)
    subtract!(rc, pc)
    multiply!(rc,mm.c) 

	if dot(pz,rc) >= upval then
	   thetaopt = 0.0
	else    
	   thetaopt = findparatheta(pz,rc,upval)
	end 
	

    ptheta=zeros(n)
    for k=1:n
    	ptheta[k] = pz[k]*exp(thetaopt*rc[k])
        ptheta[k] = ptheta[k]/(1.0+pz[k]*(exp(thetaopt*rc[k])-1.0))
    
    end

    psit=0.0
    for k=1:n
    	psit+=log(1.0+pz[k]*(exp(thetaopt*rc[k]) -1))
    end
    	
    L = dot( (rand(n) .<= ptheta)*1.0, rc)
	
	ans=0.0
	if L > upval then
	    ans= exp(-thetaopt*L+psit)
	end	
	return ans
end

function ordinarysampling(mm::RNormalPfModels, upval::Float64)
 
 	pz,pc =condefpro(mm::RNormalPfModels)
	rc = mm.c .* (1.0 .- pc)

    L = dot( (rand(mm.m) .<= pz)*1.0, rc)
	
	ans=0.0
	if L > upval then
	    ans= 1.0
	end	
	return ans
end

function ordinarysampling2(mm::RNormalPfModels, upval::Float64)
    n=mm.m
    l=mm.d

    z= rand(Normal(),l)
    e=rand(Normal(0.0,mm.sige),n)
    w=rand(Normal(0.0,mm.sigr),n)
    
    #Rec = randomrecovery(mm,w,z,lam[2])
    Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) )


    C=ones(n)
    subtract!(C, Rec)
    multiply!(C,mm.c) 
    
    L = dot( (fma(mm.a*z , mm.b, e) .> mm.invpa*mm.invpn )*1.0, C)

    ans=0.0
    if L > upval then
       ans= 1.0
    end 

	return ans
end
