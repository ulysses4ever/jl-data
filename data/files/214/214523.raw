using HDF5, JLD

function write_arrhdf5(data::Array, filename::String, varname::String)
    #A function that writes the array **data** to a file **filename** in HDF5 file type format; storing it as a variable **varname**.

    #We need to check if the file is there, as h5write cannot overwrite
    if(isfile(filename))
        rm(filename)
    end
    h5write(filename,varname,data)
end

function read_arrhdf5(filename::String, varname::String)
    #A function that reads the variable **varname** stored in file **filename** 
    @assert isfile(filename)
    return h5read(filename,varname)
end
