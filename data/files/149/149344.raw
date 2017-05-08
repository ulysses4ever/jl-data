# Project Euler Problem 9
# 4-20-14, Ben Southgate

# Question:
# There exists exactly one Pythagorean triplet for which a + b + c = 1000.
# Find the product abc.

# Solve a^2 + b^2 = (1000 - a - b)^2
b(a) = 1000*(a-500)/(a-1000)
# Check if int
is_int(x) = (x-floor(x)) == 0

for a=3:999
	if is_int(b(a)) && b(a) > 0
		c = (sqrt(a^2 + b(a)^2))
		println("a=$a, b=$(b(a)), c=$c")
		println("Product = a*b*c = $(a*b(a)*c)")
		break
	end
end

