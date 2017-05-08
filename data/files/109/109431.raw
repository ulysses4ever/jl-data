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

M=sparse(vec(J),vec(I),vec(V),p,q)
end

function getMDim(polysys,d)
n=size(polysys[1,2],2)
q=binomial(d+n,n)
p=sum([binomial(d-maximum(sum(polysys[i,2],2))+n,n) for i=1:size(polysys,1)])
return p,q
end

function sparseN(polysys,d)
# return N,nM,tol
s=size(polysys,1)
n=size(polysys[1,2],2)

# normalize each coefficient vector to unit 1-norm such that the largest
for i=1:s
 polysys[i,1]=polysys[i,1]/norm(polysys[i,1],1);
end

# if M is sparse column compressed than accessing columns
# is faster than rows

initialM=getM(polysys,d); # non sparse version for test
p, q=size(initialM);

tol=max(p,q)*eps(sqrt(s));
nM=zeros(1,p);

nM[1]=sum(abs(initialM[1,:]))

# indices of nonzero coefficients
nindex=find(initialM[1,:]);
# indices of zero coefficients
zindex=setdiff(1:q,nindex);

# column indices
colI=zeros(Int,1,length(zindex)+2*(length(nindex)-1));
colI[1:length(zindex)]=1:length(zindex); # need to finish remaining indices

# row indices
rowI=zeros(Int,1,length(zindex)+2*(length(nindex)-1));
rowI[1:length(zindex)]=zindex;

# values
values=zeros(1,length(zindex)+2*(length(nindex)-1));
values[1:length(zindex)]=ones(1,length(zindex));

pivotI=indmax(abs(initialM[1,:]));
initialM[1,:]=initialM[1,:]/initialM[1,pivotI];
tempI=setdiff(nindex,pivotI);

# make the new M
# M=spalloc(p-1,q-1,nnz(initialM));  use spzeros instead
M=spzeros(p-1,q-1)
M[:,1:length(zindex)]=initialM[2:end,zindex];

# finish M and remaining indices/values for initialN
for j=1:length(tempI)
    # remaining columns of M
    M[:,length(zindex)+j]=initialM[1,tempI[j]]*initialM[2:end,pivotI]-initialM[1,pivotI]*initialM[2:end,tempI[j]];
    
    # remaining indices that determine new N
    colI[length(zindex)+2*(j-1)+1:length(zindex)+2*j]=(length(zindex)+j)*ones(1,2);
    rowI[length(zindex)+2*(j-1)+1:length(zindex)+2*j]=[pivotI tempI[j]];
    values[length(zindex)+2*(j-1)+1:length(zindex)+2*j]=[initialM[1,tempI[j]] -initialM[1,pivotI]];    
end

# now we can make the first N

#N=sparse(rowI,colI,values,q,q-1);
N=sparse(vec(rowI),vec(colI),vec(values),q,q-1);
(p,q)=size(M);

for i=1:p
    nM[i+1]=sum(abs(M[1,:]));
    if nM[i+1] > tol
        nindex=find(M[1,:]);
        zindex=setdiff(1:q,nindex);

        pivotI=indmax(abs(M[1,:]));
        tempI=setdiff(nindex,pivotI);
        M[1,:]=M[1,:]/M[1,pivotI];

        tempM=M;
        M=spzeros(p-1,q-1)
        M[:,1:length(zindex)]=tempM[2:end,zindex];
        
        tempN=N;
        # N=spalloc(size(N,1),q-1,nnz(tempN));
        N=spzeros(size(N,1),q-1)
		N[:,1:length(zindex)]=tempN[:,zindex];

        for j=1:length(tempI)
            # remaining columns of M            
            M[:,length(zindex)+j]=tempM[1,tempI[j]]*tempM[2:end,pivotI]-tempM[1,pivotI]*tempM[2:end,tempI[j]];
            
            N[:,length(zindex)+j]=tempM[1,tempI[j]]*tempN[:,pivotI]-tempM[1,pivotI]*tempN[:,tempI[j]];    
        end
        (p, q)=size(M);
    else
       # first row of M is numerically zero, remove it
       M=M[2:end,:];
       (p,q)=size(M); 
    end
end
return N,nM,tol
end
