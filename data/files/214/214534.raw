
using HDF5, JLD

function write_arrhdf5(data::Array, filename::String, varname::String)
    @assert typeof(data) == Array{Float64,1}
    #We need to check if the file is there, as h5write cannot overwrite
    if(isfile(filename))
        rm(filename)
    end
    h5write(filename,varname,data)
end

function read_arrhdf5(filename::String, varname::String)
    @assert isfile(filename)
    return h5read(filename,varname)
end
