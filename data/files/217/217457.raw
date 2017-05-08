
function propagate!(state::Array{Int64,1},energy::Array{Float64,1},J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
	i=rand(1:N)
	c=rand(1:q)
	dE=get_energy_difference(state,i,c,J,h,N,q)
	if dE<0.0 || exp(-dE) > rand()
		state[i]=c
		energy[1]+=dE
	end
end

