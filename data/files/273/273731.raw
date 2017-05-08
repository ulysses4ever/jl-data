module ImagePlot

using Images, Compose, Color 
import Cairo, FixedPointNumbers
import Compose.compose

export plot

function compose(img::Image, c::Context)
    width, height = size(img)
    
    surface = Cairo.CairoARGBSurface(zeros(Uint32, height, width))
    draw(PNG(surface), c)
    overlay = reinterpret(BGRA{FixedPointNumbers.Ufixed8}, surface.data)
    
    outimg = similar(img)
    for i=1:width, j=1:height
        alpha = overlay[i,j].alpha
        overlay_pixel = convert(eltype(img), overlay[i,j])
        beta = one(alpha) - alpha
        outimg[i,j] = beta*img[i,j] + alpha*overlay_pixel
    end
    
    outimg
end



function plot{T<:Number}(img::Image, points::Array{T,2}; radius = 3px, fillcolor = "yellow", strokecolor = nothing)
    c = context()
    for i = 1:size(points,2)
        c = compose(c,  circle(points[2,i],points[1,i], radius))
    end
    if strokecolor != nothing
        c = compose(c, stroke(color(strokecolor)))
    end
    c = compose(c, fill(fillcolor))
    width, height = size(img)
    c = compose(context(units=UnitBox(0, 0, width, height)), c)
    compose(img, c)
end


end # module
