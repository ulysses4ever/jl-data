
include("C:/sde/db12/julia/pm.jl")

primesmax = 200
numrange = 200



for m in [1:numrange] 
	i = 2m
	expdata = String[]
	push!(expdata,"$i;$(PM.pm(primesmax,i));")
	setprimes = Set()
	counter = 0
	minprime = 0
	for j in primes(m)
		if isprime(i -j)
			counter = counter+1
			if (minprime == 0)
				minprime = j
			end
			push!(expdata,"[$j,$(i-j)] ")
			push!(setprimes,j)
			push!(setprimes,i-j)
		end
	end
	push!(expdata,";$counter;")
	if (minprime > 7)
		println(expdata...)
	end
end

for i in primes(2numrange)
	tup = string(PM.pm(2primesmax,i))
	replace(tup, "(", "")
	replace(tup, ")", "")
	replace(tup, ",", ";")
	println("$i;$tup")
end


#=
for m in primes(100)
	print("$m;")
end
println("")

for m in primes(100)
	print("$m;")
	for k in primes(100)
		print(PM.partner(k,m))
		print(";")
	end
	println()
end
=#
