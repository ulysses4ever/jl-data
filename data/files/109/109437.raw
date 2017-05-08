function pfeti(exponent)
n=length(exponent); 
index = @parallel (+) for i=1:n
    sum(exponent[i:n])>0 ? binomial(n-i+sum(exponent[i:n]),n-i+1) : 0
end
index=index+1
end

function feti(exponent)
(k,n)=size(exponent)
index=zeros(1,k)
[index[j] = sum([binomial(sum(exponent[j,i+1:n])-1+n-i,n-i) for i=0:n-1])+1 for j=1:k]
end

function fite(index,n)
exponent=zeros(Int,1,n);
# first asses the degree
d=0;
while binomial(d+n,n) < index
    d=d+1;
end
if d==0
 return exponent
else
 index = index-binomial(d-1+n,n);

 for i=1:n-1
   k=0;
   while binomial(k+n-i-1,n-i-1) < index
       index = index - binomial(k+n-i-1,n-i-1);
       k=k+1;
   end   
   exponent[i]=d-sum(exponent[1:i-1])-k;
 end
exponent[n] = d-sum(exponent[1:n-1]);
end
return exponent
end

function getD0(polysys)
max([max(sum(polysys[i,2],2)) for i=1:size(polysys,1)])
end

function getDorig(polysys)
[max(sum(polysys[i,2],2)) for i=1:size(polysys,1)]
end
