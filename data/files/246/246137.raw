#= Largest prime factor
Problem 3
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?


Answer:
6857
Completed on Sat, 20 Apr 2013, 16:04 =#

function is_prime(n)
	for i = 2:n-1 
		if n%i ==0
			return false
			break
		end
	end
	return true
end


function largest_prime_factor(n)
	if is_prime(n)
		return n
	end
	sqrtn_int = round(Int, sqrt(n))
	for i = sqrtn_int:-1:2
		if n%i == 0 && is_prime(i)   
			return i 
		end
	end
end
