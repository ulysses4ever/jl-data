
function propagate!(state::Array{Int64,1},energy::Array{Float64,1},J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
	i=rand(1:N)
	c=rand(1:q)
	dE=get_energy_difference(state,i,c,J,h,N,q)
	if dE<0.0 || exp(-dE) > rand()
		state[i]=c
		energy[1]+=dE
	end
end

function propagate!(state::Array{Int64,1},energy::Array{Float64,1},J::Array{Float64,3},h::Array{Float64,2},MB_parameters::Array{Float64,1},MB_sites::Array{Array{Int64,1},1},MB_colors::Array{Array{Int8,1},1},N::Int64,q::Int64)
	i=rand(1:N)
	c=rand(1:q)
	dE=get_energy_difference(state,i,c,J,h,MB_parameters,MB_sites,MB_colors,N,q)
	if dE<0.0 || exp(-dE) > rand()
		state[i]=c
		energy[1]+=dE
	end
end


