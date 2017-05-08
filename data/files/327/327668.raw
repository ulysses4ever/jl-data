# Sieve of Eratosthenes, docstrings coming in Julia 0.4
function es(n::Int32)
	# accepts one 64 bit integer argument
	isprime = ones(Bool, n)
	# n-element vector of true-s
	isprime[1] = false
	# 1 is not a prime
	for i in 2:int64(sqrt(n))
		# loop integers from 2 to sqrt(n), explicit conversion to integer
		if isprime[i]
			# conditional evaluation
			for j in (i*i):i:n
			# sequence from i^2 to n with step i
			isprime[j] = false
			# j is divisible by i
			end
		end
	end
	return filter(x -> isprime[x], 1:n)
	# filter using anonymous function
end

function es(n::Float64)
	return 0
end

println(es(80))
println(es(80.0))
# print all primes less or equal than 100
@time es(10^7)
# check function execution time and memory usage	