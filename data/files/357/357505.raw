module AperturePhotometry

export sum_circle, sum_circann

using Compat

include("overlap.jl")

# -----------------------------------------------------------------------------

function circbounds(data, x, y, r)
    xmin = max(1, round(Int, x - r))
    xmax = min(size(data, 1), round(Int, x + r))
    ymin = max(1, round(Int, y - r))
    ymax = min(size(data, 2), round(Int, y + r))

    return xmin, xmax, ymin, ymax
end

# Internal and external radius^2 of the oversampled annulus
function oversampann(r)
    rin = r - sqrt(2.0) / 2.0
    rout = r + sqrt(2.0) / 2.0

    return (rin < 0.0 ? 0.0 : rin*rin), rout*rout
end

ismasked(mask::Nothing, x, y, thresh) = false
ismasked{T<:Real}(mask::AbstractArray{T, 2}, x, y, thresh::T) =
    mask[x, y] > thresh

getvar(error::Nothing, x, y) = 0.0
getvar(error::Real, x, y) = @compat Float64(error) * Float64(error)
getvar{T<:Real}(error::AbstractArray{T, 2}, x, y) =
    @compat Float64(error[x, y]) * Float64(error[x, y])


# mask : Nothing or AbstractArray{T, 2}
# error : Nothing, Real, AbstractArray{T, 2}
function sum_circle{T<:Real}(data::AbstractArray{T, 2}, x::Real, y::Real, r::Real;
                             mask=nothing, error=nothing, maskthresh=false, gain=1.0)

    mthresh = convert(eltype(mask), maskthresh)
    r2 = r * r
    rin2, rout2 = oversampann(r)
    xmin, xmax, ymin, ymax = circbounds(data, x, y, r)

    sum, var, area, maskarea, pixarea = 0.0, 0.0, 0.0, 0.0, 0.0
    
    for ypix in ymin:ymax
        for xpix in xmin:xmax
            dx = xpix - x
            dy = ypix - y
            rpix2 = dx*dx + dy*dy

            if rpix2 < rout2
                pixarea = (rpix2 < rin2 ? 1.0 :
                           circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, r))
                if ismasked(mask, xpix, ypix, mthresh)
                    maskarea += pixarea
                else
                    sum += pixarea * data[xpix, ypix]
                    var += pixarea * getvar(error, xpix, ypix)
                    area += pixarea
                end
            end
        end
    end

    if gain > 0.0 && sum > 0.0
        var += sum / gain
    end

    if area > 0.0
        factor = 1.0 + maskarea / area
        sum *= factor
        var *= factor
    end

    return sum, sqrt(var)
end

function sum_circann{T<:Real}(data::AbstractArray{T, 2}, x::Real, y::Real,
                              rin::Real, rout::Real; mask=nothing,
                              error=nothing, maskthresh=false, gain=1.0)

    mthresh = convert(eltype(mask), maskthresh)
    rin2 = rin * rin
    rinin2, rinout2 = oversampann(rin)
    routin2, routout2 = oversampann(rout)
    xmin, xmax, ymin, ymax = circbounds(data, x, y, rout)

    sum, var, area, maskarea, pixarea = 0.0, 0.0, 0.0, 0.0, 0.0
    
    for ypix in ymin:ymax
        for xpix in xmin:xmax
            dx = xpix - x
            dy = ypix - y
            rpix2 = dx*dx + dy*dy

            if rpix2 < routout2 && rpix2 > rinin2
                pixarea = (rpix2 < routin2 ? 1.0 :
                           circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, rout))
                if rpix2 < rinout2
                    pixarea -= circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, rin)
                end

                if ismasked(mask, xpix, ypix, mthresh)
                    maskarea += pixarea
                else
                    sum += pixarea * data[xpix, ypix]
                    var += pixarea * getvar(error, xpix, ypix)
                    area += pixarea
                end
            end
        end
    end

    if gain > 0.0 && sum > 0.0
        var += sum / gain
    end

    if area > 0.0
        factor = 1.0 + maskarea / area
        sum *= factor
        var *= factor
    end

    return sum, sqrt(var)
end


end # module
