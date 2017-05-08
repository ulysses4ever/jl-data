module FalseColor
using Devectorize
include("colormaps.jl")

# ColorMap type for regularly spaced colormaps
immutable ColorMapRegular{T<:FloatingPoint}
colors::Array{T, 2}
end

# Lookup colors in regularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupindex(cmap::ColorMapRegular, x)
xi = ceil(x)
w = xi - x
(xi, w)
end

# ColorMap type for irregularly spaced colormaps
immutable ColorMapIrregular{T<:FloatingPoint}
colors::Array{T, 2}
x::Vector{T}
w::Vector{T}
end

# Lookup colors in irregularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupindex{T<:FloatingPoint}(cmap::ColorMapIrregular{T}, x::T)
xi = searchsortedlast(cmap.x, x)
@inbounds begin
w = (x - cmap.x[xi]) * cmap.w[xi]
end
(xi, w)
end

# Store a colormap plus its range
immutable ColorMapRange
cmap::Union(ColorMapRegular, ColorMapIrregular)
low
high
f

function ColorMapRange(cmap::Union(ColorMapRegular, ColorMapIrregular), low, high)
    T = eltype(cmap.colors)
    new(cmap, convert(T, low), convert(T, high), convert(T, (size(cmap.colors, 2) - 1)) / convert(T, high - low))
end
end

# A generic colormap constructor
function ColorMap{T<:FloatingPoint}(table::Array{T,2}, varargs...)
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

function real2rgb(data::Real, cmap::ColorMapRange)
# Per-pixel conversion
@inbounds begin
data = convert(eltype(cmap.f), data);
if data <= cmap.low
    return cmap.cmap.colors[:,1]
elseif data >= cmap.high
    return cmap.cmap.colors[:,end]
else
    (xi, w) = lookupindex(cmap.cmap, (data - cmap.low) * cmap.f)
    xi_ = xi + 1
    w_ = 1.0 - w
    @devec out = cmap.cmap.colors[:,xi] .* w + cmap.cmap.colors[:,xi_] .* w_
    return out
end
end
end

function real2rgb!{T<:FloatingPoint,U<:Real}(out_::AbstractArray{T,3}, data::Array{U,2}, cmap::ColorMapRange)
# Check the output size
assert(size(out_, 1) == size(data, 1) && size(out_, 2) == size(data, 2) && size(out_, 3) == 3)
out = reshape(out_, length(data), 3)
# Go over each pixel
@inbounds begin
for i = 1:length(data)
    out[i,:] = real2rgb(data[i], cmap)
end
end
end

function real2rgb{T<:Real}(data::Array{T,2}, cmap::ColorMapRange)
out = Array(typeof(cmap.cmap.colors[1]), size(data, 1), size(data, 2), 3)
real2rgb!(out, data, cmap)
out
end

function real2rgb{T<:Real,U<:FloatingPoint}(data::AbstractArray{T,2}, cmap::Array{U,2}, varargs...)
# Check for a range
(low, high) = getrange(data, varargs...)
# Do the conversion
real2rgb(data, ColorMapRange(ColorMap(cmap), low, high))
end

function sc!{T<:FloatingPoint,U<:Number}(out::AbstractArray{T,3}, data::AbstractArray{U,2}, varargs...)
assert(size(out, 1) == size(data, 1) && size(out, 2) == size(data, 2) && size(out, 3) == 3 && ndims(data) <= 3)
(low, high) = getrange(data, varargs...)
real2rgb!(out, data, ColorMapRange(ColorMap(jet()), low, high))
end

function sc{T<:Number}(data::Array{T,2}, varargs...)
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
