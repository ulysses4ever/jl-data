
function propagate!(state::Array{Int64,1},energy::Array{Float64,1},J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
	i=rand(1:N)
	c=rand(1:q)
	while(c==state[i])
		c=rand(1:q)
	end
	dE=get_energy_difference(state,i,c,J,h,N,q)
	if dE<0.0 || exp(-dE) > rand()
		state[i]=c
		energy[1]+=dE
	end
end

function propagate!(state::Array{Int64,1},energy::Array{Float64,1},J::Array{Float64,3},h::Array{Float64,2},MB_parameters::Array{Float64,1},MB_at_site::Array{Array{Int64,1},1},MB_colors_at_site::Array{Array{Int8,1},1},MB_hd::Array{Int64,1},N::Int64,q::Int64)
	i=rand(1:N)
	c=rand(1:q)
	while(c==state[i])
		c=rand(1:q)
	end
	dE=get_energy_difference(state,i,c,J,h,MB_parameters,MB_at_site,MB_colors_at_site,MB_hd,N,q)
	if dE<0.0 || exp(-dE) > rand()
		for k=1:length(MB_at_site[i])
			mb=MB_at_site[i][k]
			color=MB_colors_at_site[i][k]
			if color==c && state[i]!=color
				# The new color "c" is the correct color
				MB_hd[mb]-=1
			elseif state[i]==color && c!=color
				# The old color "state[i]" was the correct color
				MB_hd[mb]+=1
			end
		end
		state[i]=c
		energy[1]+=dE
	end
end


