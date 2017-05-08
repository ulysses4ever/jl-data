#Brian Pomerantz
#reads value at position n of binary file
function reader2df(file::String, n::Int)
	@assert isfile(file);
	io = open(file, "r");

	#file is non-empty and at beginning
	@assert !eof(io);
	@assert stat(file) != 0;
	@assert position(io) == 0;

	arr = [read(io, Float64)];

	counter = 0

	while !eof(io) && counter < n
		 read(io, Float64);
		 counter += 1;
	end

	@assert !eof(io);
	arr = read(io, Float64);
	close(io);
	return arr;
end
