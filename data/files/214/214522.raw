function write_arrbin(x::Array, filename::String)
    #A function that writes the array x to a file **filename** as a binary file
    f = open(filename, "w")
    write(f,x)
    close(f)
end

function read_arrbin(filename::String, size::Int)
    #A function that reads the file **filename**, and returns an array of size **size**
    @assert isfile(filename)
    f = open(filename,"r")
    #Nobs is the number of elements in the array
    x = read(f, Array(Float64, size))
    close(f)
    return x
end
