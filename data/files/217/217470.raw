
module PottsMBMC

	function do_simulation( J::Array{Float64,3},
				h::Array{Float64,2},
				N::Int64,
				q::Int64,
				N_samples::Int64,
				s_init::Int64,
				s_delta::Int64,
				output_prefix::String)

		# Check Input Consistency
		assert(size(J)==(q,q,binomial(N,2)))
		assert(size(h)==(q,N))

		# Check Files for Output
		en_out=string(output_prefix,"_energies")
		sample_out=string(output_prefix,"_samples")
		log_out=string(output_prefix,"_log")
		if isfile(en_out)
			warn("Appending to $en_out")
		end
		if isfile(sample_out)
			warn("Appending to $sample_out")
		end
		if isfile(log_out)
			warn("Appending to $log_out")
		end

		# Running Variables
		state=rand(1:q,N)
		energy=get_energy(state,J,h,N,q)
		acceptance_rate=0.0

		@printf("Energy before thermalization: %.3f\n", energy)
		for s=1:s_init
			i=rand(1:N)
			c=rand(1:q)
			dE=get_energy_difference(state,i,c,J,h,N,q)
			if dE<0.0 || exp(-dE) > rand()
				state[i]=c
				energy+=dE
			end
		end
		@printf("Energy after thermalization: %.3f\n", energy)
		
		for sample=1:N_samples
			for s=1:s_delta
				i=rand(1:N)
				c=rand(1:q)
				dE=get_energy_difference(state,i,c,J,h,N,q)
				if dE<0.0 || exp(-dE) > rand()
					state[i]=c
					energy+=dE
				end
			end
			@printf("\rCurrent sample energy: %.3f",energy)
			write_sample(energy,state,en_out,sample_out,N)
		end
	#/do_simulation
	end

	function write_sample(energy,state,en_out,sample_out,N)
		fid=open(en_out,"a")
		@printf("%f\n",energy)
		close(fid)
		fid=open(sample_out,"a")
		for i=1:N
			@printf("%2d ",state[i])
		end
		@printf("\n")
		close(fid)
	#/write_sample
	end


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

	function get_energy_difference(state::Array{Int64,1},i::Int64,c::Int64,J::Array{Float64,3},h::Array{Float64,2},N::Int64,q::Int64)
		dE= -h[c,i] + h[state[i],i]
		for j=1:i-1
			l = (j-1)*N - binomial(j,2) + j - i
			dE+=( -J[state[j],c,l] + J[state[j],state[i],l] )
		end
		for j=(i+1):N
			l = (j-1)*N - binomial(j,2) + j - i
			dE+=( -J[c,state[j],(i-1)*N+j] + J[state[i],state[j],(i-1)*N+j] )
		end
	#/get_energy_difference
	end

#/module
end



				
