#Brian Pomerantz
function reader2df(file::String, n::Int)
	@assert stat(file).isfile;
	io = open(file, "r");
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
