module fmmcall

include("fmm.jl")
include("quadtree.jl")



function fmm_eval(tree::Array{quadtree.box,2},levels::Int64)

	box_numbers = quadtree.sort_into_boxes(pos)
	quadtree.initialize()
	M_finest_level = Array(Array{Complex{Float64},1},
			4^(quadtree.levels-1))
	[M_finest_level[i]=quadtree.tree[end,i].M 
	for i=1:4^(quadtree.levels-1)]
 
	FMM.compute_multipole_expansions(q,pos,box_numbers,
							M_finest_level)

	#Wasteful O(nbox) operation!
	[quadtree.tree[end,i].M[:] = M_finest_level[i][:] 
	for i=1:4^(quadtree.levels-1)]

	#Upward Pass
	for i= levels-1:-1:1
		for j = 1:1:2.0^(i-1)	   
				
			FMM.MM_Translate(A,B,z1,z2)

		end
	end
				
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

