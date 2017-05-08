# Evaluate the sum of all the amicable numbers under 10000.

# return the number of divisors of x
function sum_of_divisors(x)
	s = 0
	for i in 1:(x/2)
		if x % i == 0
			s += i
		end
	end
	return s
end

x = zeros(10000)
for i=1:10000
	x[i] = sum_of_divisors(i)
end
s = 0
# continue to evaluate sum here


println("Sum of amicable numbers under 10000: ",s)