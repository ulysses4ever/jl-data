#Brian Pomerantz
function reader2bf(file::String, n::Int)
	@assert stat(file).isfile;
	io = open(file, "r");
	
	@assert stat(file) != 0;
	@assert position(io) == 0;

	counter = 0

	while !eof(io) && counter < n
		readline(io);
		counter += 1;
	end

	@assert !eof(io);
	arr = read(io, Float64);
	close(io);
	return arr;
end
