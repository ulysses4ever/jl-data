include("/Users/feifeihuang/lab3/lab3_2b.jl");

function printAscii(x::Array)
    x = uint8(x);
    @printf(STDOUT,"%s",ascii(x));
end

function writeASCII(x::Array,file_name)
	open(file_name,"r+");
	x = uint8(x);
	x = ascii(x);
        #writecsv(file_name,x);
end

function writeArray(x::Array,file_name)
	open(file_name,"r+");
	writecsv(file_name,x);
end

x = 127*rand(1024);
open("/Users/feifeihuang/lab3_2b.txt","r+");
#writeASCII(x,"lab3_2b.txt");
#writeArray(x,"lab3_2b.txt");
