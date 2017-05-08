#!/usr/bin/env julia

require("ArgParse")
require("TexTools")
using ArgParse, TexTools

s = ArgParseSettings()

@add_arg_table s begin
	"matrix"
		help = "A matrix string, to be parsed and evaluated"
		required = true
end

parsed_args = parse_args(s)

###
## AWFUL PRACTICE, SO MUCH HACKING
###
input_mat = eval(parse(parsed_args["matrix"]))

# tex = texify(input_mat, "v")

# println("$(tex)")

function submatrices(matrix::Array{Int, 2})
	numrows = size(matrix, 1)
	numcols = size(matrix, 2)
	pivrow = 1 # In case I add functionality to change which we iter over
	# Currently only iterates over columns

	thislevel = []
	next = []

	for pivcol in 1:numcols
		count = 1
		submat = [ matrix[rownum, colnum] for rownum=(1:numrows)[1:numrows .!= pivrow],
			colnum=(1:numcols)[1:numcols .!= pivcol] ]
		# for rownum in (1:numrows)[1:numrows .!= pivrow]
		# 	for colnum in (1:numcols)[1:numcols .!= pivcol]
		# 		hcat(submat, [matrix[rownum,colnum]])
		# 	end
		# end
		factor = matrix[pivrow, pivcol] * (-1)^(pivrow+pivcol)
		reshaped_submat = reshape(submat, numrows-1, numcols-1)
		thislevel = cat(1, thislevel, (factor, reshaped_submat))
		if numrows > 1
			nextlevel, further = submatrices(reshaped_submat)
		end
	end

	return (thislevel, next)
end

function determinant_steps(matrix::Array{Int,2})
	thislevel, next = submatrices(matrix)
	stepslist = [[texify(thislevel,"v")]]
	while 

		size(next,1) > 0 && break
		thislevel, next = next[1]
		vcat(stepslist, [texify(thislevel, "v")])
	end
	return join(stepslist, "\\\\ \n \t &=")
end


println("$(determinant_steps(input_mat))")

### The problem is that I need to figure out how to collapse a tree inward.