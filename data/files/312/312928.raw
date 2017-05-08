#! /usr/bin/julia

# Rosetta Code, Bitmap

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

w = 5
h = 7
a = Image(w, h)

purple = Color(0xff, 0, 0xff)
green = Color(0, 0xff, 0)

fill!(a, purple)
splat!(a, 2, 3, green)

for i in 1:h
    for j in 1:w
        print(showpixel(a, j, i), " ")
    end
    println()
end
        

