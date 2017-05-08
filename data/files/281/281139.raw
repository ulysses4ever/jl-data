module GCode
using Calculus

const STEP_RATIO = 0.9  # ratio to iteratively shrink the fitting arc segment
const PRINT_DIGITS = 3  # number of digits after comma to print in G-codes

# returns the (center, radius) of the circle, circumscribed around three points
function circumscribed_circle(P1, P2, P3)
    d12 = vec(P1 - P2); n12 = dot(d12, d12)
    d23 = vec(P2 - P3); n23 = dot(d23, d23)
    d31 = vec(P3 - P1); n31 = dot(d31, d31)
    den = norm(cross([d12; 0], [d23; 0]))
    r = sqrt(n12*n23*n31)/(2den)
    a = n23*dot(d12, d31)
    b = n31*dot(d12, d23)
    c = n12*dot(d31, d23)
    PC = -(a*P1 + b*P2 + c*P3)/(2den^2)
    (PC, r)
end

# finds if three points are winded in clockwise direction
is_cw_winding(P1, P2, P3) = cross([vec(P2 - P1); 0], [vec(P3 - P1); 0])[3] < 0

# half-circle equation
f_arc(x, c, R, sign = 1.0) = sign*sqrt(R^2 - (x - c[1])^2) + c[2]

# half-circle equation for a segment
f_arc(x, c, R, p1, p2) = f_arc(x, c, R, (is_cw_winding(p1, c, p2) ? -1.0 : 1.0))

# error distance for a function from an arc, on the given segment
function err_metric(f, c, R, seg)
    x1, x2 = seg
    p1 = [x1 f(x1)]
    p2 = [x2 f(x2)]
    E(x) = (f(x) - f_arc(x, c, R, p1, p2))^2
    sqrt(integrate(E, x1, x2))
end

# makes an arc going through the segment ends and a point inbetween (middle by default)
function make_arc(f, seg, ratio = 0.5)
    x1, x2 = seg
    xc = x1 + (x2 - x1)*ratio
    y1, y2, yc = f(x1), f(x2), f(xc)
    c, R = circumscribed_circle([x1 y1], [xc yc], [x2 y2])
end

# finds the set of segments/arcs fitting the given function within the tolerance
function fit_arcs(f, range, tolerance)
    ra, rb = range
    D = rb - ra
    rel_tol = tolerance/D
    ca = ra
    segs, arcs = [], []
    # iterate until covered the whole range
    while (ca < rb)
        cb = rb
        # shrink the arc until within the tolerance
        while true
            c, R = make_arc(f, [ca cb])
            E = err_metric(f, c, R, [ca cb])
            if E <= rel_tol*(cb - ca)
                segs = [segs, (ca, cb)]
                arcs = [arcs, (c, R)]
                ca = cb
                break
            end
            cb = ca + STEP_RATIO*(cb - ca)
        end
    end
    segs, arcs
end

# creates G-codes string from the list of segments/arcs
function make_g_code(f, segs, arcs)
    fmt(x) = (x == ceil(x)) ? int64(x) : round(x, PRINT_DIGITS)
    function arc2g(x)
        ((cx, cy), R), (a, b) = x
        fa, fb = f(a), f(b)
        (is_cw_winding([cx cy], [b fb], [a fa]) ? "G02" : "G03") * " X$(fmt(b)) Y$(fmt(fb)) I$(fmt(cx - b)) J$(fmt(cy - fb))"
    end
    start, = segs[1]
    "G00 X$(fmt(start)) Y$(fmt(f(start))) " *
        join(map(arc2g, zip(arcs, segs)), " ")
end

# creates G-codes string to interpolate the given function within a tolerance
function fit_g_code(f, range, tolerance)
    segs, arcs = fit_arcs(f, range, tolerance)
    make_g_code(f, segs, arcs)
end

end # module GCode
