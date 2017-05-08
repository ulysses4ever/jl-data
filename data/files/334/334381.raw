module ImagePlot

using Compose, Color, Compat
import Cairo, FixedPointNumbers
import Compose.compose
import Images

export plot

# M x N  or  M x N x 3 image of float in 0..1
function compose{T<:Real,N}(img::Array{T,N}, c::Context; usealpha = true)
    sm, sn = size(img)
    
    surface = Cairo.CairoARGBSurface(zeros(UInt32, sn, sm)) # width and height
    draw(PNG(surface), c)
    overlay = reinterpret(UInt8, surface.data, (4, sm, sn)) / 255
    
    outimg = similar(img, sm, sn, 3)
    imgind = (ndims(img) == 3 && size(img,3) == 3) ? [1,2,3] : [1,1,1]
    for m = 1:sm, n = 1:sn
        alpha = overlay[4,m,n]
        alpha = usealpha ? alpha : convert(typeof(alpha), alpha > 0.5)
        beta = one(alpha) - alpha
        for i = 1:3
            outimg[m,n,i] = beta*img[m,n,imgind[i]] + alpha*overlay[4-i,m,n]
        end
    end
    
    outimg
end

function plot{T<:Number}(img, points::Array{T,2}; radius = 3px, fillcolor = "yellow", strokecolor = nothing, kargs...)
    c = context()
    for i = 1:size(points,2)
        c = compose(c,  circle(points[1,i],points[2,i], radius))
    end
    if strokecolor != nothing
        c = compose(c, stroke(color(strokecolor)))
    end
    c = compose(c, fill(fillcolor))
    width, height = size(img)
    c = compose(context(units=UnitBox(0, 0, width, height)), c)
    compose(img, c; kargs...)
end


end # module
