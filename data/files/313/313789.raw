type TPfModels 
	m::Int64  				# number of obligors
	d::Int64 				# dim of factors
	v::Float64              # degree of freedom for T (Gamma)
	a::Array{Float64,2}     # factor coefficients 
	b::Vector{Float64} 		# coefficient for random error
	sige::Float64            # sd of random error 
	invpn::Float64   		# function of n in threshold level for default
	invpa::Vector{Float64}  # constants in threshold level for default

	c::Vector{Float64}      # cost of m obligors
end

 
function TPfModels(
	AA::Array{Float64,2},
	invpn::Float64,
	invpa::Vector{Float64},
	sigeta::Float64,
	cost::Vector{Float64},
	df::Float64)
	
	df > 0.0 || error("Degree of freedom must be positive")
	sum(invpa .<= 0.0) ==0 || error("threshold value must be positive")
	sum(cost .<= 0.0) ==0 || error("Cost must be positive")
    length(invpa)== length(cost)==size(AA,1) || error("Dimension mismatch!")
    sigeta > 0.0 || error("Standard deviation must be positive")
    m=length(invpa)
    d=size(AA,2)
    b=sqrt(ones(m) - sumsq(AA,2))[:,1]
    TPfModels(m,d,df,AA,b,sigeta,invpn,invpa,cost)
end

# clacluate conditional default probability 
# when normal variable Z and Gamma variable lambda are gievn
function condefpro(mm::TPfModels, z::Vector{Float64}, lambda::Float64)
	n=mm.m
	l=mm.d
	
	w= sqrt(lambda) 
    pz=zeros(n)

    for k=1:n
    	vv=(w*mm.invpa[k]*mm.invpn- dot( mm.a[k,:]',z))/mm.b[k]
        pz[k] =1.0- cdf(Normal(),vv )[1]
    end         
    return pz
end

# Find R_{(k)} of order statistics in Chan and Kroese(2010, page 363)
function findminR(upval::Float64,R::Vector{Float64},C::Vector{Float64})

	n=length(R)
    tsum=0
    k=n
    while tsum <= upval && k>1 
       tsum += C[k]
       k=k-1
	end

	if k==1 then
	  x=ifelse(tsum+C[1] <= upval , 0.0, R[1])      
    else
      x=R[k+1]
    end
    return x
end

# Find normal parameters for CondMC-CE in Chan and Kroese(2010)
function findparais(mm::TPfModels, upval::Float64)

    n=mm.m
	l=mm.d

l == 1 || error("Conditional MC with Cross Entropy works only one dimensional case!")

	muis = zeros(2)
	varis = zeros(2)

	sumS =0.0
	
	B3=5000


    for k=1:B3

		z= rand(Normal(),1)
        e = rand(Normal(0.0,mm.sige),n)  
        R = fma(mm.a *z , mm.b ,e) 
        divide!(R, mm.invpa)
     
    	q=sortperm(R)
    	R=R[q]
    	C=mm.c[q]

    	xx= findminR(upval, R, C)/mm.invpn   
	
		S=cdf(Gamma(mm.v/2.0,2.0/mm.v),max(0.0,xx)^2)

	    sumS += S

	    muis[1] +=S*z[1]
	    muis[2] +=S*sum(e)

	    varis[1] +=S*z[1]^2
	    varis[2] +=S*sumsq(e)

	end
	
	muis[1] = muis[1]/sumS
	muis[2] = muis[2]/(n*sumS)

    varis[1]=varis[1]/sumS -muis[1]^2
    varis[2]=varis[2]/(n*sumS) -muis[2]^2

    return muis, varis

end

# CondMC in Chan and Kroese(2010)
function condmc(mm::TPfModels, upval::Float64)
 
    n=mm.m
	l=mm.d
	z= rand(Normal(),l)

    R=fma(mm.a*z , mm.b , rand(Normal(0.0,mm.sige),n))
    divide!(R,mm.invpa )


	q=sortperm(R)
    R=R[q]
    C=mm.c[q]
    xx= findminR(upval, R, C)/mm.invpn    
	
	val = cdf(Gamma(mm.v/2.0,2.0/mm.v),max(0.0,xx)^2)

end

# CondMC-CE in Chan and Kroese(2010)
# only work for the case: dim of Z is 1 (mm.d=1)
function condmcce(mm::TPfModels, upval::Float64, muis::Vector{Float64}, varis::Vector{Float64})
 
    n=mm.m
	l=mm.d

	z = rand(Normal(muis[1],sqrt(varis[1])),l)
	e = rand(Normal(muis[2],sqrt(varis[2])),n)

    R=fma(mm.a*z , mm.b , e)
    divide!(R,mm.invpa )


    q=sortperm(R)
    R=R[q]
    C=mm.c[q]

	xx= findminR(upval, R, C) /mm.invpn  
	
	val = cdf(Gamma(mm.v/2.0,2.0/mm.v),max(0.0,xx)^2)

	s1 = sum(logpdf(Normal(0.0,1.0),z) - logpdf(Normal(muis[1],sqrt(varis[1])),z) ) 
    t1 = sum(logpdf(Normal(0.0,mm.sige),e) ) 
    t2 = sum(logpdf(Normal(muis[2],sqrt(varis[2])),e))
    

	val=val*exp(s1+t1-t2)
    
	return val[1]   
end

# Conditional Naive Simulation
function ordinarysampling(mm::TPfModels, upval::Float64)
 
    n=mm.m
	l=mm.d

    lam = rand(Gamma(mm.v/2.0,2.0/mm.v),1)[1]
	z= rand(Normal(),l)

 	pz=condefpro(mm,z,lam)
	
    L = dot( (rand(mm.m) .<= pz)*1.0, mm.c)
	
	ans=0.0
	if L > upval then
	    ans= 1.0
	end	
	return(ans)
end

function ordinarysampling2(mm::TPfModels, upval::Float64)
    n=mm.m
    l=mm.d

    lam = rand(Gamma(mm.v/2.0,2.0/mm.v),1)[1]
    z= rand(Normal(),l)
    e=rand(Normal(0.0,mm.sige),n)
   
    C=mm.c
    
    L = dot( (fma(mm.a*z , mm.b, e)/sqrt(lam) .> mm.invpa*mm.invpn )*1.0, C)

    ans=0.0
    if L > upval then
       ans= 1.0
    end 

	return ans
end
