# Number of lattice paths in a 20x20 grid

function solve(grid_size)
	grid = zeros(grid_size + 1, grid_size +1)
	grid[1,:] = grid[:,1] = 1
	for ii in 2:(grid_size + 1)
		for jj in 2:(grid_size + 1)
			grid[ii,jj] = grid[ii - 1,jj] + grid[ii,jj - 1]
		end
	end
	return grid[grid_size + 1,grid_size + 1] 
end 

@printf("Number of lattice paths in 20x20 grid: %d\n",solve(20))