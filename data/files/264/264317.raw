using MNISTDataset
using Base.Test

# write your own tests here
@test 1 == 1

labels = parseLabels("test")
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (10000, 10)
@test labels[1,1]    == 0.0
@test labels[1,7]    == 1.0

labels = parseLabels("test", multi=true)
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (10000, 10)
@test labels[1,1]    == 0.0
@test labels[1,7]    == 1.0

labels = parseLabels("test", multi=false)
@test typeof(labels) == Array{UInt8, 1}
@test size(labels)   == (10000,)
@test labels[1]      == 0x07

labels = parseLabels("test", useBetterValues=true)
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (10000, 10)
@test labels[1,1]    == 0.1
@test labels[1,7]    == 0.9

labels = parseLabels("test", useBetterValues=false)
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (10000, 10)
@test labels[1,1]    == 0.0
@test labels[1,7]    == 1.0

labels = parseLabels("test", multi=true, useBetterValues=true)
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (10000, 10)
@test labels[1,1]    == 0.1
@test labels[1,7]    == 0.9

labels = parseLabels("test", multi=false, useBetterValues=true)
@test typeof(labels) == Array{UInt8, 1}
@test size(labels)   == (10000,)
@test labels[1]      == 0x07

labels = parseLabels("test", multi=false, useBetterValues=false)
@test typeof(labels) == Array{UInt8, 1}
@test size(labels)   == (10000,)
@test labels[1]      == 0x07

labels = parseLabels("train")
@test typeof(labels) == Array{Float64, 2}
@test size(labels)   == (60000, 10)

images = parseImages("test")
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0.0
@test images[1, 3]   == 0.9921568627450981

images = parseImages("test"; useDecimal=true)
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0.0
@test images[1, 3]   == 0.9921568627450981

images = parseImages("test"; useDecimal=false)
@test typeof(images) == Array{UInt8, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0x00
@test images[1, 3]   == 0xfd

images = parseImages("test"; addBias=true)
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 785)
@test images[1, 1]   == 1.0
@test images[1, 2]   == 0.0
@test images[1, 4]   == 0.9921568627450981

images = parseImages("test"; addBias=false)
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0.0
@test images[1, 3]   == 0.9921568627450981

images = parseImages("test"; useDecimal=true, addBias=true)
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 785)
@test images[1, 1]   == 1.0
@test images[1, 2]   == 0.0
@test images[1, 4]   == 0.9921568627450981

images = parseImages("test"; useDecimal=true, addBias=false)
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0.0
@test images[1, 3]   == 0.9921568627450981

images = parseImages("test"; useDecimal=false, addBias=true)
@test typeof(images) == Array{UInt8, 2}
@test size(images)   == (10000, 785)
@test images[1, 1]   == 0xff
@test images[1, 2]   == 0x00
@test images[1, 4]   == 0xfd

images = parseImages("test"; useDecimal=false, addBias=false)
@test typeof(images) == Array{UInt8, 2}
@test size(images)   == (10000, 784)
@test images[1, 1]   == 0x00
@test images[1, 3]   == 0xfd

images = parseImages("train")
@test typeof(images) == Array{Float64, 2}
@test size(images)   == (60000, 784)
@test images[1, 1]   == 0.0
@test images[1, 782] == 0.5333333333333333
