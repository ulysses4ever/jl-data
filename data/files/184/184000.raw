# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Round 1A 2008
# Problem C: Numbers

# Returns the last three digits before the decimal point of the sum 3 + sqrt(5)
# raised to the nth power, as a 3-character string left-padded with zeros.
function last3(n)
	mat = [0 1; -4 6]^(n-1)
	x = (6mat[1,1] + 28mat[1,2] + 1_000_000) % 1000
	x = (x == 0) ? 999 : x - 1
	lpad(x, 3, 0)
end

function main()
	n = int(readline())
	for i = 1:n
		x = int(readline())
		println("Case #$i: ", last3(x))
	end
end

main()
