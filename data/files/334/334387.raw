VERSION >= v"0.4.0-dev+6521" && __precompile__()

module ImagePlot

using FunctionalDataUtils
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

function plot{T<:Number}(img, points::Array{T,2}, labels::AbstractArray = [];
    compact = false,
    radius = 3px,
    fillcolor = "yellow",
    strokecolor = nothing,
    colormap = [],
    kargs...)
    isempty(points) && return img
    c = context()
    function plotpoints(points, fillcolor)
        newc = context() 
        for i = 1:size(points,2)
            newc = compose(newc,  circle(points[1,i],points[2,i], radius))
        end
        if strokecolor != nothing
            newc = compose(newc, stroke(color(strokecolor)))
        end
        newc = compose(newc, fill(fillcolor))
        c = compose(c, newc)
    end
    if isempty(labels)
        plotpoints(points, fillcolor)
    else
        U = sort(unique(labels))
        if all(x->isa(x,Real), U)
            if isempty(colormap) 
                colors = @p jetcolormap len(U) | unstack | map x->RGB(x...)
            else
                colors = colormap
            end
        else
            colors = U
        end
        for i in 1:length(U)
            plotpoints(points[:,vec(labels .== U[i])], colors[i])
        end
    end
    width, height = size(img)
    c = compose(context(units=UnitBox(0, 0, width, height)), c)
    r = compose(img, c; kargs...)                                      
    if compact
        mi = round(Int,minimum(points,2))
        ma = round(Int,maximum(points,2))
        r = r[clamp(mi[1]-20:ma[1]+20,1,size(r,1)), clamp(mi[2]-20:ma[2]+20,1,size(r,2)), :] 
    end
    r
end


end # module
