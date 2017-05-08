# Parameters:
#	N::Int
#	- the dimension of Hn
#	M::BigInt
#	- the module
#	PA::Array{Array{Int, 1}, 1}
#	- PA[i] is a vertex
#	VA::Array{Bigint, 1}
#	- VA[i] is the Value associated with PA[i]
# Return Values:
#	HNF::Array{BigInt, 1}
#	- HNF[i] is the value associated with the vertex that permutation_index() maps to i
# Notes:
#	- any vertex of Hn not represented in PA will be assigned a value of zero
function hn_f(N::Int, M::BigInt, PA::Array{Array{Int, 1}, 1}, VA::Array{BigInt, 1})
  HNF = zeros(BigInt, factorial(N))
	for i = 1:length(PA)
		Vertex = PA[i]
		Index = index(Vertex)
		HNF[Index+1] = VA[i] % M
	end
	return HNF
end
