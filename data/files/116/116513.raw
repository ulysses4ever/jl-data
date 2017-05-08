Pkg.add("HDF5")
using HDF5, JLD

function writeHDF5(x::Array,file_name)
        @assert(isa(x,Array));
        #@save file_name x
        file = jldopen(file_name,"w");
        @write file x;
        close(file);
end

function readHDF5(file_name)
        file = jldopen(file_name,"r");
        read(file);
        close(file);
end

function getTime()
    x = 127*rand(1024);	#create an array of random number from 0 to 127
    x = uint8(x);
    file_name = "/Users/feifeihuang/lab3/file_hdf5.jld";
    writeHDF5(x,file_name);
    readHDF5(file_name);
    println("time to write in hdf5 to file = ", @elapsed writeHDF5(x,file_name));
    println("time to read in hdf5 from file = ", @elapsed readHDF5(file_name));
    println("time to read in hdf5 from file = ", @elapsed readHDF5(file_name));
    println("time to read in hdf5 from file = ", @elapsed readHDF5(file_name));
end

#getTime()
