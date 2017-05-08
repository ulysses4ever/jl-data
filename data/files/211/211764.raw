#Brian Pomerantz
#Writes array to file in ASCII format
function writer2b(file::String, arr::Array)
	io = open(file, "w");
	@assert position(io) == 0;  #ensures that stream is at the beginning of the file

	writecsv(file, arr);
	close(io);
end
