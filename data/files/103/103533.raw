module FMM
  

import PyPlot
include("quadtree.jl")

global s = 5
maxpart = 10
"""
Performs Translation of Local Expansion 
Centred Around Parent Box (with centre z1
and s-term local expansion in A) to Local 
Expansion Centred Around Child Box (with
centre z2 and s-term local expansion in B)

"""
function LL_Translate(A::Array{Complex{Float64},2}
					,B::Array{Complex{Float64},2},
					z1::Complex{Float64},
					z2::Complex{Float64})
	
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
function ML_Translate(A::Array{Complex{Float64},1}
					,B::Array{Complex{Float64},1},
					z1::Complex{Float64},
					z2::Complex{Float64})


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
function MM_Translate(A::Array{Complex{Float64},1}
		,B::Array{Complex{Float64},1},
		z1::Complex{Float64}
		,z2::Complex{Float64})
	
	z0 = z1 - z2
	B[1] += A[1]
	
	for l=1:s-1
		B[l+1] += -(A[1]/l)*(z0^l)
		for k=1:l
			B[l+1] += (A[k+1]*(z0^(l-k))
			*choose(l-1,k-1))
		end
		
	end

end

"""
Computes Multipole Expansions About
Box Centres At the Finest Level

"""
function compute_multipole_expansions(q::Array{Float64,2},
		pos::Array{Complex{Float64},2},
		box_numbers::Array{Int64,2},
		M_finest_level::Array{Array{Complex{Float64},1},1})
	global s
	particles_in_box = zeros(Int64, size(M_finest_level,1), maxpart)
	nboxes = size(M_finest_level,1)
	count = ones(Int32,size(M_finest_level,1))
	for i = 1:length(q)
		M_finest_level[box_numbers[i]][1] += q[i]
		particles_in_box[box_numbers[i],count[box_numbers[i]]] = i
		count[box_numbers[i]] += 1
	end
	for i = 1:nboxes
		if(count[i]>=2)
		M_finest_level[i][2:s] = 
		-q[particles_in_box[i,1:count[i]-1]]*
		pos[particles_in_box[i,1:count[i]-1]]'./(1:(s-1))
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
