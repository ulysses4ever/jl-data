module CVImgProc

export ColorConversionCodes, ThresholdTypes, cvtColor, resize, threshold,
    flip!, flip

using LibOpenCV
using CVCore
using Cxx

import CVCore: cvSize, similar_empty

libopencv_imgproc = LibOpenCV.find_library_e("libopencv_imgproc")
try
    Libdl.dlopen(libopencv_imgproc, Libdl.RTLD_GLOBAL)
catch e
    warn("You might need to set DYLD_LIBRARY_PATH to load dependencies proeprty.")
    rethrow(e)
end

cxx"""
#include <opencv2/imgproc.hpp>
"""

typealias ColorConversionCodes Cxx.CppEnum{Symbol("cv::ColorConversionCodes"),UInt32}
typealias ThresholdTypes Cxx.CppEnum{Symbol("cv::ThresholdTypes"),UInt32}

include("const.jl")

function cvtColor(src::AbstractCvMat, code::Integer)
    dst = similar_empty(src)
    icxx"cv::cvtColor($(src.handle), $(dst.handle), $code);"
    # Since cvtColor may changes its type (e.g.
    # Mat{Float64,3} -> Mat{Float64,2} when code=COLOR_RGB2GRAY)
    # retype from its value
    return Mat(dst.handle)
end
cvtColor(src::AbstractCvMat, code::ColorConversionCodes) = cvtColor(src, code.val)

function resize(src::AbstractCvMat, shape::NTuple{2})
    w, h = shape
    s = cvSize(w, h)
    return resize(src, s)
end

function resize(src::AbstractCvMat, s::cvSize)
    dst = similar_empty(src)
    icxx"cv::resize($(src.handle), $(dst.handle), $s);"
    return dst
end

function threshold(src::AbstractCvMat, thresh, maxval, typ::Integer)
    dst = similar_empty(src)
    icxx"cv::threshold($(src.handle), $(dst.handle), $thresh, $maxval, $typ);"
    return dst
end
threshold(src::AbstractCvMat, thresh, maxval, typ::ThresholdTypes) =
    threshold(src, thresh, maxval, typ.val)

function flip!(src::AbstractCvMat, dst::AbstractCvMat, flip_mode)
    icxx"cv::flip($(src.handle), $(dst.handle), $flip_mode);"
    return src
end
flip!(src::AbstractCvMat, flip_mode) = flip!(src, src, flip_mode)
flip(src::AbstractCvMat, flip_mode) = flip(src, similar_empty(src), flip_mode)

end # module
