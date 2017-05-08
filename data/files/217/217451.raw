
function write_sample(energy::Array{Float64,1},state::Array{Int64,1},en_out::String,sample_out::String,N::Int64)
		fid=open(en_out,"a")
		@printf(fid,"%f\n",energy[1])
		close(fid)
		fid=open(sample_out,"a")
		for i=1:N
			@printf(fid,"%2d ",state[i])
		end
		@printf(fid,"\n")
		close(fid)
#/write_sample
end

function select_MB_parameters(MB_file::String,MB_parameters::Array{Float64,2})

	new_MB_parameters=zeros(Float64,size(MB_parameters,1))
	counter=zeros(Int64,size(MB_parameters,1))
	fid=open(MB_file)
	mb=0
	for line in eachline(fid)
		mb+=1
		line_data=int(split(chomp(line)))
		for k=1:div(length(line_data),2)
			site=line_data[2*k-1]
			new_MB_parameters[mb]+=MB_parameters[mb,site]
			counter[mb]+=1
		end
	end
	close(fid)
	for mb=1:length(counter)
		new_MB_parameters[mb]/=counter[mb]
	end
	return new_MB_parameters
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

function parse_MB_file(MB_file::String,N::Int64,q::Int64)
	
	MB_sites,MB_colors=get_MB_sites_MB_colors(MB_file,N,q)

	MB_at_site=Array(Array{Int64,1},N)
	MB_colors_at_site=Array(Array{Int8,1},N)
	for i=1:N
		MB_at_site[i]=zeros(Int64,0)
		MB_colors_at_site[i]=zeros(Int64,0)
	end
	for mb=1:length(MB_sites)
		for k=1:length(MB_sites[mb]) 
			push!(MB_at_site[MB_sites[mb][k]],mb)
			push!(MB_colors_at_site[MB_sites[mb][k]],MB_colors[mb][k])
		end
	end
	return MB_at_site,MB_colors_at_site
end

function get_MB_sites_MB_colors(MB_file::String,N::Int64,q::Int64)
	
	MB_sites=Array(Array{Int64,1},0)
	MB_colors=Array(Array{Int8,1},0)
	fid=open(MB_file)
	for line in eachline(fid)
		params=int(split(chomp(line)))
		if !iseven(length(params))
			close(fid)
			error("Cannot read MB_file")
		end
		N_mb=div(length(params),2)
		sites=Array(Int64,N_mb)
		colors=Array(Int64,N_mb)
		for l=1:N_mb
			site=params[2*l-1]
			assert(site > 0 && site <= N)
			color=params[2*l]
			assert(color >= -q && color <= q && color!=0)
			sites[l]=site
			colors[l]=color
		end
		push!(MB_sites,sites)
		push!(MB_colors,colors)
	end
	close(fid)
	return MB_sites,MB_colors
end

