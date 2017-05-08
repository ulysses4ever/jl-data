#! /usr/bin/julia

# Rosetta Code, Brownian tree


using Color, Images, FixedPointNumbers

const W = 512
const W0 = W>>1
const H = 512
const H0 = H>>1

type Point{T<:Integer}
    x::T
    y::T
end

type Line{T<:Point}
    a::T
    b::T
    stride = Array{Int,1}
end

function start(l::Line)
    n = l.a*l.sa + l.b*l.sa
    return Segment(l.a, l.b, 1, n)
end

function next(l::Line, s::Segment)
    a = s.a + 1
    
    

function Line(u::Point, v::Point, img::Image)
    if abs(u.x-v.x) > abs(u.y-v.y)
        if v.x > u.x
            x = [u.x, v.x]
            y = [u.y, v.y]
        else
            x = [v.x, u.x]
            y = [v.y, u.y]
        end
    else
        if v.y > u.y
            x = [u.y, v.y]
            y = [u.x, v.x]
        else
            x = [v.y, u.y]
            y = [v.x, v.y]
        end
    end
    a = x[1]
    b = y[1]
    db = y[2] - y[1]
    


            
function motecolor(x::Int, y::Int)
    h = clamp(180*(atan2(y-H0, x-W0)/pi + 1.0), 0.0, 360.0)
    return HSV(h, 0.5, 0.5)
end

img = Image(zeros(RGB{Ufixed8}, H, W))
img["x", W0, "y", H0] = RGB(1, 1, 1)
isfree = trues(W, H)
isfree[W0, H0] = false
for i in 1:N
    x = rand(1:W)
    y = rand(1:H)
    isfree[x, y] || continue
    mc = motecolor(x, y)
    for j in 1:10^3
        xp = x + rand(-1:1)
        yp = y + rand(-1:1)
        iscontained = 0 < xp <= W && 0 < yp <= H
        if  iscontained && isfree[xp, yp]
            x = xp
            y = yp
            continue
        else
            if SIDESTICK || (iscontained && !isfree[xp, yp])
                isfree[x, y] = false
                img["x", x, "y", y] = mc
            end
            break
        end
    end
end

imwrite(img, "brownian_tree.png")

