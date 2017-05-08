function smallestMultiple(r::Range)
	divisibleByAll(n) = all([n%m ≡ 0 for m in r])

	n=1
	while !divisibleByAll(n)
		n+=1
	end

	n
end

problem05 = smallestMultiple(1:20)

# Lmao!
problem05′ = lcm(1:20)