# find the smallest positive number that is evenly divisible with 1:20

evenlyDivisible = function()
	Int not_found = 1
	Int number = 1
	while(not_found)
		for ii=2:20
			if(number%ii!=0)
				break
			end
			if(ii==20)
				not_found = 0
			end
		end
		if (not_found)
			number += 1
		end
	end
	number
end

println(evenlyDivisible())