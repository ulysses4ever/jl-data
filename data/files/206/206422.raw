# Euler problem 15
# Number of ways to traverse an n x n grid
tic()

n = 1000
grid = [-1 for i=1:n,j=1:n] # Grid to be filled, at index (i,j) is the number of possible ways from (i,j) to (n,n)
grid[n,:] = grid[:,n]= 1 	# When an edge is reached there is only one possible path left
i = j = n

function findpaths(i,j)		# Recursively find total number of ways 
	global grid
	if grid[i+1,j] == -1
		findpaths(i+1,j)
	end
	if grid[i,j+1] == -1
		findpaths(i,j+1)
	end
	grid[i,j] = grid[i+1,j] + grid[i,j+1]
end

findpaths(1,1)
println("Number of routes: ",grid[1,1])

toc()

# n = 21
# i = 1
# j = 1
# paths = 0

# Tar för lång tid:
# function iterate(i,j)
# 	global paths
# 	if i < n && j < n
# 		iterate(i+1,j)
# 		iterate(i,j+1)
# 	else
# 		paths += 1
# 	end
# end
#
# iterate(1,1)
# println(paths)

