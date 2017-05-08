module ImageIO
using ColorTypes
using Compat
using FileIO
using ImageMagick
using FixedPointNumbers

importall ImageMagick, FileIO, Base

include("types.jl")

export Image
export AbstractImage
export colorspace
export colordim
export grayim
export colorim
export ImageCmap
export copyproperties
export shareproperties
export raw
export separate
export getindexim
export ImageCmap
export ImageCmap
#Define backends
FileIO.read(file::readformats(ImageMagick.BACKEND)) = read(file, ImageMagick.BACKEND)

end



