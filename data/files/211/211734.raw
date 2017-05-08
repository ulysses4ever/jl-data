#Brian Pomerantz
function reader2b(file::String)
	@assert stat(file).isfile;

	io = open(file, "r");

	@assert stat(file) != 0;
	@assert position == 0;


	arr = readcsv(file);
	close(io);

	return arr;
end
