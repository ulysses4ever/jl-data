# Copyright 2014 Mitchell Kember. Subject to the MIT License.
# Google Code Jam Qualification Round 2014
# Problem C: Minesweeper Master

# Computes a minesweeper grid with, r rows, c columns, and m mines that can be
# won win a single click on the cell labelled 'c'.
function oneclickgrid(r, c, m)
	if m == 0
		grid = fill('.', r, c)
		grid[1,1] = 'c'
		return grid
	end
	if r <= 2 && c <= 2
		return nothing
	end
	ns = r*c - m
	grid = fill('*', r, c)
	grid[1,1] = '.'
	if solve!(grid, ns)
		grid[1,1] = 'c'
		return grid
	end
	if r != 1 && c != 1
		fill!(grid, '*')
		grid[2,2] = '.'
		if solve!(grid, ns)
			grid[2,2] = 'c'
			return grid
		end
	end
	if r >= 3 && c >= 3
		fill!(grid, '*')
		grid[3,3] = '.'
		if solve!(grid, ns)
			grid[3,3] = 'c'
			return grid
		end
	end
	nothing
end

# Attempts to solve the grid so that there are ns safe cells which will all be
# revealed with a one click on the 'c' cell. Returns true if sucessful.
function solve!(g, ns)
	sz = size(g)
	nsc = 1
	while nsc < ns
		ind = (0,0)
		smallest = 9
		for i = 1:sz[1], j = 1:sz[2]
			if g[i,j] == '.'
				n = nmines(g, i, j)
				if nsc + n == ns
					demine_neighbours!(g, i, j)
					return true
				end
				if n > 0 && n < smallest
					ind = (i,j)
					smallest = n
				end
			end
		end
		if smallest == 9
			return false
		end
		demine_neighbours!(g, ind[1], ind[2])
		nsc += smallest
	end
	false
end

# Returns the number of mines neibouring the cell at (i,j).
function nmines(g, i, j)
	sz = size(g)
	f(x,y) = (x >= 1 && y >= 1 && x <= sz[1] && y <= sz[2] && g[x,y] == '*')?1:0
	+(f(i-1,j-1),f(i-1,j),f(i-1,j+1),f(i,j-1),f(i,j+1),f(i+1,j-1),f(i+1,j),f(i+1,j+1))
end

# Removes mines from cells neighbouring (i,j).
function demine_neighbours!(g, i, j)
	sz = size(g)
	f(x,y) = (x >= 1 && y >= 1 && x <= sz[1] && y <= sz[2])?g[x,y]='.':nothing
	f(i-1,j-1);f(i-1,j);f(i-1,j+1);f(i,j-1);f(i,j+1);f(i+1,j-1);f(i+1,j);f(i+1,j+1)
end

# Converts a grid, or nothing, to a string.
function message(grid)
	if grid === nothing
		"Impossible"
	else
		join(map(i -> join(grid[i,:]), 1:size(grid, 1)), '\n')
	end
end

function main()
	n = int(readline())
	for i = 1:n
		r, c, m = int(split(readline()))
		grid = oneclickgrid(r, c, m)
		println("Case #$i:")
		println(message(grid))
	end
end

main()
