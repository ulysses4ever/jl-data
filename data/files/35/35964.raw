function largestfactor(number::Int64)
	for i = number - 1:-1:1
		if number % i == 0
			return i
		end
	end
end

function largestprimefactor(number::Int64)
	factor = number
	result = 1
	while factor != 1
		result = factor
		factor = largestfactor(factor)
	end
	return result
end

# This is a lot faster than the ones above because we look at the lower
# numbers first. The idea that we test divide on a low number `i`, so that 
# div(n, i) is potentially the largest prime factor. If mod(n, i) == 0 it
# is the largest dividing factor when `i` starts low. But this might not
# be the largest prime fact. So we find the largest factor of div(n, i) and
# continue like that.
function fast(n::Int64)
   for i in 2:(n-1)
      if mod(n, i) == 0
         return fast(div(n, i))
      end
   end
   return n
end