#! /usr/bin/julia

# Rosetta Code, Circles of given radius through two points

immutable Point{T<:FloatingPoint}
    x::T
    y::T
end

immutable Circle{T<:FloatingPoint}
    c::Point{T}
    r::T
end
Circle{T<:FloatingPoint}(a::Point{T}) = Circle(a, zero(T))

using AffineTransforms

function circlepoints{T<:FloatingPoint}(a::Point{T}, b::Point{T}, r::T)
    cp = Circle{T}[]
    r >= 0 || return (cp, "No Solution, Negative Radius")
    if a == b
        if abs(r) < 2eps(zero(T))
            return (push!(cp, Circle(a)), "Point Solution, Zero Radius")
        else
            return (cp, "Infinite Solutions, Indefinite Center")
        end
    end
    ca = Complex(a.x, a.y)
    cb = Complex(b.x, b.y)
    d = (ca + cb)/2
    tfd = tformtranslate([real(d), imag(d)])
    tfr = tformrotate(angle(cb-ca))
    tfm = tfd*tfr
    u = abs(cb-ca)/2
    r-u > -5eps(r) || return(cp, "No Solution, Radius Too Small")
    if r-u < 5eps(r)
        push!(cp, Circle(apply(Point, tfm*[0.0, 0.0]), r))
        return return (cp, "Single Solution, Degenerate Centers")
    end
    v = sqrt(r^2 - u^2)
    for w in [v, -v]
        push!(cp, Circle(apply(Point, tfm*[0.0, w]), r))
    end
    return (cp, "Two Solutions")
end

tp = [Point(0.1234, 0.9876),
      Point(0.0000, 2.0000),
      Point(0.1234, 0.9876),
      Point(0.1234, 0.9876),
      Point(0.1234, 0.9876)]

tq = [Point(0.8765, 0.2345),
      Point(0.0000, 0.0000),
      Point(0.1234, 0.9876),
      Point(0.8765, 0.2345),
      Point(0.1234, 0.9876)]

tr = [2.0, 1.0, 2.0, 0.5, 0.0]

println("Testing circlepoints:")
for i in 1:length(tp)
    p = tp[i]
    q = tq[i]
    r = tr[i]
    (cp, rstatus) = circlepoints(p, q, r)
    println(@sprintf("(%.4f, %.4f), (%.4f, %.4f), %.4f => %s",
                     p.x, p.y, q.x, q.y, r, rstatus))
    for c in cp
        println(@sprintf("    (%.4f, %.4f), %.4f",
                         c.c.x, c.c.y, c.r))
    end
end
