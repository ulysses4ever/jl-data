module AperturePhotometry

using Compat

export sum_circle, sum_circann, sum_ellipse

include("overlap.jl")

abstract Shape

immutable Circle <: Shape
    x::Float64
    y::Float64
    r::Float64
    Circle(x::Real, y::Real, r::Real) =
        @compat new(Float64(x), Float64(y), Float64(r))
end

immutable CircAnn <: Shape
    x::Float64
    y::Float64
    rin::Float64
    rout::Float64
    rinin2::Float64
    rinout2::Float64
    routin2::Float64
    routout2::Float64
    function CircAnn(x::Real, y::Real, rin::Real, rout::Real)
        rinin2, rinout2 = oversampann(rin)
        routin2, routout2 = oversampann(rout)
        @compat new(Float64(x), Float64(y), Float64(rin), Float64(rout),
                    rinin2, rinout2, routin2, routout2)
    end
end

immutable Ellipse <: Shape
    x::Float64
    y::Float64
    a::Float64
    b::Float64
    theta::Float64
    cxx::Float64
    cyy::Float64
    cxy::Float64
    function Ellipse(x::Real, y::Real, a::Real, b::Real, theta::Real)
        if (b < 0.0 || a < b || theta < -pi/2.0 || theta > pi/2.0)
            error("illegal ellipse parameters. " *
                  "Require a >= b >= 0.0, -pi/2 <= theta <= pi/2")
        end
        cxx, cyy, cxy = ellipse_coeffs(a, b, theta)
        @compat new(Float64(x), Float64(y), Float64(a), Float64(b),
                    Float64(theta), cxx, cyy, cxy)
    end
end

function ellipse_coeffs(a, b, theta)
    costheta = cos(theta)
    sintheta = sin(theta)
    cxx = costheta*costheta/(a*a) + sintheta*sintheta/(b*b)
    cyy = sintheta*sintheta/(a*a) + costheta*costheta/(b*b)
    cxy = 2.*costheta*sintheta * (1./(a*a) - 1./(b*b))
    return cxx, cyy, cxy
end

# Internal and external radius^2 of the oversampled annulus
@inline function oversampann(r)
    rin = r - sqrt(2.0) / 2.0
    rout = r + sqrt(2.0) / 2.0
    return (rin < 0.0 ? 0.0 : rin*rin), rout*rout
end

@inline function oversampann_ellipse(b)
    rin = 1.0 - (sqrt(2.0) / 2.0) / b
    rout = 1.0 + (sqrt(2.0) / 2.0) / b
    return (rin > 0.0 ? rin*rin : 0.0), rout * rout
end

ismasked(mask::Nothing, x, y, thresh) = false
ismasked{T<:Real}(mask::AbstractArray{T, 2}, x, y, thresh::T) =
    mask[x, y] > thresh

getvar(error::Nothing, x, y) = 0.0
getvar(error::Real, x, y) = @compat Float64(error) * Float64(error)
getvar{T<:Real}(error::AbstractArray{T, 2}, x, y) =
    @compat Float64(error[x, y]) * Float64(error[x, y])

function box_bounds(data, x, y, dx, dy)
    xmin = max(1, round(Int, x - dx))
    xmax = min(size(data, 1), round(Int, x + dx))
    ymin = max(1, round(Int, y - dy))
    ymax = min(size(data, 2), round(Int, y + dy))
    return xmin, xmax, ymin, ymax
end

function box_bounds_ellipse(data, x, y, cxx, cyy, cxy)
    dx = cxx - cxy * cxy / (4.0 * cyy)
    dx = dx > 0.0 ? 1.0/sqrt(dx) : 0.0
    dy = cyy - cxy * cxy / (4.0 * cxx)
    dy = dy > 0.0 ? 1.0/sqrt(dy) : 0.0
    return box_bounds(data, x, y, dx, dy)
end

box_bounds(data, c::Circle) = box_bounds(data, c.x, c.y, c.r, c.r)
box_bounds(data, c::CircAnn) = box_bounds(data, c.x, c.y, c.rout, c.rout)
box_bounds(data, e::Ellipse) = box_bounds_ellipse(data, e.x, e.y, e.cxx, e.cyy,
                                                  e.cxy)

@inline function overlap(c::Circle, xpix::Int, ypix::Int)
    dx = xpix - c.x
    dy = ypix - c.y
    rpix2 = dx*dx + dy*dy

    rin2, rout2 = oversampann(c.r)

    if rpix2 > rout2
        return 0.0
    elseif rpix2 < rin2
        return 1.0
    else
        return circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, c.r)
    end
end

@inline function overlap(c::CircAnn, xpix::Int, ypix::Int)
    dx = xpix - c.x
    dy = ypix - c.y
    rpix2 = dx*dx + dy*dy

    if rpix2 > c.routout2 || rpix2 < c.rinin2
        return 0.0
    end

    pixarea = (rpix2 < c.routin2 ? 1.0 :
               circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, c.rout))
    if rpix2 < c.rinout2
        pixarea -= circoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, c.rin)
    end

    return pixarea
end

@inline function overlap(e::Ellipse, xpix::Int, ypix::Int)
    dx = xpix - e.x
    dy = ypix - e.y
    rpix2 = e.cxx*dx*dx + e.cyy*dy*dy + e.cxy*dx*dy
    rin2, rout2 = oversampann_ellipse(e.b)
    if rpix2 > rout2
        return 0.0
    elseif rpix2 < rin2
        return 1.0
    else
        return ellipoverlap(dx-0.5, dy-0.5, dx+0.5, dy+0.5, e.a, e.b, e.theta)
    end
end

function sum_shape{T<:Real}(data::AbstractArray{T, 2}, shape::Shape;
                            mask=nothing, error=nothing,
                            maskthresh=false, gain=1.0)

    mthresh = convert(eltype(mask), maskthresh)
    xmin, xmax, ymin, ymax = box_bounds(data, shape)
    sum, var, area, maskarea, pixarea = 0.0, 0.0, 0.0, 0.0, 0.0

    @inbounds for ypix in ymin:ymax
        for xpix in xmin:xmax
            pixarea = overlap(shape, xpix, ypix)
            if pixarea > 0.0
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

sum_circle{T<:Real}(data::AbstractArray{T, 2}, x::Real, y::Real, r::Real;
                    mask=nothing, error=nothing, maskthresh=false, gain=1.0) =
    sum_shape(data, Circle(x, y, r); mask=mask, error=error,
              maskthresh=maskthresh, gain=gain)

sum_circann{T<:Real}(data::AbstractArray{T, 2}, x::Real, y::Real, rin::Real,
                     rout::Real; mask=nothing, error=nothing,
                     maskthresh=false, gain=1.0) =
    sum_shape(data, CircAnn(x, y, rin, rout); mask=mask, error=error,
              maskthresh=maskthresh, gain=gain)

sum_ellipse{T<:Real}(data::AbstractArray{T, 2}, x::Real, y::Real, a::Real,
                     b::Real, theta::Real; mask=nothing, error=nothing,
                     maskthresh=false, gain=1.0) =
    sum_shape(data, Ellipse(x, y, a, b, theta); mask=mask, error=error,
              maskthresh=maskthresh, gain=gain)


end # module
