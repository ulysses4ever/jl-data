n = 14

if n%2 == 0
	last_factor = 2
	n = n/2
	while n%2 == 0
		n = n/2
	end
else last_factor = 1
end

factor = 3
max_factor = sqrt(n)
while n>1 && factor <= max_factor
	if n%factor == 0
		n = n/factor
		last_factor = factor
		while n%factor == 0
			n = n/factor
		end
		max_factor = sqrt(n)
	end
	factor = factor + 2
end

if  n == 1
	return last_factor
else return n
end