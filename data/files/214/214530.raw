function write_arrbin(x::Array, filename::String)
    f = open(filename, "w")
    write(f,x)
    close(f)
end

function read_arrbin(filename::String, size)
    f = open(filename,"r")
    #Nobs is the number of elements in the array
    x = read(f, Array(Float64, size))
    close(f)
    return x
end
