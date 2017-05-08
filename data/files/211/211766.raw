#Brian Pomerantz
function writer2d(file::String, arr::Array)
	io = open(file, "w");
	@assert position(io) == 0;
	write(io, arr);
	close(io);
end
