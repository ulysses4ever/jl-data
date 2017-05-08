include("/Users/feifeihuang/lab3/lab3_2a.jl");
include("/Users/feifeihuang/lab3/lab3_2b.jl");
include("/Users/feifeihuang/lab3/lab3_2d.jl");
include("/Users/feifeihuang/lab3/lab3_2e.jl");

using Base.Test
x = 127*rand(10);	#create an array of random number from 0 to 127
x = uint8(x);
file_name1 = "/Users/feifeihuang/lab3/file_compare.csv";
file_name2 = "/Users/feifeihuang/lab3/file_compare.txt";
file_name3 = "/Users/feifeihuang/lab3/file_compare.jld";
@test isa(x,Array);
@test isa(convertToAscii(x),ASCIIString);
@test isa(writeASCII(x,file_name1),Nothing);
@test isa(readASCII(file_name1),Nothing);
@test isa(writeBinary(x,file_name2),Nothing);
@test isa(readBinary(file_name2),Nothing);
@test isa(writeHDF5(x,file_name3),Nothing);
@test isa(readHDF5(file_name3),Nothing);
