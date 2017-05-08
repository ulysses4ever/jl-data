function getM(polysys,d,x...)
dorig=getDorig(polysys)
neq= size(polysys,1)
n=size(polysys[1,2],2)

if isempty(x)
 # no optional argument, default Macaulay matrix
 shiftindices = cell(neq,1)
 for i=1:neq
  shiftindices[i]=[1:binomial(d-dorig[i]+n,n)]  
  println(shiftindices[i])
 end
 println(sum([length(shiftindices[i]) for i=1:neq]))
else
 # optional argument specifies up to which degree we already have the Macaulay matrix
 dmin=x[1]
 shiftindices = cell(neq,1)
 for i=1:neq
  shiftindices[i] = [binomial(dmin-dorig[i]+n,n)+1 : binomial(d-dorig[i] +n,n) ]
  println(shiftindices[i])
 end
println(sum([length(shiftindices[i]) for i=1:neq]))
end

end


function getMDim(polysys,d)
n=size(polysys[1,2],2)
q=binomial(d+n,n)
p=sum([binomial(d-max(sum(polysys[i,2],2))+n,n) for i=1:size(polysys,1)])
return p,q
end
