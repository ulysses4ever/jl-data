include("path/lab3_2b.jl");

function printAscii(x::Array)
    x = uint8(x);
    @printf(STDOUT,"%s",ascii(x));
end

function writeASCII(x::Array,file_name)
	open(file_name,"r+");
	x = uint8(x);
	x = ascii(x);
	writecsv(file_name,x);
end

function writeArray(x::Array,file_name)
	open(file_name,"r+");
	writecsv(file_name,x);
end

x = 127*rand(1024);
writeASCII(x,"lab3_2b.txt");
