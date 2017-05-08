module quadtree

s = 5

immutable box 
	M::Array{Complex{Float64},1}
	L::Array{Complex{Float64},1}
	Z::Complex{Float64}
	

end
box() = box( complex(zeros(s)),
				 complex(zeros(s)),
				 0.0 + 0.0im)


function initialize(tree::Array{box,2}, 
			levels::Int64)

	boxes = 4^(levels-1)
	
	for i = 1:levels
		for j =1:boxes
			tree[i,j] = box()
		end
	end
end
function sort_into_boxes(
		pos::Array{Complex{Float64},2},
		levels::Int64)
	 n = 2^(levels-1)
		
	 xpos = ceil(Int64,real(pos).*n)
	 ypos = ceil(Int64,imag(pos).*n)

	 boxnum = xpos + n.*(ypos-1)
	 return boxnum
	
end





















end
