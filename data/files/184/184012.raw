# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round 2014
# Problem B: Cookie Clicker Alpha

const initial_rate = 2.0

# Calculates the amount of time (in seconds) needed to get x cookies when farms
# cost c cookies and increase production by f, if using the optimal strategy.
function besttime(c, f, x)
	t = 0
	r = initial_rate
	while x/r > c/r + x/(r+f)
		t += c/r
		r += f
	end
	t + x/r
end

function main()
	n = int(readline())
	for i = 1:n
		c, f, x = float(split(readline()))
		t = besttime(c, f, x)
		println("Case #$i: ", t)
	end
end

main()
