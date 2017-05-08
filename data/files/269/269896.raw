## Monomial basis
immutable MonomialBasis{N} <: PolynomialBasis{N} end
MonomialBasis(N::Int) = MonomialBasis{N}()

evaluate{N}(::MonomialBasis{N}, x::Real) = Float64[x^i for i=0:N]

function evaluate!{N}(::MonomialBasis{N}, xs::Vector, out::Matrix)
    @assert size(out) == (length(xs), N+1) "output wrong size"
    for i=0:N, j=1:length(xs)
        out[j, i+1] = xs[j]^i
    end
    return out
end

FunctionalSpace{N}(mb::MonomialBasis{N}) =
    FunctionalSpace(mb, ChebyshevNodes(N+1))

FunctionalSpace{N}(mb::MonomialBasis{N}, a::Real, b::Real) =
    FunctionalSpace(mb, ChebyshevNodes(N+1, a, b))
