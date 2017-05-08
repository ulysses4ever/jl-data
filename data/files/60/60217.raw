# A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
# a^2 + b^2 = c^2
# There exists exactly one Pythagorean triplet for which a + b + c = 1000.
# Finds the product abc.
function PythagoreanTriplet()
	for a in 1:333
		for b in (a+1):(1000-2*a)
			c = 1000 - a - b
			if a^2 + b^2 == c^2
				return a*b*c
			end
		end
	end
	return "did not find answer"
end

println(PythagoreanTriplet())