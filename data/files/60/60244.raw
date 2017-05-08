# By considering the terms in the Fibonacci sequence whose values
# do not exceed four million, finds the sum of the even-valued terms.

function sumOfEvenTerms()
	Sum = 2 # start /w 2 
	curr = 2
	prev1 = 2
	prev2 = 1
	while(curr<=4e6)
		curr = prev1 + prev2
		if(curr%2==0) 
			Sum+=curr
		end
		prev2=prev1
		prev1 = curr
	end
	return Sum 
end

println(sumOfEvenTerms())