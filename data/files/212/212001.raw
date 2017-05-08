include("avcodec_common.jl")
include("avcodec.jl")
include("avutil/avutil_common.jl")
include("avutil/mem.jl")
function ycbcr!(a::Array{Uint8,3},y::Array{Uint8,2},cb::Array{Uint8,2},cr::Array{Uint8,2})
    nc,width,height = size(a)
    for j=1:height,i=1:width y[i,j]=uint8(16+65.481*a[1,i,j]/256+128.553*a[2,i,j]/256+24.966*a[3,i,j]/256) end
    for j=1:ifloor(height/2),i=1:ifloor(width/2)
        r = mean(sub(a,1,(2*i-1):(2*i),(2*j-1):(2*j)))
        g = mean(sub(a,2,(2*i-1):(2*i),(2*j-1):(2*j)))
        b = mean(sub(a,3,(2*i-1):(2*i),(2*j-1):(2*j)))
        cb[i,j] = uint8(128-37.797*r/256-74.203*g/256+112.0*b/256)
        cr[i,j] = uint8(128+112.0*r/256-93.786*g/256-18.214*b/256)
    end
    return(y,cb,cr)
end