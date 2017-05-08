
# Find check if n is prime

function is_prime(n::Int64)

	if n <= 3
	    return true;
	end

	if is_divisible(n, 2)
	    return false;
	end

	return true;

	i = 3;

	while i <= sqrt(n)
		if is_divisible(n, i)
			return false;
		end
		i += 2;
	end

	return true;
end

function is_divisible(n, i)

	return n % i == 0;

end

println(is_prime(101));
