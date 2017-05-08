#!/usr/bin/env julia

# Author: Graham Smith

module TexTools

export texify

function texify(matrix::Array{Number, 2}, mtype::String)
	if size(matrix,1) == 1
		return "$(matrix[1])"
	end
	texout = "\\begin{$(mtype)matrix}\n"
	numrows = size(matrix,1)
	numcols = size(matrix,2)
	rows = Array(String, numrows)
	for rownum in 1:numrows
		row = Array(String, numcols)
		for colnum in 1:numcols
			row[colnum] = "$(matrix[rownum, colnum])"
		end
		rows[rownum] = join(row, " & ")
	end
	matstr = join(rows, "\\\\ \n")
	return join(["\\begin{$(mtype)matrix}\n", matstr, "\n\\end{$(mtype)matrix} "])
end

function texify(matrix::Array{Number, 1}, mtype::String)
	return "$(matrix[1])"
end

function texify(fac_and_mat::(Number, Array{Number, 2}), mtype::String)
	factor, matrix = fac_and_mat
	# NOTE: Has leading sign, even when positive
	sgn = "+"
	if sign(factor) < 0
		sgn = "-"
	end
	return ["$sgn $(abs(factor)) \\cdot $(texify(matrix, mtype))"]
end

function texify(matrices::Array, mtype::String)
	nummats = size(matrices,1)
	texmats = Array(String, nummats)


	texmats = [texify(matrices[i], mtype) for i=1:nummats]

	return join(texmats, " ")
end

end

