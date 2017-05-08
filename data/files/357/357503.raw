module AperturePhotometry

export sum_circle

using Compat

include("overlap.jl")

function sum_circle{T}(data::Array{T, 2},
                       x::Real, y::Real, r::Real)

    r2 = r * r

    # Internal and external radius of the oversampled annulus
    rin = r - (sqrt(2.0) / 2.0)
    rin2 = rin > 0.0 ? rin * rin : 0.0
    rout = r + (sqrt(2.0) / 2.0)
    rout2 = rout * rout

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

            if ir2 < rout2
                pixarea = (ir2 < rin2 ? 1.0 :
                           circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, r))
                area += pixarea
                sum += data[x, y] * pixarea
            end
        end
    end

    return sum
end


# -----------------------------------------------------------------------------

function circbounds(data, x, y, r)
    xmin = max(1, round(Int, x - r))
    xmax = min(size(data, 1), round(Int, x + r))
    ymin = max(1, round(Int, y - r))
    ymax = min(size(data, 2), round(Int, y + r))

    return xmin, xmax, ymin, ymax
end

# helper functions
ismasked{T}(mask::AbstractArray{T, 2}, x, y, thresh::T) = mask[x, y] > thresh
ismasked(mask::Nothing, x, y, thresh) = false

type StDev end
getvariance(error::Nothing, x, y, ::Type{StDev}) = 0.0
getvariance(error::Real, x, y, ::Type{StDev}) =
    @compat Float64(error) * Float64(error)
getvariance{T}(error::AbstractArray{T, 2}, x, y, ::Type{StDev}) =
    @compat Float64(error[x, y]) * Float64(error[x, y])

# 
# mask can be nothing or a 2-d array
# error can be nothing, a Real, or a 2-d array

function sum_circle{T}(data::AbstractArray{T, 2}, mask, error,
                       x::Real, y::Real, r::Real; maskthresh=false, gain=1.0)

    mthresh = convert(eltype(mask), maskthresh)
    r2 = r * r

    # Internal and external radius of the oversampled annulus
    rin = r - sqrt(2.0) / 2.0
    rin2 = rin > 0.0 ? rin * rin : 0.0
    rout = r + sqrt(2.0) / 2.0
    rout2 = rout * rout

    # Box of pixel positions to consider
    xmin, xmax, ymin, ymax = circbounds(data, x, y, r)

    sum = 0.0
    var = 0.0
    area = 0.0
    maskarea = 0.0
    pixarea = 0.0

    for iy in ymin:ymax
        for ix in xmin:xmax
            dx = ix - x
            dy = iy - y
            ir2 = dx*dx + dy*dy

            if ir2 < rout2
                pixarea = (ir2 < rin2 ? 1.0 :
                           circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, r))
                if ismasked(mask, ix, iy, mthresh)
                    maskarea += pixarea
                else
                    area += pixarea
                    sum += data[ix, iy] * pixarea
                    var += pixarea * getvariance(error, ix, iy, StDev)
                end
            end
        end
    end

    # correct masked pixels to average value in non-masked pixels.
    if area > 0.0
        sum *= (maskarea + area) / area
    end

    if gain > 0.0 && sum > 0.0
        var += sum / gain
    end

    return sum, sqrt(var)
end

end # module
