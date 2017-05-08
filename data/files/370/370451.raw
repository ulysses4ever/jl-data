#systems parameterized in the standard "generalized" form
"""Generalized Lotka-Volterra ecosystem with intrisic growth rate r and community matrix A."""
type GeneralizedLotkaVolterra{S<:AbstractVector{Float64},T<:AbstractMatrix{Float64}} <: AbstractLotkaVolterra
  r::S
  A::T
  function GeneralizedLotkaVolterra{S,T}(r::S,A::T)
    size(A,1) == size(A,2) == length(r) ? new(r,A) : error("dimension mismatch")
  end
end
function GeneralizedLotkaVolterra(r::AbstractVector{Float64},A::AbstractMatrix{Float64})
    GeneralizedLotkaVolterra{typeof(r),typeof(A)}(r,A)
end
function GeneralizedLotkaVolterra(A::AbstractMatrix{Float64})
    N = size(A,1)
    GeneralizedLotkaVolterra(ones(N),A)
end

"""The number of species in the ecosystem"""
nspecies(Z::GeneralizedLotkaVolterra) = length(Z.r)
"""The ecosystem community matrix"""
communitymatrix(Z::GeneralizedLotkaVolterra) = Z.A
"""The intrinsic gorwth rate of the ecosystem"""
intrinsicrate(Z::GeneralizedLotkaVolterra) = Z.r
