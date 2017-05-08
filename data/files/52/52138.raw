# Timelength: legth of repated resposne
# Idnum : number of subjects
# total number of response = Timelength*Idnum
# Groupnum : number of groups in response
#     total number of response/Groupnum must be multiple of tiemlength
# Beta: coefficients for linear model
# Sig10: covariance vector for random effect for linear coefficients
# Sig2 : standard deviation for randoem effect for group
# Esig:  standard deviation for error
# timegap: time covariates are constgructed as [0:(Timelength-1)]*timegap
type ReplinearOnegroup <: MixedData
	Timelength::Int64
	Idnum::Int64
	Groupnum::Int64
	Beta::Array{Float64,1} 
	Sig10::Array{Float64,1}
	Sig2::Float64
	Esig::Float64
  	re::Array{Any,1}
  	n::Int64
  	dat::DataFrame
end

function makedata2waylinear(Timelength::Int64,Idnum::Int64, Groupnum::Int64,
		Beta::Array{Float64,1} ,Sig10::Array{Float64,1},Sig2::Float64,Esig::Float64, timegap::Float64 )
	
	n=Timelength*Idnum
	grplength=convert(Int64,n/Groupnum)
	ggrp = [1:Groupnum]
	idd=[1:Idnum]
	ttime=[0:(Timelength-1)]*timegap
	id=pool(repeat(idd,inner=[Timelength]))
	time= repeat(ttime,outer=[Idnum])
	grp=pool(repeat(ggrp,inner=[grplength]))
	n=size(id,1)
	X = hcat(repeat([1.0],outer=[n]),time)
	sig1=reshape(Sig10,2,2)
	r1=vec(rand(MvNormal([0.0,0.0], sig1),Idnum))
	Z1=kron(speye(Idnum),sparse(hcat(ones(Timelength),[1:Timelength])))
	if Sig2 > 0.0
	  r2=rand(Normal(0.0,Sig2),Groupnum)
	  Z2 = kron(speye(Groupnum),sparse(ones(grplength)))
	  y = X*Beta+Z1*r1+Z2*r2+rand(Normal(0.0,Esig),n)
	  re={r1,r2}
    else
      y = X*Beta+Z1*r1+rand(Normal(0.0,Esig),n)
      re={r1}
    end  	
    
	dat=DataFrame(time=time,id=id,grp=grp,y=y)
	ReplinearOnegroup(Timelength,Idnum, Groupnum, Beta, 
		              Sig10, Sig2, Esig, re, n, dat)
end 

