#! /usr/bin/julia

# Rosetta Code, Bitmap/Write a PPM file

type Color
    r::Uint8
    g::Uint8
    b::Uint8
end

type Image
    pic::Array{Color,2}
end

Image(w::Int, h::Int) = Image(Array(Color, w, h))

Base.fill!(a::Image, c::Color) = Base.fill!(a.pic, c)

function splat!(a::Image, x::Int, y::Int, c::Color)
    a.pic[x, y] = c
    nothing
end

function color(a::Image, x::Int, y::Int)
    a.pic[x, y]
end

function showpixel(a::Image, x::Int, y::Int)
    c = color(a, x, y)
    hex(c.r, 2)*hex(c.g, 2)*hex(c.b, 2)
end

function writeppm(fn::String, a::Image)
    outf = open(fn, "w")
    (w, h) = size(a.pic)
    write(outf, "P6\n")
    write(outf, @sprintf "%d %d\n" w h)
    write(outf, @sprintf "%d\n" 255)
    for i in 1:h
        for j in 1:w
            c = color(a, j, i)
            write(outf, c.r)
            write(outf, c.g)
            write(outf, c.b)
        end
    end
    close(outf)
end
    

w = 500
h = 300
a = Image(w, h)

purple = Color(0xff, 0, 0xff)
green = Color(0, 0xff, 0)
white = Color(0xff, 0xff, 0xff)

fill!(a, green)
for i in 20:220, j in 10:100
    splat!(a, i, j, purple)
end
for i in 180:400, j in 80:200
    splat!(a, i, j, white)
end

fn = "bitmap_write.ppm"
writeppm(fn, a)

