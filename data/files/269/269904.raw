module TempInterp

import Dierckx: evaluate, Spline1D, derivative

# basis functions
export BasisFunctions, SpectralBasis, PolynomialBasis,
       OrthogonalPolynomialBasis, FiniteElementBasis, SplineBasis,
       LinearSpline, CubicSpline, ChebyshevBasis, MonomialBasis,
       HKSplineBasis, DierckxSplineBasis

# nodes
export InterpolationNodes, EquidistantNodes, ChebyshevNodes


# spaces/interpoland
export FunctionalSpace, Interpoland

# functions
export default_coefs, evaluate, evaluate!, degree, hk_interp, cheb_interp,
       differentiate, nodes, derivative



using LaTeXStrings

# set up type system in this file and then include other files

# --------------- #
# Basis Functions #
# --------------- #

abstract BasisFunctions{N}

# SpectralBasis
abstract SpectralBasis{N} <: BasisFunctions{N}
abstract PolynomialBasis{N} <: SpectralBasis{N}
abstract OrthogonalPolynomialBasis{N} <: PolynomialBasis{N}

# Finite Element Basis
abstract FiniteElementBasis{N} <: BasisFunctions{N}
abstract SplineBasis{N} <: FiniteElementBasis{N}

typealias LinearSpline SplineBasis{1}
typealias CubicSpline SplineBasis{3}


# Generic Functions for all BasisFunctions subtypes

# general evaluation of any BasisFunctions at a vector of points
evaluate{N}(b::BasisFunctions{N}, x::AbstractVector) =
    evaluate!(b, x, similar(x, length(x), N+1))

evaluate!(b::BasisFunctions, x::AbstractVector, y) =
    error("This function should be defined for subtypes of BasisFunctions")

degree{N}(::BasisFunctions{N}) = N
Base.length{N}(::BasisFunctions{N}) = N+1
Base.size{N}(::BasisFunctions{N}) = (N+1, )
Base.size{N}(::BasisFunctions{N}, i::Int) = i == 1 ? N+1 : 1


# ----------- #
# Nodes/Knots #
# ----------- #

abstract InterpolationNodes{M}

Base.size{M}(::InterpolationNodes{M}) = (M,)
Base.length{M}(::InterpolationNodes{M}) = M
Base.min(nodes::InterpolationNodes) = nodes.a
Base.max(nodes::InterpolationNodes) = nodes.b
Base.writemime{T<:InterpolationNodes}(io::IO, ::MIME"text/plain", pts::T) =
    print(io, "$T on [$(pts.a), $(pts.b)]")
nodes(n::InterpolationNodes) = nodes.nodes

# equidistant nodes. They don't really belong anywhere else, so we just
# put them here
immutable EquidistantNodes{M} <: InterpolationNodes{M}
    a::Float64
    b::Float64
    nodes::Vector{Float64}
    h::Float64

    function EquidistantNodes(a::Real, b::Real)
        new(a, b, linspace(a, b, M), (b-a)/(M - 1))
    end

end

EquidistantNodes(M::Int, a::Real, b::Real) = EquidistantNodes{M}(a, b)


immutable IrregularNodes{M} <: InterpolationNodes{M}
    a::Float64
    b::Float64
    nodes::Vector{Float64}
end

IrregularNodes(x::Vector{Float64}) =
    IrregularNodes{length(x)}(minimum(x), maximum(x), x)

# --------------- #
# FunctionalSpace #
# --------------- #

immutable FunctionalSpace{TB<:BasisFunctions, TN <: InterpolationNodes}
    basis::TB
    nodes::TN
    _basis_at_nodes::Matrix
end


FunctionalSpace{TB<:BasisFunctions, TN <: InterpolationNodes}(basis::TB,
                                                             nodes::TN) =
    FunctionalSpace(basis, nodes, evaluate(basis, nodes.nodes))

Base.min(spc::FunctionalSpace) = min(spc.nodes)
Base.max(spc::FunctionalSpace) = max(spc.nodes)
nodes(spc::FunctionalSpace) = spc.nodes.nodes

function Base.writemime{TB, TN}(io::IO, ::MIME"text/plain",
                                spc::FunctionalSpace{TB, TN})
    deg = degree(spc.basis)
    m = "Functional Space of $(TB)\nwith Nodes $(TN)\nof degree $deg"
    print(io, m)
end

# default to solving for coefficients using least squares
default_coefs(spc::FunctionalSpace, y::Vector) = coefs_ls(spc, y)

# -------------------------- #
# Final Interpolation Object #
# -------------------------- #

immutable Interpoland{TB<:BasisFunctions, TN <: InterpolationNodes, TC}
    spc::FunctionalSpace{TB, TN}
    coefs::TC
end

Base.writemime(io::IO, ::MIME"text/plain", i::Interpoland) =
    print(io, repr(typeof(i)))

degree(interp::Interpoland) = degree(interp.spc.basis)

# evaluate the interpoland. This is very general and should work for
# all subtypes of Interpoland, but is probably not the most efficient
evaluate(ii::Interpoland, x::Real) = dot(ii.coefs, evaluate(ii.spc.basis, x))
evaluate(ii::Interpoland, x::AbstractVector) =
  evaluate(ii.spc.basis, x) * ii.coefs

# constructor to take a functional space plus a vector y of the function
# on spc.nodes.nodes and compute coefs using `default_coefs`
function Interpoland(spc::FunctionalSpace; y::Vector=[NaN])
    if all(isnan(y))
        error("I don't know how you got here, but pass f(nodes) as kwarg y")
    end
    coefs = default_coefs(spc, y)
    Interpoland(spc, coefs)
end


# constructor to take a functional space plus a function f. This will compute
# f(spc.nodes.nodes) and pass to constructor for space and vector
Interpoland(spc::FunctionalSpace, f::Function) =
    Interpoland(spc; y=f(nodes(spc)))

# constructor to take just a basis, compute the default functional space
# for that basis, and use the constructor for a space and vector
Interpoland(basis::BasisFunctions; y::Vector=[NaN]) =
    Interpoland(FunctionalSpace(basis); y=y)


# constructor to take just a basis, compute the default functional space
# for that basis, and use the constructor for a space and function
Interpoland(basis::BasisFunctions, f::Function) =
    Interpoland(FunctionalSpace(basis), f)







# -------- #
# Includes #
# -------- #

# types of basis
include("monomials.jl")
include("chebyshev.jl")
include("splines.jl")

# util
include("util.jl")


end  # module
