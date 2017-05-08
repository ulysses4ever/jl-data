module PottsMBMC
	
	include("io.jl")
	include("check_inputs.jl")
	include("propagate.jl")
	include("energy_functions.jl")
	include("analyze_MC.jl")

	function do_simulation( J::Array{Float64,3},
				h::Array{Float64,2},
				MB_parameters::Array{Float64,2},
				MB_file::AbstractString,
				N::Int64,
				q::Int64,
				N_samples::Int64,
				s_init::Int64,
				s_delta::Int64,
				output_prefix::AbstractString)

		
		check_inputs(MB_file,MB_parameters,N)
		warn("Selecting many-body parameters automatically")
		MB_parameters=select_MB_parameters(MB_file,MB_parameters)

		do_simulation(J,h,MB_parameters,MB_file,N,q,N_samples,s_init,s_delta,output_prefix)
	end


	function do_simulation( J::Array{Float64,3},
				h::Array{Float64,2},
				MB_parameters::Array{Float64,1},
				MB_file::AbstractString,
				N::Int64,
				q::Int64,
				N_samples::Int64,
				s_init::Int64,
				s_delta::Int64,
				output_prefix::AbstractString)

		check_inputs(J,h,MB_parameters,MB_file,N,q)
		en_out,sample_out,log_out = define_output_files(output_prefix)
		MB_at_site,MB_colors_at_site=parse_MB_file(MB_file,N,q)
		
		
		state=rand(1:q,N)
		MB_hd=get_MB_hd(state,MB_at_site,MB_colors_at_site,length(MB_parameters),N,q)
		energy=[get_energy(state,J,h,MB_parameters,MB_hd,N,q)]
		acceptance_rate=0.0

		@printf("Energy before thermalization: %.3f\n", energy[1])

		for s=1:s_init
			propagate!(state,energy,J,h,MB_parameters,MB_at_site,MB_colors_at_site,MB_hd,N,q)
		end

		@printf("Energy after thermalization: %.3f\n", energy[1])
		
		for sample=1:N_samples
			for s=1:s_delta
				propagate!(state,energy,J,h,MB_parameters,MB_at_site,MB_colors_at_site,MB_hd,N,q)
			end
			@printf("\rCurrent sample energy: %.3f",energy[1])
			write_sample(energy,state,en_out,sample_out,N)
		end

		energy=[get_energy(state,J,h,MB_parameters,MB_hd,N,q)]
	#/do_simulation
	end


	function do_simulation( J::Array{Float64,3},
				h::Array{Float64,2},
				N::Int64,
				q::Int64,
				N_samples::Int64,
				s_init::Int64,
				s_delta::Int64,
				output_prefix::AbstractString)
		

		check_inputs(J,h,N,q)
		en_out,sample_out,log_out = define_output_files(output_prefix)
		
		state=rand(1:q,N)
		energy=[get_energy(state,J,h,N,q)]
		acceptance_rate=0.0

		@printf("Energy before thermalization: %.3f\n", energy[1])

		for s=1:s_init
			propagate!(state,energy,J,h,N,q)
		end

		@printf("Energy after thermalization: %.3f\n", energy[1])
		
		for sample=1:N_samples
			for s=1:s_delta
				propagate!(state,energy,J,h,N,q)
			end
			@printf("\rCurrent sample energy: %.3f",energy[1])
			write_sample(energy,state,en_out,sample_out,N)
		end
	#/do_simulation
	end

	function do_simulation( J::Array{Float64,3},
				h::Array{Float64,2},
				N::Int64,
				q::Int64,
				N_samples::Int64,
				s_init::Int64,
				s_delta::Int64)
				
		

		check_inputs(J,h,N,q)
		
		state=rand(1:q,N)
		energy=[get_energy(state,J,h,N,q)]
		acceptance_rate=0.0

		#@printf("Energy before thermalization: %.3f\n", energy[1])

		for s=1:s_init
			propagate!(state,energy,J,h,N,q)
		end

		#@printf("Energy after thermalization: %.3f\n", energy[1])
		
		Z=Array(Int8,N_samples,N)
		
		for sample=1:N_samples
			for s=1:s_delta
				propagate!(state,energy,J,h,N,q)
			end
			#@printf("\rCurrent sample energy: %.3f",energy[1])
			for i=1:N
				Z[sample,i]=state[i]
			end
		end
		return Z
	#/do_simulation
	end

#/module
end



				
