module CVImgProc

export ColorConversionCodes, ThresholdTypes, cvtColor, resize, threshold,
    flip!, flip, undistort!, undistort

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
function flip(src::AbstractCvMat, flip_mode)
    dst = similar_empty(src)
    flip!(src, dst, flip_mode)
    dst
end

# TODO
noArray() = icxx"cv::noArray();"

function undistort!{T<:AbstractCvMat}(src::T, dst::T,
        cameraMatrix::AbstractCvMat, distCoeffs::AbstractCvMat,
        newCameraMatrix=noArray())
    icxx"cv::undistort($(src.handle), $(dst.handle), $(cameraMatrix.handle),
        $(distCoeffs.handle), $newCameraMatrix);"
end
function undistort!(src::AbstractCvMat, cameraMatrix::AbstractCvMat,
        distCoeffs::AbstractCvMat, newCameraMatrix=noArray())
    undistort!(src, src, cameraMatrix, distCoeffs, newCameraMatrix)
end
function undistort(src::AbstractCvMat, cameraMatrix::AbstractCvMat,
        distCoeffs::AbstractCvMat, newCameraMatrix=noArray())
    dst = similar_empty(src)
    undistort!(src, dst, cameraMatrix, distCoeffs, newCameraMatrix)
    dst
end

end # module
