module ImageIO
using ColorTypes, Compat, FileIO
include("types.jl")

export Image
using ImageMagick
importall ImageMagick, FileIO

#Define backends
FileIO.read(file::readformats(ImageMagick.BACKEND)) = read(file, ImageMagick.BACKEND)

end



