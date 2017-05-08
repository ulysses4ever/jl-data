function write_arrbin(x::Array, filename::String)
    @assert typeof(x) == Array{Float64,1}
    f = open(filename, "w")
    write(f,x)
    close(f)
end

function read_arrbin(filename::String, size::Int)
    @assert isfile(filename)
    f = open(filename,"r")
    #Nobs is the number of elements in the array
    x = read(f, Array(Float64, size))
    close(f)
    return x
end
