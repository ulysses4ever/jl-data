module FMM
  

import PyPlot

s = 5

"""
Performs Translation of Local Expansion 
Centred Around Parent Box (with centre z1
and s-term local expansion in A) to Local 
Expansion Centred Around Child Box (with
centre z2 and s-term local expansion in B)

"""
function LL_Translate(A,B,z1,z2)
	
	z0 = z1 - z2
	for l=1:s+1
		for k=l:s+1
			B[l] += A[k]*((-z0)^(k-l))*choose(k-1,l-1)
		end
	end

end

"""
n choose k

"""
function choose(n,k)
	
	return fact(n)/(fact(k)*fact(n-k))
end

"""
Performs Translation of Multipole Expansion 
Centred Around Box in Interaction List (with 
centre z1 and s-term local expansion 
in A) to Local Expansion Centred 
Around Box (with centre z2 
and s-term local expansion in B)

"""
function ML_Translate(A,B,z1,z2)

	z0 = z1 - z2
	B[1] += A[1]*log(-z0) + sum(A[2:(s+1)].*((-1/z0).^((1:s)')))
	
	for l=1:s
		B[l+1] += -(A[1]/l)/z0^l
		for k=l:s
			B[l+1] += (A[k+1]/((-z0)^(l+k))
			*choose(l+k-1,k-1)*(-1)^k)
		end
		
	end

end

"""
Performs Translation of Multipole Expansion 
Centred Around Child Box (with 
centre z1 and s-term Multipole expansion 
in A) to Multipole Expansion Centred 
Around Parent Box (with centre z2 
and s-term local expansion in B)

"""
function MM_Translate(A,B,z1,z2)
	
	z0 = z1 - z2
	B[1] += A[1]
	
	for l=1:s
		B[l+1] += -(A[1]/l)*(z0^l)
		for k=1:l
			B[l+1] += (A[k+1]*(z0^(l-k))
			*choose(l-1,k-1))
		end
		
	end

end



"""
Finds factorials for small numbers

"""
function fact(i::Int64)
	
	if(i==0||i==1)
		return 1
	else
		return i*fact(i-1)
	end
	
end

"""
Computes Parallel Prefix Sum
Courtesy: 18.337 Lecture Notebook

"""
function prefix!(y, f)
    l=length(y)
    k=ceil(Int, log2(l))
    @inbounds for j=1:k, i=2^j:2^j:min(l, 2^k)              #"reduce"
        y[i] = f(y[i-2^(j-1)] , y[i])
    end
    @inbounds for j=(k-1):-1:1, i=3*2^(j-1):2^j:min(l, 2^k) #"broadcast"
        y[i] = f(y[i-2^(j-1)] , y[i])
    end
    y
end

end
