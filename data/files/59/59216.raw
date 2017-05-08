module FalseColor
#Using Devectorize
#include("colormaps.jl")

# ColorMap type for regularly spaced colormaps
immutable ColorMapRegular
colors::Array{Float64, 2}
end

# Lookup colors in regularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupcolor(cmap::ColorMapRegular, x::Float64)
@inbounds begin
xi = ceil(x)
w = xi - x
return cmap.colors[:,xi] * w + cmap.colors[:,xi+1] * (1.0 - w)
end
end

# ColorMap type for irregularly spaced colormaps
immutable ColorMapIrregular
colors::Array{Float64, 2}
x::Vector{Float64}
end

# Lookup colors in irregularly spaced colormaps - assumes x is within (0,size(cmap.data, 2)-1)
function lookupcolor(cmap::ColorMapIrregular, x::Float64)
@inbounds begin
xi = searchsortedlast(cmap.x[:,1], x)
w = (x - cmap.x[xi,1]) * cmap.x[xi,2]
return cmap.colors[:,xi] * w + cmap.colors[:,xi+1] * (1.0 - w)
end
end

# A generic colormap constructor
function ColorMap(table::Array{Float64, 2})
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
   x = table[end,1:end-1]
   y = cumsum(x)
   y = [0.0 y[1:end-1] / y[end]]
   return ColorMapIrregular(table[1:end-1,:], [x' y'])
end
end

function real2rgb_(data::Array{Float64, 2}, cmap::Union(ColorMapRegular,ColorMapIrregular), low::Float64, high::Float64)
out = Array(Float64, size(data, 1)*size(data, 2), 3)
f = (size(cmap.colors, 2) - 1) / (high - low)
# Go over each pixel
#@inbounds begin
for i = 1:length(data)
    if data[i] <= low
        out[i,:] = cmap.colors[:,1]'
    elseif data[i] >= high
        out[i,:] = cmap.colors[:,end]'
    else
        out[i,:] = lookupcolor(cmap, (data[i] - low) * f)
    end
end
#end
return reshape(out, size(data, 1), size(data, 2), 3)
end

function real2rgb(data::Array{Float64, 2}, cmap::Array{Float64, 2}, range...)
if length(range) > 0 && length(range[1]) == 2
    low = range[1][1]
    high = range[1][2]
else
    # Compute the range of the data
    try
        (low, high) = extremum(data)
    catch
        (low, high) = (minimum(data), maximum(data))
    end
end
# Do the conversion
real2rgb_(data, ColorMap(cmap), float64(low), float64(high))
end

# Functions to be visible outside
export real2rgb
end
