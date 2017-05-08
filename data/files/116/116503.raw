include("/Users/feifeihuang/lab3/lab3_2a.jl");
include("/Users/feifeihuang/lab3/lab3_2b.jl");
include("/Users/feifeihuang/lab3/lab3_2d.jl");
include("/Users/feifeihuang/lab3/lab3_2e.jl");

Pkg.add("HDF5");
using HDF5, JLD;

function readOneAscii(file_name,x::Array,i::Int)
        y = {x[i]};
        print(typeof(y));
        #writeASCII(y,file_name);
        s = open(file_name,"r");
        readcsv(s,ASCIIString)
        close(s);
end

function readOneBinary(file_name,x::Array,i::Int)
        y = {x[i]};
        s = open(file_name,"r");
        #read(s,y);
        close(s);
end

function readOneHDF5(file_name,x::Array,i::Int)
        y = {x[i]};
        #writeHDF5(y,file_name);
        c = jldopen(file_name, "r") do file
            read(file, x)
        end
        close(file);
end

function compare(x::Array,number::Int)
        file_name1 = "/Users/feifeihuang/lab3/file_compare.csv";
        file_name2 = "/Users/feifeihuang/lab3/file_compare.txt";
        file_name3 = "/Users/feifeihuang/lab3/file_compare.jld";
        writeASCII(x,file_name1);
        writeBinary(x,file_name2);
        writeHDF5(x,file_name3);
        n = length(x);
        if (number > n || number<1)
                println("please enter a number in between 1 and ", n);
        else
                println("\n","time to read one element in Ascii = ", @elapsed readOneAscii(file_name1,x,number));
                println("\n","time to read one element in Binary = ", @elapsed readOneBinary(file_name2,x,number));
                println("\n","time to read one element in HDF5 = ", @elapsed readOneHDF5(file_name3,x,number));
        end
end



x = 127*rand(1024);	#create an array of random number from 0 to 127

x = uint8(x);
compare(x,500);
