# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round Africa 2010
# Problem A: Store Credit

# Finds indices (i,j) where i < j and ps[i] + ps[j] = c.
function findindices(c, ps)
	for (i, a) in enumerate(ps)
		b = c - a
		j = findfirst(ps[i+1:end], b)
		if j != 0
			return i, i+j
		end
	end
end

function main()
	n = int(readline())
	for i = 1:n
		c = int(readline())
		readline() # number of products
		ps = int(split(readline()))
		a, b = findindices(c, ps)
		println("Case #$i: $a $b")
	end
end

main()
