function read_arr(inputname::String)
    @assert isfile(inputname)
    return readcsv(inputname)
end

function write_arr(x::Array, filename::String)
    @assert typeof(x) == Array{Float64,1}
    writecsv(filename, x)
end

