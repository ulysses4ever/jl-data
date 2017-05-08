function solve(sudoku::Array{Int,2})
	newsudoku = copy(sudoku)
	converged = false
	iteration = 0

	while !converged
		iteration += 1

		for idx = 1:length(sudoku)
			if sudoku[idx] == 0 
				possibles = get1stOrderPossibles(idx, newsudoku)
				if length(possibles) == 1
					newsudoku[idx] = possibles[1]
				end

				print("iter: $iteration\nidx: $idx\npossible: $possibles\n$sudoku\n\n")

				if !isValidSudoku(newsudoku)
					error("Invalid sudoku created:\n\niteration: $iteration\nindex: $idx\nsudoku: \n$newsudoku\n\n")
				end
			end
		end

		if newsudoku == sudoku
			converged = true
		end

		sudoku = newsudoku
	end

	sudokuPrint(sudoku)
	return sudoku
end


function getRegion(idx::Int, sudoku::Array{Int,2})
	const idx_matrix = reshape(1:81,9,9)

	for i=0:2
		for j=0:2
			if idx in idx_matrix[i*3+1:i*3+3, j*3+1:j*3+3]
				return sudoku[i*3+1:i*3+3, j*3+1:j*3+3]
			end
		end
	end

end

function hasDoubles(itr)
	for item in itr
		if item != 0 && count(x -> x == item, itr) > 1
			return true
		end
	end

	return false
end

function isValidSudoku(sudoku::Array{Int,2})
	# check collums and rows
	for i=1:9
		
		collum = sudoku[:,i]
		row    = sudoku[i,:]
		#region = getRegion()

		if hasDoubles(collum) 
			print("bad collum $i")
			return false
		end


		if hasDoubles(collum) 
			print("bad row $i")
			return false
		end
	end

	# check regions
	for i=0:2
		for j=0:2
			region = sudoku[i*3+1:i*3+3, j*3+1:j*3+3]
			
			if hasDoubles(region)
				print("Bad region $(i+1) $(j+1)")
				return false
			end
		end
	end

	return true
end

function isFinishedSudoku(sudoku::Array{Int,2})
	return isValidSudoku(sudoku) && all(i -> i != 0, sudoku)
end

function get1stOrderPossibles(idx::Int, sudoku::Array{Int,2})
	if sudoku[idx] != 0
		error("Attempting to get possibilities for allready filled index")
	end

	all_numbers = 0:9

	i,j = ind2sub(size(sudoku), idx)

	collum = sudoku[:,j]
	row    = sudoku[i,:]
	region = getRegion(idx, sudoku)

	not_possibles = union(collum,row,region)
	print("not possible: $not_possibles\n")

	return setdiff(all_numbers, not_possibles)
end


function sudokuPrint(sudoku::Array{Int,2})
	print("$(sudoku[1,1:3]) $(sudoku[1,4:6]) $(sudoku[1,7:9])\n")
	print("$(sudoku[2,1:3]) $(sudoku[2,4:6]) $(sudoku[2,7:9])\n")
	print("$(sudoku[3,1:3]) $(sudoku[3,4:6]) $(sudoku[3,7:9])\n")
	print("\n")

	print("$(sudoku[4,1:3]) $(sudoku[4,4:6]) $(sudoku[4,7:9])\n")
	print("$(sudoku[5,1:3]) $(sudoku[5,4:6]) $(sudoku[5,7:9])\n")
	print("$(sudoku[6,1:3]) $(sudoku[6,4:6]) $(sudoku[6,7:9])\n")

	print("\n")

	print("$(sudoku[7,1:3]) $(sudoku[7,4:6]) $(sudoku[7,7:9])\n")
	print("$(sudoku[8,1:3]) $(sudoku[8,4:6]) $(sudoku[8,7:9])\n")
	print("$(sudoku[9,1:3]) $(sudoku[9,4:6]) $(sudoku[9,7:9])\n")

	print("\n")
end
