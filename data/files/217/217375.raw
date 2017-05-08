
function check_inputs(J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)

	assert(size(J)==(q,q,binomial(N,2)))
	assert(size(h)==(q,N))

end

function check_inputs(J::Array{Float64,3},h::Array{Float64,2},MB_parameters::Array{Float64,1},MB_file::String, N::Int64, q::Int64)

	assert(size(J)==(q,q,binomial(N,2)))
	assert(size(h)==(q,N))
	assert(isfile(MB_file))
	fid=open(MB_file)
	N_lines=countlines(fid)
	assert(N_lines==length(MB_parameters))

end

	

