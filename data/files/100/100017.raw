# Let V be an element of Hn, the hypercube of dimension N
#	V::Array{Int, 1}
# - the coordinates of the vertex
#	length(V) == N

###
# Group Operations
###

# Parameters:
#	V1::Array{Int, 1}
#	- the first vertex
#	V2::Array{Int, 1}
#	- the second vertex
# Return Value:
#	Prod::Array{Int, 1}
#	- the vertex that is V1 * V2 (we use multiplicative notation here)
function hn_multiply(V1::Array{Int, 1}, V2::Array{Int, 1})
  @assert length(V1) == length(V2)
	N = length(V1)
	Prod = Array(Int, N)
	for i = 1:N
		Prod[i] = V1[i] $ V2[i]
	end
	return Prod
end

# Parameters:
#	V::Array{Int, 1}
#	- a vertex of Hn
# Return Values:
#	Inv::Array{Int, 1}
#	- the vertex that is the inverse of P
function hn_inverse(V::Array{Int, 1})
	Inv = copy(V)
	return Inv
end

# Parameters:
#	N::Int
#   - the dimension of Hn
# Return Values
#	Id::Array{Int, 1}
#	- the identity element of Hn
function hn_identity(N::Int)
  Id = zeros(Int, N)
	return Id
end

###
# Permutation Constructors
###

# Parameters:
#	N::Int
#   - the dimension of Hn
# Return Values:
#	P::Array{Int, 1}
#	- a random permutation of N
function hn_vertex(N::Int)
  P = rand(0:1, N)
	return P
end

# Parameters:
# N::Int
# - the dimension of Hn
# Index:Int
#   - the index
# Return Values:
#	V::Array{Int, 1}
#	- the vertex corresponding to Index
function index_vertex(N::Int, Index::Int)
  @assert Index < 2^N "dimension $N too small for index $Index"
  V = zeros(Int, N)
  m = 1
  for i = 0:N - 1
    V[i+1] = sign(Index & m)
    m *= 2
  end
	return V
end

# Parameters:
#	V::Array{Int, 1}
#	- a vertex
# Return Value:
#	Index::Int
#	- the unique index that V maps to
function index(V::Array{Int, 1})
	index = 0
  for i = length(V)-1:-1:0
    index = 2*index + V[i+1]
  end
	return index
end
