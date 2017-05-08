function poly(a,x)
	sum=0;
	for i=1:length(a)
		sum+=a[i]*x.^(i-1)
	end
	return sum
end

function polyval(a,x)
	sum=0
	for i=1:length(a)
		sum+=a.value[i]*x.^(i-1)
	end
	return sum
end

function diffpoly(a,x)
	sum=0
	for i=1:length(a)
		sum+=(i-1)*a[i]*x.^(i-2)
	end
	return sum
end

function diff2poly(a,x)
	sum=0
	for i=1:length(a)
		sum+=(i-1)*(i-2)*a[i]*x.^(i-3)
	end
	return sum
end

#Evaluate a polynomial with coeffs a and data x
#n is the degree of the first component (time)
#m is the degree of the other components. Mirrors the construction
#in genreg.jl

function multipolyval(a,x,n,m)
k=size(x,1)
l=size(x,2)
local X
w=l-1 #number of explanatory, non-time variables

for i=0:n, j= 0:m^w-1
                if i==0 && j==0
                        X=ones(k,1)
                else
                        A=digits(j,m,w) #integer i in base m with zero padding w
                        t=ones(k)
                        for p=1:w
                                t=t.*(x[:,p+1].^A[p])
                        end
                        X=hcat(X,x[:,1].^i.*t)
                end
end
return X*a
end

# old
#function multipolyval(a,x,y, n, m)
#	S=zeros(x.*y)
#	k=1	
#	for i=0:n, j=0:m
#		S=S+a[k]*x.^i.*y.^j
#	k=k+1
#	end
#	return S
#end
