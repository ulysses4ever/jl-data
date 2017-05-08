#Brian Pomerantz
function reader2d(file::String)
	@assert stat(file).isfile;
	
	io = open(file, "r");
	@assert !eof(io);
	@assert stat(file).size != 0;
	@assert position(io) == 0;

	arr = [read(io, Float64)];

	while !eof(io)
		 push!(arr, read(io, Float64));
	end

	close(io);

	return arr;
end
