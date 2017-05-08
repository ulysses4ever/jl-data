module quadtree

global tree,levels,boxes
export tree
levels = 4
boxes  = 0
s = 5
for i = 0:levels-1
		boxes += 4^i
end
immutable box 
	M::Array{Complex{Float64},1}
	L::Array{Complex{Float64},1}
	Z::Complex{Float64}
	

end
box() = box( complex(zeros(s)),
				 complex(zeros(s)),
				 0.0 + 0.0im)

tree = Array(box,levels,boxes)
function initialize()
	global tree, levels, boxes 
	for i = 1:levels
		for j =1:boxes
			tree[i,j] = box()
		end
	end
end
function sort_into_boxes(pos)
		
	 xpos = ceil(Int64,real(pos).*(2^levels))
	 ypos = ceil(Int64,imag(pos).*(2^levels))

	 boxnum = xpos + (2^levels).*(ypos-1)
	 return boxnum
	
end





















end
