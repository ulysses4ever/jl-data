
using HDF5, JLD

function write_arrhdf5(data::Array, filename::String, varname::String)
    touch(filename)
    rm(filename)
    h5write(filename,varname,data)
end

function read_arrhdf5(filename::String, varname::String)
    return h5read(filename,varname)
end
