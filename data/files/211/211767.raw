#Brian Pomerantz
#writes array to file in binary format
function writer2d(file::String, arr::Array)
	io = open(file, "w");
	@assert position(io) == 0; #ensures at beginning of file
	write(io, arr);
	close(io);
end
