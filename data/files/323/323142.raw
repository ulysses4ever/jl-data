function ithprime(i::Int64)
	primesfound::Int16=0

	n::Integer=0
	while primesfound<i
		n+=1
		isprime(n) && (primesfound+=1)
	end

	n
end

problem07 = ithprime(10_001)

problem07′ = first(drop(filter(isprime, countfrom(1,1)), 10_000))