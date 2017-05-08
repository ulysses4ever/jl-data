doc = 
"""
Reads a flat binary file into an array. Dimensions and data type are
parameters.
"""
function readbinary(f::String, dims::Array{Int64, 1}, dt::DataType)

    # initialize array and element count
    n = reduce(*, dims)
    arr = Array(dt, n)

    # open file and read in values of appropriate data type
    of = open(f)
    for i in 1:n
        arr[i] = read(of, dt)
    end

    # return reshape of flat array we read in
    return arr
#    return reshape(arr, dims...)
end

@time readbinary("data/nireland.dat", [472, 682, 128], Int16)
