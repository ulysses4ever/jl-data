function is_palindrome(number::Int64)
	s = string(number)

	return s == reverse(s)
end

function largest_palindrome(no_digits::Int64)
	first     = 10^(no_digits - 1) :: Int64
	last      = first * 10 - 1 :: Int64

	for i = last:-1:first
		for j = last:-1:first
			product = i*j :: Int64
			if is_palindrome(product)
				return (product, i, j)
			end
		end
	end

	return 0
end


function slow_largest_palindrome(no_digits::Int64)
	first     = 10^(no_digits - 1) :: Int64
	last      = first * 10 - 1 :: Int64
	max_prod  = 0 :: Int64
	product   = 0 :: Int64

	for i = first:last
		for j = first:last
			product = i*j :: Int64
			if product > max_prod && is_palindrome(product)
				max_prod = product
			end
		end
	end

	return max_prod
end