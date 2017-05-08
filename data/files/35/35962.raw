function fib(i::Int64)
	if i == 1
		1
	elseif i == 2
		2
	else
		sum = 0
		local first = 1, second = 2
		for j = 3:i
			sum = first + second
			first = second
			second = sum 
		end
		return sum
	end		
end

function evensum(max::Int64)
	i = 1
	sum = 0
	value = 0
	while value < max
		value = fib(i)
		if value % 2 == 0
			sum += value
		end
		i += 1
	end
	return sum
end