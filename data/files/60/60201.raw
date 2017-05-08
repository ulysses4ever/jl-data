# What is the value of the first triangle number
# to have over five hundred divisors?
# Using formula divisors(x)=(a_1+1)*...*(a_n+1)
# where a_i is the multiplicity of the ith prime factor of x
first = 1 
iterator = 2 
not_found = true
while(not_found)
	first += iterator # first to be checked is 3
	iterator += 1
	factors = 1
	pfactors = factor(first)
	for ii in values(pfactors)
		factors*= ii+1
	end
	if factors > 500
		not_found = false
	end
end
println(first)