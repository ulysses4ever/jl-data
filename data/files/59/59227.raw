module FalseColor
using Devectorize
include("colormaps.jl")

# ColorMap type for regularly spaced colormaps
immutable ColorMapRegular
colors::Array{Float64, 2}
end

# Lookup colors in regularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupindex(cmap::ColorMapRegular, x::Float64)
xi = ceil(x)
w = xi - x
(xi, w)
end

# ColorMap type for irregularly spaced colormaps
immutable ColorMapIrregular
colors::Array{Float64, 2}
x::Vector{Float64}
w::Vector{Float64}
end

# Lookup colors in irregularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupindex(cmap::ColorMapIrregular, x::Float64)
xi = searchsortedlast(cmap.x, x)
@inbounds begin
w = (x - cmap.x[xi]) * cmap.w[xi]
end
(xi, w)
end

# A generic colormap constructor
function ColorMap(table::Array{Float64, 2}, varargs...)
if size(table, 2) < 2
    error("Colormaps require at least 2 entries (2nd dimension");
end
n = size(table, 1)
if n != 3 && n != 4
    error("Colormaps require 2 or 3 channels (1st dimension)")
end
if n == 3
   return ColorMapRegular(table)
else
   w = vec(table[end,1:end-1])
   x = cumsum(w)
   x = [0.0, (x[1:end-1] * (length(x) / x[end]))]
   return ColorMapIrregular(table[1:end-1,:], x, 1.0./w)
end
end

# Determine the data range
function getrange{T<:Real,N}(data::AbstractArray{T,N}, varargs...)
# Check if the range was given as input
for i = 1:length(varargs)
    if (length(range[i]) == 2 && typeof(range[i][1]) <: Real && typeof(range[i][2]) <: Real)
        return (range[i][1], range[i][2])
    end
end
# Compute the range of the data
try
    return extremum(data)
catch
    # Support v0.2
    return (minimum(data), maximum(data))
end
end

function real2rgb!(out_::AbstractArray{Float64, 3}, data::Array{Float64, 2}, cmap::Union(ColorMapRegular,ColorMapIrregular), low::Float64, high::Float64)
# Check the output size
assert(size(out_, 1) == size(data, 1) && size(out_, 2) == size(data, 2) && size(out_, 3) == 3)
out = reshape(out_, length(data), 3)
f = (size(cmap.colors, 2) - 1) / (high - low)
# Go over each pixel
@inbounds begin
for i = 1:length(data)
    if data[i] <= low
        out[i,:] = cmap.colors[:,1]'
    elseif data[i] >= high
        out[i,:] = cmap.colors[:,end]'
    else
        (xi, w) = lookupindex(cmap, (data[i] - low) * f)
        xi_ = xi + 1
        w_ = 1.0 - w
        out[i,1] = cmap.colors[1,xi] * w + cmap.colors[1,xi_] * w_
        out[i,2] = cmap.colors[2,xi] * w + cmap.colors[2,xi_] * w_
        out[i,3] = cmap.colors[3,xi] * w + cmap.colors[3,xi_] * w_
    end
end
end
end

function real2rgb(data::Array{Float64, 2}, cmap::Union(ColorMapRegular,ColorMapIrregular), low::Float64, high::Float64)
out = Array(Float64, size(data, 1), size(data, 2), 3)
real2rgb!(out, data, cmap, low, high)
out
end

function real2rgb{T<:Real,U<:Real}(data::Array{T, 2}, cmap::AbstractArray{U, 2}, varargs...)
# Check for a range
(low, high) = getrange(data, varargs...)
# Do the conversion
real2rgb(convert(Array{Float64, 2}, data), ColorMap(convert(Array{Float64, 2}, cmap)), float64(low), float64(high))
end

function sc!{T<:Real,N}(out::AbstractArray{Float64,3}, data::AbstractArray{T,N}, varargs...)
assert(size(out, 1) == size(data, 1) && size(out, 2) == size(data, 2) && size(out, 3) == 3 && ndims(data) <= 3)
(low, high) = getrange(data, varargs...)
real2rgb!(out, data, ColorMap(jet()), low, high)
end

function sc{T<:Real,N}(data::Array{T,N}, varargs...)
out = Array(Float64, size(data, 1), size(data, 2), 3, size(data)[4:end]...)
n = length(out) / (size(data, 1) * size(data, 2) * 3)
if n == 1
    sc!(out, data, varargs...)
else
    # Do multiple images at once
    for i = 1:n
        sc!(sub(out,:,:,:,i), sub(data,:,:,:,i), varargs...)
    end
end
out
end

# Functions to be visible outside
export real2rgb, real2rgb!, sc, sc!
end
