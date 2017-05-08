#Brian Pomerantz
#reades array from ASCII file
function reader2b(file::String)
	@assert isfile(file); #ensures file exists

	io = open(file, "r");
	
	#ensures non-empty file and at beginning
	@assert stat(file) != 0;
	@assert position(io) == 0;


	arr = readcsv(file);
	
	@assert eof(io); #ensures that reader read entire file
	close(io);

	return arr;
end
