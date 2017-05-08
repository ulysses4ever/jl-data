function getM(polysys,d,x...)

dorig=getDorig(polysys)
neq= size(polysys,1)
n=size(polysys[1,2],2)
ncoef=zeros(Int,1,neq)
nshifts=zeros(Int,1,neq)

if isempty(x)
 # no optional argument, default Macaulay matrix
 shiftindices = cell(neq,1)
 for i=1:neq
  ncoef[i] = length(polysys[i,1])
  shiftindices[i]=[1:binomial(d-dorig[i]+n,n)]  
  nshifts[i]=length(shiftindices[i])
  #println(shiftindices[i])
 end
 #println(sum(nshifts))
else
 # optional argument specifies up to which degree we already have the Macaulay matrix
 dmin=x[1]
 shiftindices = cell(neq,1)
 for i=1:neq
  ncoef[i] = length(polysys[i,1])
  shiftindices[i] = [binomial(dmin-dorig[i]+n,n)+1 : binomial(d-dorig[i] +n,n) ]
  nshifts[i]=length(shiftindices[i])
  #println(shiftindices[i])
 end
#println(sum(nshifts))
end

I=zeros(Int,1,sum([nshifts[i]*ncoef[i] for i=1:neq]))
J=zeros(Int,1,sum([nshifts[i]*ncoef[i] for i=1:neq]))
V=zeros(1,sum([nshifts[i]*ncoef[i] for i=1:neq]))

p=sum([length(shiftindices[i]) for i=1:neq])
q=binomial(d+n,n)

IVcounter=1
Jcounter=1
for i=1:neq 
 for j=1:length(shiftindices[i])
   # coefficients in V
   V[IVcounter:IVcounter+ncoef[i]-1]=polysys[i,1]   
   # row indices in I
   I[IVcounter:IVcounter+ncoef[i]-1]=feti(polysys[i,2]+ones(Int,ncoef[i],1)*fite(shiftindices[i][j],n))
   # column indices in J
   J[IVcounter:IVcounter+ncoef[i]-1]=Jcounter*ones(Int,1,ncoef[i])
   Jcounter+=1
   IVcounter+=ncoef[i]
 end
end 

M=sparse(vec(I),vec(J),vec(V),q,p)
end


function getMDim(polysys,d)
n=size(polysys[1,2],2)
q=binomial(d+n,n)
p=sum([binomial(d-max(sum(polysys[i,2],2))+n,n) for i=1:size(polysys,1)])
return q,p
end
