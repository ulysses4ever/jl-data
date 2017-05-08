function readbinary(f::String, dims::Array{Int64, 1}, dt::DataType)
    arr = Array(dt, dims...)
    of = open(f, "r")
    read!(of, arr)
    return arr
end

@time readbinary("data/nireland.dat", [472, 682, 128], Int16)

fp = open("data/nireland.dat", "r")
@time read(fp, Int16, (472, 682, 128))
