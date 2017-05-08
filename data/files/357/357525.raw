module Photometry

export sum_circle

using Compat

include("overlap.jl")

function sum_circle{T}(data::Array{T, 2}, x::Real, y::Real, r::Real)

    #scale = 1.0 / subpixels
    #scale2 = scale * scale
    #offset = 0.5 * (scale - 1.0)
    r2 = r * r
    
    # Internal and external radius of the oversampled annulus
    # [r-sqrt(2)/2, r+sqrt(2)/2]
    rintlim = r - (sqrt(2.0) / 2.0)
    rintlim2 = rintlim > 0.0 ? rintlim * rintlim : 0.0
    rextlim = r + (sqrt(2.0) / 2.0)
    rextlim2 = rextlim * rextlim

    # Box of pixel positions to consider
    xmin = round(Int, x - r)
    xmax = round(Int, x + r)
    ymin = round(Int, y - r)
    ymax = round(Int, y + r)

    sum = 0.0
    var = 0.0
    area = 0.0
    pixarea = 0.0

    for iy in ymin:ymax
        for ix in xmin:xmax
            dx = ix - x
            dy = iy - y
            ir2 = dx*dx + dy*dy

            (ir2 > rextlim2) && continue  # pixel not in aperture

            if ir2 < rintlim2
                pixarea = 1.0  # pixel fully in aperture
            else
                pixarea = circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, r)
            end

            area += pixarea
            sum += data[x, y] * pixarea
        end
    end

    return sum
end


end # module
