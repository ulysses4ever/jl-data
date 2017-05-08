module quadtree

levels = 4
boxes  = 1
for i = 1:levels
		boxes += 4^i
end
M = Array{Complex{Float64},2}
L = Array{Complex{Float64},2}

Z = Array{Complex{Float64},1}

function sort_into_boxes(pos)
		
	 xpos = ceil(Int64,real(pos).*(2^levels))
	 ypos = ceil(Int64,imag(pos).*(2^levels))

	 boxnum = xpos + (2^levels).*(ypos-1)
	 return boxnum
	
end






















end
