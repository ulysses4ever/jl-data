## Chebyshev Basis
immutable ChebyshevBasis{N} <: OrthogonalPolynomialBasis{N} end
ChebyshevBasis(N::Int) = ChebyshevBasis{N}()

# Evaluation of Chebyshev polynomials

function evaluate{N}(::ChebyshevBasis{N}, x::Real)
    out = Array(Float64, N+1)
    out[1] = 1.0
    out[2] = x
    for i=3:N+1
        out[i] = 2x*out[i-1] - out[i-2]
    end
    return out
end

function evaluate!{N}(::ChebyshevBasis{N}, x::AbstractVector, out::Matrix)
    @assert size(out) == (length(x), N+1) "output wrong size"
    out[:, 1] = 1.0
    out[:, 2] = x
    for i=3:N+1, j=1:length(x)
        out[j, i] = 2x[j].*out[j, i-1] - out[j, i-2]
    end
    return out
end

# --------------- #
# Chebyshev Nodes #
# --------------- #

# NOTE: I go from n:-1:1 so that they are sorted increasing
cheb_nodes(n::Int) = cos(π*(2*(n:-1:1) - 1)/(2n))

"""
Extend the Chebyshev grid from [-1, 1] to [a, b). If the optional
Boolean keyword argument `extended` is true, the resultant grid will
be set to exactly equal a at the lower bound

Default arguments are to keep the grid on [-1, 1], but make the bottom
grid point exactly -1

"""
function cheb_trans(x, m::Int, a::Real, b::Real; extended::Bool=false)
    extended ? (b+a)/2 + sec(π/(2m)) * (b-a)/2 .* x :
               (b+a)/2 + x.* (b-a)/2
end


"""
Retract the Chebyshev grid points from [a, b) back to [-1, 1]. If the
optional Boolean argument `extended` is true, this routine assumes that
the points were mapped into [a, b) such that the minimal node was
exactly equal to a. Otherwise, a standard linear mapping is performed.

Same default arguments as `cheb_trans`
"""
function cheb_itrans(z, m::Int, a::Real, b::Real; extended::Bool=false)
    extended ? cos(π/(2m)) * 2/(b-a) .* (z - (b+a)/2) :
               z.* 2/(b-a) - (b+a)/(b-a)
end


immutable ChebyshevNodes{M} <: InterpolationNodes{M}
    nodes::Vector{Float64}  # nodes on user domain [a, b]
    _cube_nodes::Vector{Float64}  # actual chebyshev nodes on [-1, 1]
    a::Float64  # lower bound for domain
    b::Float64  # upper bound for domain
    extended::Bool
end

function ChebyshevNodes(M::Int, a::Real=-1, b::Real=1; extended::Bool=false)
    _cube_nodes = cheb_nodes(M)
    nodes = cheb_trans(_cube_nodes, M, a, b; extended=extended)
    ChebyshevNodes{M}(nodes, _cube_nodes, a, b, extended)
end


function ChebyshevNodes{N}(cb::ChebyshevBasis{N}, a::Real=-1, b::Real=1;
                           extended::Bool=false)
    ChebyshevNodes(N+1, a, b; extended=extended)
end

# method to shift any random points back to [-1, 1] given fields on cn
function cheb_itrans(cn::ChebyshevNodes, zs)
    cheb_itrans(zs, length(cn.nodes), cn.a, cn.b; extended=cn.extended)
end


# ---------- #
# Evaluation #
# ---------- #

# # special case for chebyshev nodes to map points back in to [-1, 1]
evaluate{TB<:ChebyshevBasis, TN<:ChebyshevNodes}(ii::Interpoland{TB, TN},
                                                   x::Real) =
    dot(ii.coefs, evaluate(ii.spc.basis, cheb_itrans(ii.spc.nodes, x)))

evaluate{TB<:ChebyshevBasis, TN<:ChebyshevNodes}(ii::Interpoland{TB, TN},
                                                   x::Vector) =
    evaluate(ii.spc.basis, cheb_itrans(ii.spc.nodes, x)) * ii.coefs

# implement specific coefs routine to evaluate the basis functions using the
# nodes on [-1, 1] when computing coefficients
coefs_ls{TB<:ChebyshevBasis, TN<:ChebyshevNodes}(spc::FunctionalSpace{TB, TN},
                                                     y::AbstractVector) =
    evaluate(spc.basis, spc.nodes._cube_nodes) \ y


function differentiate(ii::Interpoland)
    error("Not implemented (yet) for this type")
end

function differentiate{N}(ii::Interpoland{ChebyshevBasis{N}}, n=1)
    @assert n >= 0 "can't do negative differentiation, call integrate function"

    # pull out parameters
    a, b = min(ii.spc.nodes), max(ii.spc.nodes)

    # construct new cofficient matrix by left multiplying by necessary deriv
    # matrices
    new_c = foldl(*, [der_matrix(i) for i=(N-n+1):N]) * ii.coefs

    # construct new basis. Substract one to account for 0th order term
    new_cb = ChebyshevBasis(length(new_c) - 1)

    spc2 = FunctionalSpace(new_cb, ii.spc.nodes)

    # keep same nodes and construct new interpoland
    Interpoland(spc2, new_c)
end


# derivative matrix
function der_matrix(deg::Int, a::Real=-1, b::Real=1)
    N = deg
    D = zeros(Float64, N, N+1)
    for i=1:N, j=1:N+1
        if i == 1
            if iseven(i + j)
                continue
            end
            D[i, j] = 2*(j-1)/(b-a)
        else
            if j < i || iseven(i+j)
                continue
            end
            D[i, j] = 4*(j-1)/(b-a)
        end
    end

    D
end


# --- #
# API #
# --- #

FunctionalSpace(cb::ChebyshevBasis) = FunctionalSpace(cb, ChebyshevNodes(cb))

FunctionalSpace(cb::ChebyshevBasis, a::Real, b::Real) =
    FunctionalSpace(cb, ChebyshevNodes(cb, a, b))

# We need a special constructor for FunctionalSpace when we have Chebyshev
# basis/nodes
FunctionalSpace{TB<:ChebyshevBasis, TN <: ChebyshevNodes}(basis::TB,
                                                          nodes::TN) =
    FunctionalSpace(basis, nodes, evaluate(basis, nodes._cube_nodes))


function cheb_interp(n::Int, f::Function, a::Real=-1, b::Real=1)
    cb = ChebyshevBasis(n)
    nodes = ChebyshevNodes(cb, a, b; extended=false)
    spc = FunctionalSpace(cb, nodes)
    y = f(nodes.nodes)
    coefs = coefs_ls(cb, nodes._cube_nodes, y)
    Interpoland(spc, coefs)
end
