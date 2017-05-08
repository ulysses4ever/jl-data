module fmmcall

include("fmm.jl")
include("quadtree.jl")

N = 10
s = 5
q = rand(N,1)
pos = rand(N,1) + im*rand(N,1)
phi_direct = rand(N,1) + im*rand(N,1)
phi_fmm = rand(N,1) + im*rand(N,1)
box_numbers = quadtree.sort_into_boxes(pos)

function direct_eval()
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





function fmm_eval()

				
end


















end

