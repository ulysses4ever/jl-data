# Maximum path sum I
# Using dynamic programming
grid = readdlm("./PE18-pyramid.txt",' ')
for row=2:15
	for col=1:row
		if 1<col<row
			grid[row,col] += max(grid[row-1,col-1],grid[row-1,col])
		elseif col == 1
			grid[row,col] += grid[row-1,col]
		else
			grid[row,col] += grid[row-1,col-1]
		end
	end
end

# find max value
m = 0
for ii in 1:15
	m = max(m,grid[15,ii])
end 
println("Maximum route value: ",m) 