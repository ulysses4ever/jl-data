
function write_sample(energy::Array{Float64,1},state::Array{Int64,1},en_out::String,sample_out::String,N::Int64)
		fid=open(en_out,"a")
		@printf(fid,"%f\n",energy[1])
		close(fid)
		fid=open(sample_out,"a")
		for i=1:N
			@printf(fid,"%2d ",state[i])
		end
		@printf("\n")
		close(fid)
#/write_sample
end

function define_output_files(output_prefix::String)
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
	return en_out,sample_out,log_out
#/define_output_files
end



