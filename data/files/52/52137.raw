# timelength: legth of repated resposne
# idnum : number of subjects
# total number of response = timelength*idnum
# groupnum : number of groups in response
#     total number of response/groupnum must be multiple of tiemlength
# beta: coefficients for linear model
# sig10: covariance vector for random effect for linear coefficients
# sig2 : standard deviation for randoem effect for group
# esig:  standard deviation for error

function makedata2waylinear(timelength::Int64,idnum::Int64, groupnum::Int64,
		beta::Array{Float64,1} ,sig10::Array{Float64,1},sig2::Float64,esig::Float64 )
	
	n=timelength*idnum
	grplength=convert(Int64,n/groupnum)
	ggrp = [1:groupnum]
	idd=[1:idnum]
	ttime=[1:timelength]
	id=pool(repeat(idd,inner=[timelength]))
	time= repeat(ttime,outer=[idnum])
	grp=pool(repeat(ggrp,inner=[grplength]))
	n=size(id,1)
	X = hcat(repeat([1.0],outer=[n]),time)
	sig1=reshape(sig10,2,2)
	r1=vec(rand(MvNormal([0.0,0.0], sig1),idnum))
	Z1=kron(speye(idnum),sparse(hcat(ones(timelength),[1:timelength])))
	if sig2 > 0.0
	  r2=rand(Normal(0.0,sig2),groupnum)
	  Z2 = kron(speye(groupnum),sparse(ones(grplength)))
	  y = X*beta+Z1*r1+Z2*r2+rand(Normal(0.0,esig),n)
    else
      y = X*beta+Z1*r1+rand(Normal(0.0,esig),n)
    end  	
	DataFrame(time=time,id=id,grp=grp,y=y)
end 

