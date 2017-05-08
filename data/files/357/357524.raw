module Photometry

import Base.getindex

export CircAperture,
       aperflux

# Apertures ================================================================= #

abstract Aperture
immutable CircAperture <: Aperture
    x::Float64
    y::Float64
    r::Float64
    function CircAperture(x::Real, y::Real, r::Real)
        new(float64(x), float64(y), float64(r))
    end
end

# CCDImage and methods ====================================================== #

type CCDImage
    data
    var
    gain::Float64
end

getindex(v::FloatingPoint, x::Integer, y::Integer) = v
getvar(im::CCDImage, x, y) = getindex(im.var, x, y)
getvar(im::Array, x::Integer, y::Integer) = 0.
gain(im::CCDImage) = im.gain
gain(im::Array) = 0.

# Aperture photometry ======================================================= #

const SUBPIXELS = 5

function aperflux(aper::CircAperture, im)

    scale = 1.0 / SUBPIXELS
    scale2 = scale*scale
    offset = 0.5*(scale-1.0)
    
    r2 = aper.r * aper.r
    
    # Internal and external radius of the oversampled annulus
    # [r-sqrt(2)/2, r+sqrt(2)/2]
    rintlim = aper.r - 0.75;
    rintlim2 = rintlim > 0.0 ? rintlim*rintlim : 0.0
    rextlim2 = (aper.r + 0.75) * (aper.r + 0.75)

    # Box of pixel positions to consider
    xmin = int(aper.x-aper.r+0.499999)
    xmax = int(aper.x+aper.r+0.499999)
    ymin = int(aper.y-aper.r+0.499999)
    ymax = int(aper.y+aper.r+0.499999)

    flux = 0.0
    fluxvar = 0.0
    area = 0.0
    locarea = 0.0

    for y=ymin:ymax
        for x=xmin:xmax
            dx = x - aper.x
            dy = y - aper.y
            pixr2 = dx*dx + dy*dy

            # Pixel might be in aperture
            if pixr2 < rextlim2
                
                # pixel is in oversampled region: sum overlapping area
                if pixr2 > rintlim2

                    # reset dx, dy to corner of pixel
                    dx += offset
                    dy += offset
                    
                    # Sum overlapping area
                    locarea = 0.
                    for sy = 1:SUBPIXELS
                        dx1 = dx
                        dy2 = dy*dy
                        for sx = 1:SUBPIXELS
                            if dx1*dx1 + dy2 < r2
                                locarea += scale2
                            end
                            dx1 += scale
                        end
                        dy += scale
                    end

                # pixel fully within aperture
                else
                    locarea = 1.0
                end
                
                area += locarea
                flux += im[x, y] * locarea
                fluxvar += getvar(im, x, y) * locarea
            end
        end
    end
    flux, sqrt(fluxvar)
end


end # module
