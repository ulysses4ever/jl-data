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

#####
# The main difficulty in this function is that we want to be able
# to reconstruct all the steps of the differentiation, so submatrices
# must return all the submatrices found, in the correct order. 
#
# Since submatrices is recursive, with multiple recursions per function call,
# this amounts to collapsing the levels of a tree into a list.
#
# To accomplish this collapsing, each function call includes the entire "tree"
# list along with the current level. We happen to know that given an n x n matrix,
# there will be n-1 levels to the matrix, so we initialize the list-tree
# with that assumption.
#####

function submatrices!(matrix::Array{T, 2}, from_parent)
	numrows = size(matrix, 1)
	numcols = size(matrix, 2)
	pivrow = 1 # In case I add functionality to change which we iter over
	# Currently only iterates over columns

	thislevel = from_parent
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

function determinant_steps(matrix::Array{T,2})
	numrows = size(matrix, 1)
	numcols = size(matrix, 2)
	# TODO: Handle inequal rows/nums. ATM, just let them burn.
	submats = Array(Array, numrows-1)
	submatrices!(matrix, [])
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