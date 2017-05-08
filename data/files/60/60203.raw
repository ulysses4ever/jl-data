# Longest Collatz sequence: 
# Which starting number, under one million, produces the longest chain? 
# Execution time ~12s

# table for known results up to 2e6
table = zeros(1,2000000)
table[1] = 1
longest = 0
longest_producing_number = 0

# find the next collatz term
function collatz(x)
	if(x%2==0)
		return x/2
	else 
		return 3*x+1
	end
end

for ii in 1:1e6
	x = ii
	path = x # record the path to help dynamic program
	this_length = 1
	look_up_ok = false
	while x != 1
		if x <= 2e6 
			# look for known results
			if table[x] != 0
				this_length += table[x] - 1
				x = 1
				look_up_ok = true
			end
		end
		if !look_up_ok
			# proceed iteratively
			x = collatz(x)
			path = [path x]
			this_length += 1
		end
	end
	# add path to known results
	index = 0
	for jj in path
		if jj <=2e6
			table[jj] = this_length - index
		end
		index += 1
	end
	if this_length > longest
		longest = this_length
		longest_producing_number = ii
	end
end
println("Asked number is: ",longest_producing_number) # 837799
println("With chain length of: ",longest) # 525