# find the smallest positive number that is evenly divisible with 1:20
function evenlyDivisible()
	not_found = true
	number = 1
	while(not_found)
		for ii=2:20
			if(number%ii!=0)
				break
			end
			if(ii==20)
				not_found = false
			end
		end
		if (not_found)
			number += 1
		end
	end
	return number
end
println(evenlyDivisible())