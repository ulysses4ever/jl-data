#Brian Pomerantz
function writer2b(file::String, arr::Array)
	io = open(file, "w");
	@assert position(io) == 0;

	writecsv(file, arr);
	close(io);
end
