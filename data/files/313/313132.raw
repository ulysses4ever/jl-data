#systems parameterized inthe standard "generalized" form
type LotkaVolterraSystem{S<:AbstractVector{Float64},T<:AbstractMatrix{Float64}} <: AbstractLotkaVolterraSystem
    N::Int64
    r::S
    A::T
    function LotkaVolterraSystem{S,T}(N::Int64,r::S,A::T)
        (N==length(r)) & (size(A)==(N,N)) ? new(N,r,A) : error("dimension mismatch")
    end
end
function LotkaVolterraSystem(r::AbstractVector{Float64},A::AbstractMatrix{Float64})
    LotkaVolterraSystem{typeof(r),typeof(A)}(length(r),r,A)
end
function LotkaVolterraSystem(A::AbstractMatrix{Float64})
    N = size(A)[1]
    LotkaVolterraSystem(ones(N),A)
end

communitymatrix(Z::LotkaVolterraSystem) = Z.A
intrinsicrate(Z::LotkaVolterraSystem) = Z.r
