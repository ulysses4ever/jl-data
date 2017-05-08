
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

function get_energy( state::Array{Int64,1},
		     J::Array{Float64,3},
		     h::Array{Float64,2},
		     MB_parameters::Array{Float64,1},
		     MB_hd::Array{Int64,1},
		     N::Int64,
		     q::Int64 )
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
	for mb=1:length(MB_hd)
		if MB_hd[mb]==0
			energy-=MB_parameters[mb]
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

function get_energy_difference( state::Array{Int64,1},
				i::Int64,
				c::Int64,
				J::Array{Float64,3},
				h::Array{Float64,2},
				MB_parameters::Array{Float64,1},
				MB_at_site::Array{Array{Int64,1},1},
				MB_colors_at_site::Array{Array{Int8,1},1},
				MB_hd::Array{Int64,1},
				N::Int64,
				q::Int64 )

	dE= -h[c,i] + h[state[i],i]
	for j=1:i-1
		l = (j-1)*N - binomial(j,2) + i - j
		dE+=( -J[state[j],c,l] + J[state[j],state[i],l] )
	end
	for j=(i+1):N
		l = (i-1)*N - binomial(i,2) + j - i
		dE+=( -J[c,state[j],l] + J[state[i],state[j],l] )
	end

	# MB energy contribution
	for k=1:length(MB_at_site[i])
		mb=MB_at_site[mb][k]
		# If the MB_hd[mb] > 1, any change at i cannot lead to a contribution
		MB_hd[mb]>1 && continue
		color=MB_colors_at_site[mb][k]
		# If "c" is "color" && color!=state[i] we know MB_hd[mb] would go 1=>0 by the exchange
		# c!=state[i] is actually handled by propagate! but I want this function to be context independent
		if c==color && color!=state[i]
			dE-=MB_parameters[mb]
			continue
		end
		# If MB_hd[mb]==0 and c!=color we would switch this interaction of
		if MB_hd[mb]==0 && c!=color
			dE+=MB_paramters[mb]
		end
	end
	return dE
#/get_energy_difference
end

function get_MB_hd( state::Array{Int64,1},
		    MB_at_site::Array{Array{Int64,1},1},
		    MB_colors_at_site::Array{Array{Int8,1},1},
		    N_mb::Int64,
		    N::Int64,
		    q::Int64 )

	# MB_hd stores the "Hamming Distance" between the state and the many-body interaction (i.e. how many sites have the correct amino acid for the interaction)
	MB_hd=zeros(Int64,N_mb)
	for i=1:N
		for k=1:length(MB_at_site[i])
			mb=MB_at_site[i][k]
			correct_color=MB_colors_at_site[i][k]
			if state[i]!=correct_color
				MB_hd[mb]+=1
			end
		end
	end
	return MB_hd
end
