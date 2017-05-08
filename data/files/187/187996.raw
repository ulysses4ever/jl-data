using IDXParser
using Base.Test

# write your own tests here
@test 1 == 1

cwd = Base.dirname(Base.source_path(nothing))

labels = IDXParser.parseIDX("$(cwd)/t10k-labels-idx1-ubyte")

@test typeof(labels) == Array{UInt8, 1}
@test size(labels)   == (10000,)

images = IDXParser.parseIDX("$(cwd)/t10k-images-idx3-ubyte")

@test typeof(images) == Array{UInt8, 3}
@test size(images)   == (10000,28,28)
