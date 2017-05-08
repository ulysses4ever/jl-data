
function get_energy(state::Array{Int64,1},J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
	energy=0.0
	for i=1:N
		energy-=h[state[i],i]
	end
	l=0
	for i=1:N-1
		for j=(i+1):N
			l+=1
			energy-=J[state[i],state[j],l]
		end
	end
	return energy
#/get_energy
end

function get_energy(state::Array{Int64,1},J::Array{Float64,3},h::Array{Float64,2},MB_parameters::Array{Float64,1},MB_at_site::Array{Array{Int64,1},1},MB_colors_at_site::Array{Array{Int8,1},1},N::Int64,q::Int64)
	energy=0.0
	for i=1:N
		energy-=h[state[i],i]
	end
	l=0
	for i=1:N-1
		for j=(i+1):N
			l+=1
			energy-=J[state[i],state[j],l]
		end
	end
	return energy
#/get_energy
end


function get_energy_difference(state::Array{Int64,1},i::Int64,c::Int64,J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
	dE= -h[c,i] + h[state[i],i]
	for j=1:i-1
		l = (j-1)*N - binomial(j,2) + i - j
		dE+=( -J[state[j],c,l] + J[state[j],state[i],l] )
	end
	for j=(i+1):N
		l = (i-1)*N - binomial(i,2) + j - i
		dE+=( -J[c,state[j],l] + J[state[i],state[j],l] )
	end
	return dE
#/get_energy_difference
end

function get_energy_difference(state::Array{Int64,1},i::Int64,c::Int64,J::Array{Float64,3},h::Array{Float64,2},MB_parameters::Array{Float64,1},MB_at_site::Array{Array{Int64,1},1},MB_colors_at_site::Array{Array{Int8,1},1},N::Int64,q::Int64)
	dE= -h[c,i] + h[state[i],i]
	for j=1:i-1
		l = (j-1)*N - binomial(j,2) + i - j
		dE+=( -J[state[j],c,l] + J[state[j],state[i],l] )
	end
	for j=(i+1):N
		l = (i-1)*N - binomial(i,2) + j - i
		dE+=( -J[c,state[j],l] + J[state[i],state[j],l] )
	end
	return dE
#/get_energy_difference
end

function get_mb_hd(state::Array{Int64,1},MB_at_site::Array{Array{Int64,1},1},MB_colors_at_site::Array{Array{Int8,1},1},N::Int64,q::Int64)
