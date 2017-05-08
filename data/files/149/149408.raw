# Project Euler Problem 3
# 4-10-14, Ben Southgate

# May have gotten a little help from here: 
# http://math.stackexchange.com/questions/389675/largest-prime-factor-of-600851475143

function largest_prime_factor(n::Int64)

	b::Int64 = 2
	c::Int64 = 1

	while n != b
		if n%b == 0
			n /= b
			b = 2
		else 
			b += 1
		end
	end

	return n
end

println(largest_prime_factor(600851475143))
