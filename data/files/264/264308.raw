module MNISTDataset
# package code goes here

using IDXParser

export parseLabels, parseImages

cwd = Base.dirname(Base.source_path())

@doc """
    Parse the file containing the labels for the digits.
    name: Either "train" or "test"
    multi: Whether or not to make the output vector a vector or an nx10 matrix with each column representing one class for the data (i.e. 7 becomes [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0]
    useBetterValues: Instead of using 0.0 and 1.0 for the above values, use 0.1 and 0.9
""" ->
function parseLabels(name; multi=true, useBetterValues=false)
    file   = Base.joinpath(cwd, "..", "data", "$(name)-labels-idx1-ubyte")
    input  = parseIDX(file)

    if multi
        values = useBetterValues ? [0.1, 0.9] : [0.0, 1.0]
        labels = ones(Float64, (length(input), 10)) .* values[1]

        for i = 1:length(input)
            num            = input[i] == 0 ? 10 : input[i]
            labels[i, num] = values[2]
        end
    else
        labels = input
    end
    
    return labels
end

@doc """
     Parse the file containing the image data for the digits.
     name: Either "train" or "test"
     useDecimal: Transform the value range from 0:255 to 0.0:1.0
     addBias: Add a column to the left-end of the output matrix containing a value for the bias
""" ->
function parseImages(name; useDecimal=true, addBias=false)
    file      = Base.joinpath(cwd, "..", "data", "$(name)-images-idx3-ubyte")
    input     = parseIDX(file)

    numImages = size(input, 1)
    numPixels = prod(size(input)[2:end])
    input_res = reshape(input, (numImages, numPixels))

    if addBias
        bias   = ones(UInt8, (numImages, 1)) .* 255
        input_res = [bias input_res]
    end

    if useDecimal
        images = input_res ./ 255.0
    else
        images = input_res
    end
    
    return images
end

end # module
