
type GaussQuadratureRule
    weights::Vector{Float64}
    points::Vector{Vector{Float64}}
end

weights(qr::GaussQuadratureRule) = qr.weights
points(qr::GaussQuadratureRule) = qr.points

function integrate(qr::GaussQuadratureRule, f::Function)
    I = 0.0
    for (w, x) in zip(weights(qr), points(qr))
        I += w * f(x)
    end
    return I
end

# Maybe we could stage the coming three function and create ndim loops.
function make_quadrule(ref::ReferenceLine, order::Int)
    p, w = gausslegendre(order)
    weights = Array(Float64, order)
    points = Array(Vector{Float64}, order)
    count = 1
    for i = 1:order
        points[count] = [p[i]]
        weights[count] = w[i]
        count += 1
    end
    GaussQuadratureRule(weights, points)
end

function make_quadrule(ref::ReferenceSquare, order::Int)
    p, w = gausslegendre(order)
    weights = Array(Float64, order^2)
    points = Array(Vector{Float64}, order^2)
    count = 1
    for i = 1:order, j = 1:order
        points[count] = [p[i], p[j]]
        weights[count] = w[i] * w[j]
        count += 1
    end
    GaussQuadratureRule(weights, points)
end


function make_quadrule(ref::ReferenceCube, order::Int)
    p, w = gausslegendre(order)
    weights = Array(Float64, order^3)
    points = Array(Vector{Float64}, order^3)
    count = 1
    for i = 1:order, j = 1:order, k = 1:order
        points[count] = [p[i], p[j], p[k]]
        weights[count] = w[i] * w[j] * w[k]
        count += 1
    end
    GaussQuadratureRule(weights, points)
end


function make_quadrule(ref::ReferenceTriangle, order::Int)
    p1, w1 = gaussjacobi(order, 0.0, 0.0)
    p2, w2 = gaussjacobi(order, 1.0, 0.0)

    affine(a, b) = [(1+a) * (1-b) / 4, (1+b) / 2]

    SCALE = 1/8
    weights = Array(Float64, order^2)
    points = Array(Vector{Float64}, order^2)
    count = 1
    for i = 1:order, j = 1:order
        weights[count] = w1[i] * w2[j] * SCALE
        points[count] = affine(p1[i], p2[j])
        count += 1
    end
    GaussQuadratureRule(weights, points)
end

function make_quadrule(ref::ReferenceTetrahedron, order::Int)
    p1, w1 = gaussjacobi(order, 0.0, 0.0)
    p2, w2 = gaussjacobi(order, 1.0, 0.0)
    p3, w3 = gaussjacobi(order, 2.0, 0.0)
    error("Bugged!")
    function affine(a, b, c)
       a = (a+1) / 2
       b = (b+1) / 2
       c = (c+1) / 2
       [a*b*c, a*b*(1-c), a*(1-b)]
     end

    SCALE = 1/48
    weights = Array(Float64, order^3)
    points = Array(Vector{Float64}, order^3)
    count = 1
    for i = 1:order, j = 1:order, k = 1:order
        weights[count] = w1[i] * w2[j] * w2[k] * SCALE
        points[count] = affine(p1[i], p2[j], p3[k])
        count += 1
    end
    GaussQuadratureRule(weights, points)
end

