#Brian Pomerantz
#reads array from binary file
function reader2d(file::String)
	@assert isfile(file); #ensures file exists
	
	io = open(file, "r");

	#ensures file is non-empty and at beginning
	@assert !eof(io);
	@assert stat(file).size != 0;
	@assert position(io) == 0;

	arr = [read(io, Float64)];

	while !eof(io)
		 push!(arr, read(io, Float64));
	end
	
	@assert eof(io); #ensures read all of file

	close(io);

	return arr;
end
