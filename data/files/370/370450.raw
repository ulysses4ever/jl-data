#systems parameterized in the standard "generalized" form
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
    N = size(A)[1]
    GeneralizedLotkaVolterra(ones(N),A)
end

nspecies(Z::GeneralizedLotkaVolterra) = length(Z.r)
communitymatrix(Z::GeneralizedLotkaVolterra) = Z.A
intrinsicrate(Z::GeneralizedLotkaVolterra) = Z.r
