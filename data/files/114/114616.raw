function proper_divisors(n::Int)
	#this could be done much more efficiently if we calculated the sum directly
	#but this is meant to be illustrative
	divisors = Array(Int, 0)
	for i = 1:(n-1)
		if (n % i) == 0
			push!(divisors, i)
		end
	end
	divisors
end

function amicable_numbers(n)
	num_to_div_sum = Dict{Int, Int}()
	for i = 2:n
		num_to_div_sum[i] = sum(proper_divisors(i))
	end
	result = Set{Int}()
	for (k, v) in num_to_div_sum
		if haskey(num_to_div_sum, v) && num_to_div_sum[v] == k && k != v
			push!(result, k)
		end
	end
	result
end

function sum_amicable_numbers(n)
	numbers = amicable_numbers(n)
	sum(numbers)
end

println(sum_amicable_numbers(10000))
