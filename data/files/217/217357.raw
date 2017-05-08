function get_p3_from_mc(dir::String,reg::Regex,N::Int64,q::Int64)
	files=readdir(dir)
	filter!(reg,files)
	for k=1:length(files)
		files[k]=dir*"/"*files[k]
	end
	nr_seqs=0
	for file in files
		fid=open(file)
		nr_seqs+=countlines(fid)
		close(fid)
	end
	MSA=SharedArray(Int8,nr_seqs,N)
	seq=0
	for file in files
		fid=open(file)
		for line in eachline(fid)
			seq+=1
			line_data=int(split(chomp(line)))
			if length(line_data) != N 
				error("Cannot read $file")
			end	
			for i=1:N
				MSA[seq,i]=line_data[i]
			end
		end
	end
	assert(seq==nr_seqs)
	
	@printf("Allocating")
	p3mc=SharedArray(Float64,q,q,q,div(N*(N-1)*(N-2),6))
	for l=1:length(p3mc)
		p3mc[l]=0.0
	end
	@printf("..done\n")

	@sync @parallel for l=1:size(p3mc,4)
		fill_l!(l,MSA,p3mc,N,q)
	end
	println("Couning done")
	for k=1:length(p3mc)
		p3mc[k]==0.0 && continue
		p3mc[k]/=nr_seqs
	end
	return sdata(p3mc)
end

function get_p2_from_mc(dir::String,reg::Regex,N::Int64,q::Int64)
	files=readdir(dir)
	filter!(reg,files)
	for k=1:length(files)
		files[k]=dir*"/"*files[k]
	end
	nr_seqs=0
	for file in files
		fid=open(file)
		nr_seqs+=countlines(fid)
		close(fid)
	end
	MSA=SharedArray(Int8,nr_seqs,N)
	seq=0
	for file in files
		fid=open(file)
		for line in eachline(fid)
			seq+=1
			line_data=int(split(chomp(line)))
			if length(line_data) != N 
				error("Cannot read $file")
			end	
			for i=1:N
				MSA[seq,i]=line_data[i]
			end
		end
	end
	assert(seq==nr_seqs)
	
	@printf("Allocating")
	p2mc=SharedArray(Float64,q,q,div(N*(N-1),2))
	for l=1:length(p2mc)
		p2mc[l]=0.0
	end
	@printf("..done\n")

	@sync @parallel for l=1:size(p2mc,3)
		fill_l!(l,MSA,p2mc,N,q)
	end
	println("Counting done")
	for k=1:length(p2mc)
		p2mc[k]==0.0 && continue
		p2mc[k]/=nr_seqs
	end
	return sdata(p2mc)
end

function fill_l!(l::Int64,MSA::SharedArray{Int8,2},p2mc::SharedArray{Float64,3},N::Int64,q::Int64)
	(i,j)=revInd2(l,N)
	for m=1:size(MSA,1)
		p2mc[MSA[m,i],MSA[m,j],l]+=1.0
	end
end

function fill_l!(l::Int64,MSA::SharedArray{Int8,2},p3mc::SharedArray{Float64,4},N::Int64,q::Int64)
	(i,j)=revInd2(l,N)
	for m=1:size(MSA,1)
		p3mc[MSA[m,i],MSA[m,j],MSA[m,k],l]+=1.0
	end
end

		
function ind3(i::Int64,j::Int64,k::Int64,N::Int64)

        ind=0.5*((i-1)*(N^2-N) - (2*N-1)*(binomial(i,2)) + (2*(i-1)^3 + 3*(i-1)^2 + i - 1)/6)+(j-i)*(N-0.5*(j+i+1)) - N + k
        return int(ind)

        # Works as well return sum([binomial(N-k,2) for k=1:i-1]) + (j-i)*(N-0.5*(j+i+1)) - N + k
end

function revInd3(l::Int64,N::Int64)
        i=1
        while l>ind3(i,N-1,N,N)
                i+=1
        end
        j=i+1
        while l>ind3(i,j,N,N)
                j+=1
        end
        k=N+l-ind3(i,j,N,N)

        return i,j,k
end

function ind2(i::Int64,j::Int64,N::Int64)
        l=(i-1)*N - binomial(i,2) + j - i
end

function revInd2(l::Int64,N::Int64)
        i=1
        while l>ind2(i,N,N)
                i+=1
        end
        j=l-ind2(i-1,N,N)+i
        return i,j
end

function get_MB_freq_from_MC(dir::String,reg::Regex,MBfile::String,N::Int64,q::Int64)

	MB_sites,MB_colors=get_MB_sites_MB_colors(MBfile,N,q)
	nr_MB=length(MB_sites)

	files=readdir(dir)
	filter!(reg,files)
	for k=1:length(files)
		files[k]=dir*"/"*files[k]
	end

	nr_seqs=0
	MB_freq=zeros(Float64,nr_MB)
	for file in files
		fid=open(file)
		for line in eachline(fid)
			nr_seqs+=1
			line_data=int(split(chomp(line)))
			if length(line_data) != N 
				error("Cannot read $file")
			end	
			for mb=1:length(MB_sites)
				line_data[MB_sites[mb]]!=MB_colors[mb] && continue
				MB_freq[mb]+=1.0

			end
		end
	end
	for l=1:length(MB_freq)
		MB_freq[l]/=float(nr_seqs)
	end
	return MB_freq
end

