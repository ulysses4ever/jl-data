module fmmcall

include("fmm.jl")
include("quadtree.jl")

#Rewrite round
	function myround(x::Float64)
		if((x-floor(Int64,x)) < 0.5)
				return floor(Int64,x)
		else
				return ceil(Int64,x)
		end

	end

function get_parent(child::Int64, level::Int64)

	n  = 2^(level-1)
	n1 = floor(Int64,child/n/2)
	n2 = ceil(Int64,(child%n)/2)

	parent = floor(Int64,n1*n/2 + n2) 
	parent = parent ==0? 1 : parent
	parent = parent > n^2 ? floor(Int64,n^2) : parent

	#Corner boxes need to be updated.
end
#Wrapper for MM_Translate: to call using prefix
function MM_prefix(X::quadtree.box,Y::quadtree.box)

		s = length(X.M)
		Z = complex(zeros(s))
		z1 = X.Z
		z2 = Y.Z
		FMM.MM_Translate(X.M,Z,z1,z2)
		[Y.M[i] = Z[i] for i=1:s]
		return Y

end
function fmm_eval(tree::Array{quadtree.box,2},
				  q::Array{Float64,2},
				 pos::Array{Complex{Float64},2})
	N = length(q)
	levels = size(tree,1)
	s = quadtree.s
	phi_fmm = complex(zeros(N))
	box_numbers = 
	quadtree.sort_into_boxes(pos,levels)
	quadtree.initialize(tree,levels)
	nbox_finest_level = 4^(levels-1)
	M_finest_level = 
	Array(Array{Complex{Float64},1}
	,nbox_finest_level)
	[M_finest_level[i]=tree[end,i].M 
	for i=1:nbox_finest_level]
 
	FMM.compute_multipole_expansions(q,pos,
	box_numbers,M_finest_level)

	#Wasteful O(nbox) operation!
	[tree[end,i].M[:] = M_finest_level[i][:] 
	for i=1:nbox_finest_level]


		#Upward Pass
	pathind = 
	Array(Int64, levels, nbox_finest_level)
	path = Array(quadtree.box,levels, nbox_finest_level)
	for i= 1:nbox_finest_level
		pathind[1,i] = i
		path[1,i] = tree[end,i]	
		for j = 1:levels-1
			t = pathind[j,i]
			pathind[j+1,i] =
			get_parent(t,levels-j+1)
			path[j+1,i] = tree[end-j,pathind[j+1,i]]
		end
				
		FMM.prefix!(path[:,i], MM_prefix)				
		for j = 1:levels-1
		[tree[end-j,pathind[j+1,i]].M[k] += path[j+1,i].M[k]
		for k=1:s]
		end

	end

		#Downward Pass
	
	

	return phi_fmm	
end


function direct_eval(
		pos::Array{Complex{Float64},2},
		q::Array{Float64,2})
	
	N = length(q)
	phi_direct = complex(zeros(N))
	for i = 1:N
		phi_direct[i] = 0.0 + 0.0im
		for j = 1:N
			if(i!=j)
				phi_direct[i] += q[j]*log(pos[i]-pos[j])
			end
		end
	end
	return real(phi_direct)
end
















end

