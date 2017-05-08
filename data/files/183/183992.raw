# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Round 1A 2008
# Problem A: Minimum Scalar Product

# Calculates the minimum dot product of the permutations of u and v.
function mindot(u, v)
	sum = 0
	while !isempty(u)
		i = indmin(u)
		j = indmax(v)
		sum += splice!(u, i) * splice!(v, j)
	end
	sum
end

function main()
	n = int(readline())
	for i = 1:n
		readline() # vector length
		u = int(split(readline()))
		v = int(split(readline()))
		println("Case #$i: ", mindot(u, v))
	end
end

main()
