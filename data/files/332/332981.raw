## B-Spline Basis
#=
The B-Spline basis functions are...

=#

## Habermann and Kinderman Interpolation
#=
This cubic interpolation scheme is presented in the paper
"Multidimensional Spline Interpolation: Theory and Applications"
(CE 2007) written by Christan Habermann and Fabian Kinderman. It is a
special case of the standard BSpline interpolation, but closed form
solutions allow for faster computation and evaluation.

Note, the nodes here from from 0 to n, so there are n+1 of them

=#

function phi(t)
    abst = abs(t)
    abst <= 1 ? 4. - 6abst^2 + 3abst^3 : abst <= 2 ? (2 - abst)^3 : 0.0
end


immutable HKSplineBasis <: CubicSpline
    n::Int
    a::Float64
    b::Float64
end

get_h(hkb::HKSplineBasis) = (hkb.b - hkb.a) / hkb.n

function support(hkb::HKSplineBasis, x::Real)
    # unpack notation
    a, b, n, h = hkb.a, hkb.b, hkb.n, get_h(hkb)

    # first, if x isn't in [a,b], throw an error
    !(a <= x <= b) && error("x must be in [a,b] ([$a, $b])")

    # compute upper and lower bounds for support at this x
    l = max(floor(Int, (x-a)/h), 1)
    m = min(l+3, n+1)
    l:(m+1)
end

insupport(hkb::HKSplineBasis, x::Real, k::Int) = k ∈ support(hkb, x)


evaluate(hkb::HKSplineBasis, x::Real, k::Int) =
    insupport(hkb, x, k) ? phi((x-hkb.a)/get_h(hkb) - (k-2)) : 0.0

# WARNING: only use this if you know what you are doing!!. It skips
# checking if if x is in the support of u_k. This is to be used
# internally when we are just iterating over all k ∈ support(hkb, x).
# Otherwise, we would duplicate the support checking
unsafe_evaluate(hkb::HKSplineBasis, x::Real, k::Int) =
    phi((x-hkb.a)/get_h(hkb) - (k-2))


function evaluate(hkb::HKSplineBasis, xs::Vector)
    # construct sparse output matrix
    # NOTE: someday sparse might be fast and we can change this to spzeros
    out = zeros(length(xs), hkb.n+3)

    # now fill in rows
    for (i, x) in enumerate(xs), k in support(hkb, x)
        out[i, k] = unsafe_evaluate(hkb, x, k)
    end

    out
end


function get_coefs(hkb::HKSplineBasis, y::AbstractVector; α=0, β=0)
    # Unload params
    a, b, n = hkb.a, hkb.b, hkb.n
    h = get_h(hkb)

    @assert length(y) == n+1 "y should have $(n+1) elements, not $(length(y))"

    # Allocate space for coefficients
    c = Array(Float64, n+3)

    # Step 1: Closed form solutions for 2nd and 2nd to last
    c2 = (y[1] - α*h^2 / 6.) / 6.
    cnp2 = (y[end] - β*h^2 / 6.) / 6.
    c[2] = c2; c[n+2] = cnp2;

    # Step 2: We used first and last 2 equation to get coefficients, so
    # we need to change y. System of (n - 1) unknowns (c3 to cnp1) and
    # (n - 1) equations. Take advantage of fast symtridiag solver
    yp = y[2:end-1]; yp[1] -= c2; yp[end] -= cnp2
    A = SymTridiagonal(fill(4.,n - 1), fill(1.,n - 1))
    c[3:end-2] = A \ yp

    # Step 3: Fill in first/last elements
    c[1] = α*h^2 / 6. + 2*c2 - c[3]
    c[end] = β*h^2 / 6. + 2*cnp2 - c[end-2]

    return c
end


# special case for chebyshev nodes to map points back in to [-1, 1]
function evaluate{EN<:EquidistantNodes}(ii::Interpoland{HKSplineBasis, EN},
                  x::Real)
    out = 0.0
    for k in support(ii.spc.basis, x)
        out += ii.coefs[k] * unsafe_evaluate(ii.spc.basis, x, k)
    end
    out
end

function evaluate{EN<:EquidistantNodes}(ii::Interpoland{HKSplineBasis, EN},
                  x::AbstractVector)
    out = similar(x)
    for i in 1:length(x)
        out[i] = evaluate(ii, x[i])
    end
    out
end


# --- #
# API #
# --- #

default_coefs{EN<:EquidistantNodes}(spc::FunctionalSpace{HKSplineBasis, EN},
                                    y::Vector) =
    get_coefs(spc.basis, y)

FunctionalSpace(hkb::HKSplineBasis) =
    FunctionalSpace(hkb, EquidistantNodes(hkb.n+1, hkb.a, hkb.b))


function hk_interp(m::Int, f::Function, a::Real=-1, b::Real=1, α=0.0, β=0.0)
    hkb = HKSplineBasis(m, a, b)
    nodes = EquidistantNodes(m+1, a, b)
    spc = FunctionalSpace(hkb, nodes)
    y = f(nodes.nodes)
    coefs = get_coefs(hkb, y; α=α, β=β)
    Interpoland(spc, coefs)
end


# --------------- #
# Dierckx Splines #
# --------------- #

# Dierckx will support N=1:5
immutable DierckxSplineBasis{N} <: SplineBasis{N} end
DierckxSplineBasis(N::Int) = DierckxSplineBasis{N}()

degree{K}(db::DierckxSplineBasis{K}) = K

default_coefs{TB<:DierckxSplineBasis}(spc::FunctionalSpace{TB},
                                      y::Vector) =
    Spline1D(nodes(spc), y; k=degree(spc.basis))

# This constructor lets you pass in a vector of nodes, which get's mapped into
# our IrregularNodes type. Call into inner FunctionalSpace constructor
# directly by passing a zero matrix as `_basis_at_nodes`
FunctionalSpace(db::DierckxSplineBasis, nodes::Vector{Float64}) =
    FunctionalSpace(db, IrregularNodes(nodes), zeros(0, 0))

FunctionalSpace(db::DierckxSplineBasis, nodes::InterpolationNodes) =
    FunctionalSpace(db, nodes, zeros(0, 0))

evaluate{TB<:DierckxSplineBasis}(ii::Interpoland{TB}, x::Real) =
    evaluate(ii.coefs, x)

evaluate{TB<:DierckxSplineBasis}(ii::Interpoland{TB}, x::Vector) =
    evaluate(ii.coefs, x)


derivative{TB<:DierckxSplineBasis}(ii::Interpoland{TB}, x::Real; n=1) =
    derivative(ii.coefs, x; nu=n)

derivative{TB<:DierckxSplineBasis}(ii::Interpoland{TB}, x::Vector; n=1) =
    derivative(ii.coefs, x; nu=n)


## Monotonic Cubic Splines
#=
This method of interpolation is first presented by Fritsch and Carlson
in their "Monotone Piecewise Cubic Interpolation" (SIAM Num Anal 1980)
and allows one to get around the non-monotonicities typically presented
by cubic approximations.

=#

## Schumaker Splines
#=
Schumaker splines preserve shape and monotonicity if data exhibit it...
=#

## Knots
#=
Splines must have a set of knots with a certain multiplicity. Need to
figure out how it works before I type anything intelligent here.
=#
