#Brian Pomerantz
#reads element at position n of ASCII file
function reader2bf(file::String, n::Int)
	@assert isfile(file); #file exists
	io = open(file, "r");
	
	#file non-empty and at beginning
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
