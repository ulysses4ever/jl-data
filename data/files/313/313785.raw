type RTPfModels 
	m::Int64  				# number of obligors
	d::Int64 				# dim of factors
	v::Float64              # degree of freedom for T (Gamma)
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

	tau::Float64 			# Kendall's tau rank correlation
end
 
function RTPfModels(
	AA::Array{Float64,2},
	invpn::Float64,
	invpa::Vector{Float64},
	sigeta::Float64,           
	cost::Vector{Float64}, 
	AAR::Array{Float64,2}, 
	sigzeta::Float64,
	mu::Vector{Float64}, 
	df::Float64,  
	tau::Float64)

	df > 0.0 || error("Degree of freedom must be positive")
	sum(invpa .<= 0.0) ==0 || error("threshold value must be positive")
	sum(cost .<= 0.0) ==0 || error("Cost must be positive")
    length(invpa) ==  length(cost)==size(AA,1) || error("Dimension mismatch!")
    sigeta > 0.0 || error("Standard deviation must be positive")
    sigzeta > 0.0 || error("Standard deviation must be positive")
    tau >0.0 && tau < 1.0 || error("Correlation must be between 0 and 1")
    m=length(invpa)
    d=size(AA,2)
    b=sqrt(ones(m) - sumsq(AA,2))[:,1]
    br=sqrt(ones(m) - sumsq(AAR,2))[:,1]
    RTPfModels(m,d,df,AA,b,sigeta,invpn,invpa,cost,
    	 AAR,br,sigzeta, mu, tau )
end

# generating bivariate gamma from Clayton copula with Kendall's tau 
function claytoncopula(mm::RTPfModels)
	tt = mm.tau
	α = 2.0*tt/(1-tt) 
	v = rand(Gamma(1.0/α,1.0),1)[1]
	r = rand(2)
	r[1] = (1-log(r[1])/v)^(-1.0/α)
	r[2] = (1-log(r[2])/v)^(-1.0/α)
	r[1] = quantile(Gamma(mm.v/2.0,2.0/mm.v),r[1])
	r[2] = quantile(Gamma(mm.v/2.0,2.0/mm.v),r[2])
    return r
end

function claytoncopula(tau::Float64, alpha::Float64, beta::Float64)
	tt = tau
	α = 2.0*tt/(1-tt) 
	v = rand(Gamma(1.0/α,1.0),1)[1]
	r = rand(2)
	r[1] = (1-log(r[1])/v)^(-1.0/α)
	r[2] = (1-log(r[2])/v)^(-1.0/α)
	r[1] = quantile(Gamma(alpha,1.0/beta),r[1])
	r[2] = quantile(Gamma(alpha,1.0/beta),r[2])
    return r
end

function conddistgam(mm::RTPfModels, xx::Float64, lambda::Float64 )
    α = 2.0*mm.tau/(1.0-mm.tau)
    zz = (cdf(Gamma(mm.v/2.0,2.0/mm.v),lambda))
    ww = (cdf(Gamma(mm.v/2.0,2.0/mm.v),max(0.0,xx)^2))
     
    val = (ww^(1.0+α))/ ((zz^α+ww^α-ww^α*zz^α)^(1.0+1.0/α))
    return val
end
# clacluate conditional default probability 
# when normal variable Z and Gamma variable lambda are gievn
function condefpro(mm::RTPfModels, z::Vector{Float64}, lambda::Float64)
	n=mm.m
	l=mm.d
	w= sqrt(lambda) 
    pz=zeros(n)
    for k=1:n
        pz[k] = 1.0-cdf(Normal(),(w*mm.invpa[k]*mm.invpn - dot( mm.a[k,:]',z)  )/mm.b[k])[1]
    end
    return pz
end


# generate random recovery rates
function randomrecovery(mm::RTPfModels, e::Vector{Float64}, z::Vector{Float64}, lambda::Float64)
	
	n=mm.m
	l=mm.d

	w= sqrt(lambda) 
	rec=zeros(n)

    rec = mm.mur - fma(mm.ar*z , mm.br ,e) / w

    return cdf(Normal(),rec) 
 end

 # Find normal parameters for CondMC-CE in Chan and Kroese(2010)
function findparais(mm::RTPfModels, upval::Float64)

    n=mm.m 
	l=mm.d

	l == 1 || error("Conditional MC with Cross Entropy works only one dimensional case!")

	muis = zeros(3)
	varis = zeros(3)
    
    sumS =0.0

	B3=5000

    S=rand(B3)
    L=rand(B3) 

    for k=1:B3

		z= rand(Normal(),1)

		#lam = claytoncopula(mm)
		lam = rand(Gamma(mm.v/2.0,2.0/mm.v),1)[1]
		L[k] = lam
		w=rand(Normal(0.0,mm.sigr),n)
	    #Rec = randomrecovery(mm,w,z,lam)
 		Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) / sqrt(lam) )
 		
        e = rand(Normal(0.0,mm.sige),n)  
        R = fma(mm.a *z , mm.b ,e) 
        divide!(R, mm.invpa)
     
    	q=sortperm(R)
    	R=R[q]
    	C=ones(n)
        subtract!(C, Rec)
        multiply!(C,mm.c) 
    	C=C[q]

    	xx= findminR(upval, R, C)/mm.invpn   
	
		S[k]=conddistgam(mm, xx, lam )

	    sumS += S[k]

	    muis[1] +=S[k]*z[1]
	    muis[2] +=S[k]*sum(e)
	    muis[3] +=S[k]*sum(w)

	    varis[1] +=S[k]*z[1]^2
	    varis[2] +=S[k]*sumsq(e)
	    varis[3] +=S[k]*sumsq(w)


	end
	
	
	muis[1] = muis[1]/sumS
	muis[2] = muis[2]/(n*sumS)
	muis[3] = muis[3]/(n*sumS)

    varis[1]=varis[1]/sumS -muis[1]^2
    varis[2]=varis[2]/(n*sumS) -muis[2]^2
	varis[3]=varis[3]/(n*sumS) -muis[3]^2

    return muis, varis, findparagamis(L,S)

end

function findparagamis(L::Vector{Float64},S::Vector{Float64})

	function makeobj(y::Vector{Float64},s::Vector{Float64})
  
  		function myfun(x::Vector{Float64},g::Vector{Float64})
    	n=length(y)
    
    	ans=0.0

    	for i = 1:n
      		ans += s[i]*logpdf(Gamma(x[1],1.0/x[2]),y[i])
    	end
  
    	return ans
  		
  		end

  	return myfun
	end

	opt = NLopt.Opt(:LN_BOBYQA, 2)

	#opt = NLopt.Opt(:LN_NELDERMEAD, 1)

	NLopt.ftol_rel!(opt, 1e-12)   # relative criterion on deviance
	NLopt.ftol_abs!(opt, 1e-8)    # absolute criterion on deviance
	NLopt.xtol_abs!(opt, 1e-10)   # criterion on parameter value changes
	NLopt.lower_bounds!(opt, [eps(), eps()])
    

	NLopt.max_objective!(opt, makeobj(L,S))
	fmin, thetaopt, ret = NLopt.optimize(opt, [1.0, 1.0])
   
    return thetaopt
end

# CondMC in Chan and Kroese(2010)
function condmc(mm::RTPfModels, upval::Float64)
 
    n=mm.m
    l=mm.d

    z= rand(Normal(),l)
    w=rand(Normal(0.0,mm.sigr),n)
    #lam = claytoncopula(mm)
    lam = rand(Gamma(mm.v/2.0,2.0/mm.v),1)[1]

    #Rec = randomrecovery(mm,w,z,lam[2])
    Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) / sqrt(lam) )
    
    R=fma(mm.a*z , mm.b , rand(Normal(0.0,mm.sige),n))
    divide!(R,mm.invpa )

    q=sortperm(R)
    R=R[q]
 
    C=ones(n)
    subtract!(C, Rec)
    multiply!(C,mm.c) 
    C=C[q]

    xx= findminR(upval, R, C)/mm.invpn    
    
    val = conddistgam(mm, xx, lam )

    return val
end

# CondMC-CE in Chan and Kroese(2010)
# only work for the case: dim of Z is 1 (mm.d=1)
function condmcce(mm::RTPfModels, upval::Float64, muis::Vector{Float64}, varis::Vector{Float64}, gamis::Vector{Float64} )
 
    n=mm.m
    l=mm.d

    l == 1 || error("Conditional MC with Cross Entropy works only one dimensional case!")

    z = rand(Normal(muis[1],sqrt(varis[1])),l)
    e = rand(Normal(muis[2],sqrt(varis[2])),n)
    w = rand(Normal(muis[3],sqrt(varis[3])),n)

    #lam = claytoncopula(mm.tau, gamis[1],gamis[2])
    lam = rand(Gamma(gamis[1],1.0/gamis[2]),1)[1]

    #Rec = randomrecovery(mm,w,z,lam[2])
    Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) / sqrt(lam) )
    
    R=fma(mm.a*z , mm.b , e)
    divide!(R,mm.invpa )


    q=sortperm(R)
    R=R[q]
    C=ones(n)
    subtract!(C, Rec)
    multiply!(C,mm.c) 
    C=C[q]

    xx= findminR(upval, R, C)/mm.invpn   
     
    val = conddistgam(mm, xx, lam )

    s1 = sum(logpdf(Normal(0.0,1.0),z) - logpdf(Normal(muis[1],sqrt(varis[1])),z) ) 
    s2 = sum(logpdf(Gamma(mm.v/2.0,2.0/mm.v),lam) - logpdf(Gamma(gamis[1],1.0/gamis[2]),lam))
    t1 = sum(logpdf(Normal(0.0,mm.sige),e) ) 
    t2 = sum(logpdf(Normal(muis[2],sqrt(varis[2])),e))
    t3 = sum(logpdf(Normal(0.0,mm.sigr),w))
    t4 = sum(logpdf(Normal(muis[3],sqrt(varis[3])),w))
          

    val=val*exp(s1+s2+t1+t3-t2-t4)
    
	return val[1]    
end


# Conditional Naive Simulation
function ordinarysampling(mm::RTPfModels, upval::Float64)
	n=mm.m
	l=mm.d

   

	lam = claytoncopula(mm)
	z= rand(Normal(),l)
	w=rand(Normal(0.0,mm.sigr),n)
	pz=condefpro(mm,z,lam[1])
	#Rec = randomrecovery(mm,w,z,lam[2])

	Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) / sqrt(lam[2]) )

	C=ones(n)
	subtract!(C, Rec)
	multiply!(C,mm.c) 
	L = dot( (rand(mm.m) .<= pz)*1.0, C)
	ans=0.0
	if L > upval then
		ans= 1.0
	end

	return ans

end

# Conditional Naive Simulation
function ordinarysampling2(mm::RTPfModels, upval::Float64)
    n=mm.m
    l=mm.d


    lam = claytoncopula(mm)
    z= rand(Normal(),l)
    e=rand(Normal(0.0,mm.sige),n)
    w=rand(Normal(0.0,mm.sigr),n)
    
    #Rec = randomrecovery(mm,w,z,lam[2])
    Rec=cdf(Normal(), mm.mur - fma(mm.ar*z , mm.br ,w) / sqrt(lam[2]) )


    C=ones(n)
    subtract!(C, Rec)
    multiply!(C,mm.c) 
    
    L = dot( (fma(mm.a*z , mm.b, e)/sqrt(lam[1]) .> mm.invpa*mm.invpn )*1.0, C)

    ans=0.0
    if L > upval then
       ans= 1.0
    end 

	return ans
end



