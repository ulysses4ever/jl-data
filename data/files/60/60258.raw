# find the largest palindrome made from the product of two 3-digit numbers
function largestPalindrome()
	largest = -1 # not found
	for ii=100:999
		for jj=ii:999
			number = string(ii*jj)
			if number==reverse(number)
				largest = max(largest,int(number))
			end
		end
	end
	return largest
end
println(largestPalindrome())