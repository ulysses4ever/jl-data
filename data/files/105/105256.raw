using Color
using Images

# Command-line program that draws the Mandelbrot set. Usage:
#     julia mandelbrot.jl sx sy
# Creates an image of size sx by sy and saves it as mandelbrot.png.

const n = 10000 # maximum number of iterations

# Check if the complex number sequence z -> z^2 + c, which defines the
# Mandelbrot set, diverges. Returns the number of iterations after which
# abs(z) >= 2 (which proves it diverges) or 0 if that didn't happen within 'n'
# iterations.
function f(c::Complex{Float64})
    z = 0.0im
    for i=1:n
        z = z*z + c
        if abs2(z) >= 4.0
            return i
        end
    end
    return 0
end

function mix(c1::RGB, c2::RGB, r::Float64)
    return RGB(c1.r * (1-r) + c2.r * r,
               c1.g * (1-r) + c2.g * r,
               c1.b * (1-r) + c2.b * r)
end

# linear gradient with 'n' colors from 'a' to 'b' (including 'a' but not 'b')
function color_gradient(a::RGB, b::RGB, n::Int)
    scale = Array(RGB, n)
    for i=1:n
        scale[i] = mix(a, b, (i-1)/n)
    end
    return scale
end

# array of 't' color values that cycles through 'colors'
function color_cycle(colors::Vector{RGB}, t::Int)
    n = length(colors)
    r = Array(RGB, t)
    for i=1:t
        r[i] = colors[mod((i-1),n)+1]
    end
    return r
end

# create Mandelbrot image of size sx by sy
function mandelbrot_image(sx, sy)
    # calculate height
    const width = 3.0
    const height = (width / sx) * sy

    # compute the image pixel-by-pixel
    const xdelta = width / (sx-1)
    const ydelta = - height / (sy-1)
    const xstart = -2.0
    const ystart = height / 2.0
    A = Array(Int, sy, sx)
    for j=1:sy
        y = ystart + (j-1)*ydelta
        for i=1:sx
            x = xstart + (i-1)*xdelta
            A[j,i] = f(x + y*im)
        end
    end

    const black  = RGB(0.0, 0.0, 0.0)
    const blue   = RGB(0.4, 0.4, 1.0)
    const white  = RGB(1.0, 1.0, 1.0)
    const yellow = RGB(1.0, 0.8, 0.0)

    # create color scale
    a,b,c,d = (black, blue, white, yellow)
    const k = 60
    scale = [color_gradient(a, b, k);
    color_gradient(b, c, k);
    color_gradient(c, d, k);
    color_gradient(d, a, k)]
    colors = color_cycle(scale, n)

    # determine image colors
    image = Array(RGB, sy, sx)
    for j=1:sy, i=1:sx
        index = A[j,i]
        color = (index == 0) ? black : colors[index]
        image[j,i] = color
    end

    return image
end

# get image size from command line parameters
const sx = length(ARGS) < 1 ? 600 : int(ARGS[1])
const sy = length(ARGS) < 2 ? 400 : int(ARGS[2])

# create PNG image
imwrite(mandelbrot_image(sx,sy), "mandelbrot.png")
