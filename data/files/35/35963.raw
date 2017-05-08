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