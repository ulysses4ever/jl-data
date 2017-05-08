module MatrixDecomposition
export luls, lupp, choleskyls, qrls, lulspp

# Solve a system of linear equations using backwards substitution
function bwsub(a::Array{Float64, 2}, v::Array{Float64, 1})
	# Make sure we have an upper triangular matrix
	if !istriu(a)
		error("Matrix is not upper triangular")
	end

	# Create result vector the same size as v
	result = zeros(v)

	# The last value in result = last value in v scaled by last value in a
	result[end] = v[end] / a[end]

	# Iterate backwards through every row of a (except the last)
	for i in size(a, 1)-1:-1:1
		# Perform backwards substitution at each step
		sumterm = sum([a[i,j] * result[j] for j in i+1:size(a, 1)])
		result[i] = (1.0 / a[i,i]) * (v[i] - sumterm)
	end

	return result
end

# Solve a system of linear equations using forwards substitution
function fwsub(a::Array{Float64, 2}, v::Array{Float64, 1})
	# Make sure we have a lower triangular matrix
	if !istril(a)
		error("Matrix is not lower triangular")
	end

	# Create result vector the same size as v
	result = zeros(v)

	# The first value in result = the first value in v scaled by first value in a
	result[1] = v[1] / a[1]

	# Iterate forward through every row of a (except the first)
	for i in 2:size(a, 1)
		# Perform forwards substitution at each step
		sumterm = sum([a[i,j] * result[j] for j in 1:i-1])
		result[i] = (1.0 / a[i,i]) * (v[i] - sumterm)
	end

	return result
end

# Swap two rows of a matrix (works for any number filled matrix)
function swaprows!{T<:Number}(a::Array{T, 2}, i::Int64, j::Int64)
	# For every number across the first row
	for k in 1:size(a, 2)
		# Swap with the corresponding number in the second row
		a[i,k], a[j,k] = a[j,k], a[i,k]
	end
end

# Return stricly lower triangular portion of matrix
function stricttril{T<:Number}(a::Array{T, 2})
	return tril(a) - diagm(diag(a))
end

# Find LU Decomposition of a matrix using Crout's algorithm
function crout{T<:Number}(a::Array{T, 2}; print=false)
	N = size(a, 2)

	# Create diagonal NxN matrix to hold result in place
	result = copy(a)

	# Create matrix to store our permutations
	permuts = int(eye(a))

	# Perform Crout's algorithm in place
	for p in 1:N
		# Find u's
		for j in p:N
			# If j = 1 the sum term is taken to be zero
			sumterm = j == 1 ? 0 : sum([result[p,k] * result[k,j] for k in 1:p-1])

			result[p,j] = result[p,j] - sumterm
		end

		# Find v's
		for i in p+1:N
			# If i = 1 the sum term is taken to be zero
			sumterm = i == 1 ? 0 : sum([result[i,k] * result[k,p] for k in 1:p-1])
			result[i,p] = (result[i,p] - sumterm) / result[p,p]
		end
	end

	# Extract l and u from result matrix
	u = triu(result)
	l = stricttril(result) + eye(result)

	# Print decomposition, if requested
	if print
		println("L:\n", l)
		println("U:\n", u)
		println()
	end

	return l, u
end

# Calculate least squares estimate using LU Decomposition via Crout's Algorithm
function luls{T<:Number}(x::Array{T, 2}, y::Array{T, 1}; print=false)
	# Calculate normal equations
	m = x' * x
	v = x' * y

	# Calculate LU decomposition
	l, u = crout(m, print=print)

	# Solve V = L * gamma using forward substitution
	gamma = fwsub(l, v)

	# Solve gamma = U beta
	beta = bwsub(u, gamma)

	return beta
end

# LU Decomposition with partial pivoting
# Returns L, U and the permutation matrix recording the row pivots
function lupp{T<:Number}(a::Array{T, 2}; print=false)
	N = size(a, 2)

	# Create a copy of the input to work on
	acopy = copy(a)

	# Maintain a record of our permutations
	permut = eye(a)

	for p in 1:N-1
		if print
			println("Pivot ", p)
		end

		# Find the largest value in the current column
		istar = indmax(abs(acopy[:,p]))

		# Swap rows in the permutation and working matrices
		if istar > p
			swaprows!(permut, istar, p)
			swaprows!(acopy, istar, p)
		end

		# Dividing by zero is bad
		if a[p,p] != 0
			# Calculate l's in column
			acopy[p+1:end,p] /= acopy[p,p]

			# Subtract product of row and column k from submatrix
			acopy[p+1:end,p+1:end] -= (acopy[p+1:end,p] * acopy[p,p+1:end])
		end

		if print
			println(acopy, "\n")
		end
	end

	u = triu(acopy)
	l = stricttril(acopy) + eye(acopy)

	if print
		println("L:\n", l)
		println("U:\n", u)
		println()
	end

	return l, u, permut
end

# Calculate least squares estimate using LU Decomposition with partial pivoting
function lulspp{T<:Number}(x::Array{T, 2}, y::Array{T, 1}; print=false)
	# Calculate normal equations
	m = x' * x
	v = x' * y

	# Calculate LU decomposition
	l, u, p = lupp(m, print=print)

	# Solve V = l * gamma using forward substitution
	gamma = fwsub(l, p' * v)

	# Solve gamma = U beta
	beta = bwsub(u, gamma)

	return beta
end

# Find Cholesky decomposition of a positive definite symmetric matrix
function cholesky{T<:Number}(a::Array{T, 2}; print=false)
	# Verify that matrix is positive definite and symmetric
	if !isposdef(a)
		error("Matrix is not positive definite")
	end

	if !issym(a)
		error("Matrix is not symmetric")
	end

	N = size(a, 2)

	# Create result matrix by copying lower triangle of a
	result = tril(a)

	# Iterate through lower diagonal cells
	for p in 1:N
		# Sum is taken to be zero if p=1
		sumterm = p == 1 ? 0 : sum([result[p,j]^2 for j in 1:p-1])
		result[p,p] = sqrt((result[p,p] - sumterm))

		for i in p+1:N
			sumterm = p == 1 ? 0 : sum([result[i,j] * result[p,j] for j in 1:p-1])
			result[i,p] = (result[i,p] - sumterm) / result[p,p]
		end
	end

	# Print decomposition, if requested
	if print
		println("L:\n", result)
		println()
	end

	return result
end

# Solve a system of linear equations via Cholesky decomposition
function solvecholesky{T<:Number}(a::Array{T, 2}, v::Array{T, 1}; print=false)
	# Compute Cholesky decomposition
	l = cholesky(a, print=print)

	# Solve Ly = b using forward substitution
	y = fwsub(l, v)

	# Solve L'x=y using backward substitution
	x = bwsub(l', y)

	return x
end

# Calculate least squares estimate using Cholesky decomposition
function choleskyls{T<:Number}(x::Array{T, 2}, y::Array{T,1}; print=false)
	# Form components of normal equations
	m = x' * x
	v = x' * y

	# Solve using Cholesky decomposition
	return solvecholesky(m, v, print=print)
end

# Project one vector onto another
function project{T<:Number}(u::Array{T, 1}, v::Array{T, 1})
	return (dot(u, v) / dot(u, u)) * u
end

# Orthonormalize a set of vectors using Gram-Schmidt
function gs{T<:Number}(a::Array{T, 2})
	N = size(a, 2)

	result = copy(a)

	# For each column vector in a
	for i in 1:N
		for j in 1:i-1
			# Subtract all the previous projections
			result[:,i] -= project(result[:,j], a[:,i])
		end
	end

	# Normalize columns
	denominators = sqrt(sum(result.^2.0, 1))
	result = result ./ denominators

	return result
end

# Find QR Decomposition using Gram-Schmidt
function qrgs{T<:Number}(a::Array{T, 2}; print=false)
	N = size(a, 2)

	# Make sure matrix is full rank
	if rank(a) != N
		error("Matrix is not full rank")
	end

	# Perform Gram-Schmidt orthogonalization
	q = gs(a)
	# Need to keep only the upper triangular due to rounding errors
	r = triu(q' * a)

	# Print decomposition if requested
	if print
		println("Q:\n", q)
		println("R:\n", r)
		println()
	end

	return q, r
end

# Calculate least squares estimates using QR Decomposition
function qrls{T<:Number}(x::Array{T, 2}, y::Array{T, 1}; print=false)
	# Form components of normal equations
	# Note - I think decomposing X'X instead of X leads to stability problems
	# but I did it this way to fulfill the parameters of an assignment.
	m = x' * x
	v = x' * y

	# Compute QR decomposition
	q, r = qrgs(m, print=print)

	# Solve Rbeta = Q'V using backward substitution
	return bwsub(r, q' * v)
end
end